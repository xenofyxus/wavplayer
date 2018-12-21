#include "sdhcio.h"
#include "ctrlregs.h"
#include "FAT32lib.h"

//hardcoded pins to use for custom synchronized SPI protocol
#define DI  PORTS->B.PORT.BITS.BIT12
#define DO  PORTS->D.PORT.BITS.BIT2
#define CLK PORTS->D.PORT.BITS.BIT3
#define CS  PORTS->B.PORT.BITS.BIT1
#define INITCLOCK (128)
#define NORMCLOCK (0)

int clock;

// double buffered. the FAT region is accessed often and mostly the same block
// sry for spagetti
unsigned int genbufsector = 0xFFFFFFFF;
unsigned int fatbufsector = 0xFFFFFFFF;
unsigned char genbuf[SDBLOCKSIZE];
unsigned char fatbuf[SDBLOCKSIZE];

unsigned char sd_byte(unsigned char data)
{
	int shiftcount;
	int tick = 0;
	for (shiftcount = 0; shiftcount != 8; shiftcount++)
	{
		DO = data >> 7;
		CLK = 0;
		for (; tick != clock; tick++);
		CLK = 1;
		for (; tick != 0; tick--);
		data = (data << 1) | DI;
	}
	return data;
}

long long sd_cmd(int cmd, unsigned int arg, int crc)
{
	int readpos;
	long long response;
	int i;
	CS = 0; //sync

	//send command
	sd_byte(0xFF); //dummy byte, must be included
	sd_byte(0x40 | cmd);
	sd_byte(arg >> 24);
	sd_byte(arg >> 16);
	sd_byte(arg >> 8);
	sd_byte(arg);
	sd_byte(crc);

	//wait for response
	do
	{
		response = sd_byte(0xFF);
	} while (response & 0x80);

	//do extra stuff if the response is not supposed to be just 1 byte
	switch (cmd)
	{
	case 8:
		response = response << 32;
		for (i = 24; i != -8; i -= 8)
		{
			response = (response & 0xFFFFFFFFFF) | (sd_byte(0xFF) << i);
		}
		break;
	case 17:
		while (sd_byte(0xFF) != 0xFE);

		for (readpos = 0; readpos != 512; readpos++) //load 512 bytes
		{
			sdblockbuffer[readpos] = sd_byte(0xFF);
		}

		for (readpos = 0; readpos != 5; readpos++) //skip CRC
		{
			sd_byte(0xFF);
		}
	default: break;
	}

	//wait for end of receive just in case
	while (sd_byte(0xFF) != 0xFF);

	//dummy byte
	sd_byte(0xFF);
	CS = 1;

	return response;
}

void sd_init(void)
{
	register unsigned int delay = 0;
	long long response;

	sdblockbuffer = genbuf;

	PORTS->B.TRIS.BITS.BIT12 = 1;
	PORTS->D.TRIS.BITS.BIT2 = 0;
	PORTS->D.TRIS.BITS.BIT3 = 0;
	PORTS->B.TRIS.BITS.BIT1 = 0;

	//max 400 kHz
	clock = INITCLOCK;

	CS = 1;
	// Wait at least 1 ms
	for (delay = 0; delay != 800000; delay++);
	CLK = 1;

	//send 80 highs
	for (delay = 0; delay != 11; delay++)
	{
		sd_byte(0xFF);
	}

	//go idle
	sd_cmd(0, 0, 0x95);

	//query voltage
	sd_cmd(8, 0x1AA, 0x87);

	//wait for initialization
	do
	{
		sd_cmd(55, 0, 0);
	} while (sd_cmd(41, 0x40000000, 0));

	//get OCR (check if high capacity)
	sd_cmd(58, 0, 0);

	//set block length to 512 just in case (default for SDHC)
	sd_cmd(16, 512, 0);

	//gotta go fast
	clock = NORMCLOCK;
}

//reads a block 
void sd_readblock(unsigned int address)
{
	// saves last loaded block so it doesn't load again
	if (address >= FAT_FBA && address < FAT_CBA)
	{
		sdblockbuffer = fatbuf;
		if (address == fatbufsector)
			return;
		fatbufsector = address;
	}
	else
	{
		sdblockbuffer = genbuf;
		if (address == genbufsector)
			return;
		genbufsector = address;
	}

	//read block cmd
	sd_cmd(17, address, 0);
}
