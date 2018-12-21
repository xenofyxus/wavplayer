#include <stdlib.h>
#include "ctrlregs.h"
#include "sndlib.h"
#include "sdhcio.h"
#include "displib.h"
#include "FAT32lib.h"

// Contains relevant .wav header data
struct
{
	unsigned int samplerate;
	unsigned int size;
} wavdata;

//buffers for writing to the screen
char strbuf[16];
char timebuf[16];

//converts number to ascii hex representation
char hexasc(int num)
{
	num = num & 0xF;
	if (num > 9)
		return num + 55;
	return num + 48;
}

//converts long long to 16 hexadecimal chars
void inttostr(long long num, char* out)
{
	int i;
	for (i = 15; i != -1; i--)
	{
		out[i] = hexasc(num);
		num = num >> 4;
	}
}

//converts number to decimal stringrepresentation with a given digit length (does not work when the number is longer than len)
void dectostr(int num, char* dst, int len)
{
	int i, exp, dig;
	exp = 1;
	for (i = 1; i != len; i++) exp *= 10;
	i = 0;
	do
	{
		for (dig = 0; num >= exp; num -= exp) dig++;
		dst[i++] = dig + '0';
		exp /= 10;
	} while (i < len);
}

//converts array of bytes to their hexadecimal string representation
void atohex(char* src, char* out)
{
	int i;
	for (i = 0; i != 8; i++)
	{
		out[i * 2] = hexasc(src[i] >> 4);
		out[i * 2 + 1] = hexasc(src[i]);
	}
}

//simply copies memory
void cpymem(char* src, char* dst, int len)
{
	int i;
	for (i = 0; i != len; i++)
	{
		dst[i] = src[i];
	}
}

//fills memory with ascii spaces
void spacemem(char* p, int len)
{
	int i;
	for (i = 0; i != len; i++)
	{
		p[i] = ' ';
	}
}

//initializes buttons, switches and LEDs
void ui_init(void)
{
	PORTS->E.TRIS.LED.FULL = 0x00;
	PORTS->E.PORT.LED.FULL = 0x00;
	PORTS->D.TRIS.BTN.FULL = 0x7;
	PORTS->F.TRIS.BTN1 = 0x1;
	PORTS->D.TRIS.SW.FULL = 0xF;
}

//validates and extracts data from the .wav file
int parsewavheader()
{
	if (sdblockbuffer[0] != 'R' || sdblockbuffer[1] != 'I' || sdblockbuffer[2] != 'F' || sdblockbuffer[3] != 'F')
		return 0;
	wavdata.samplerate = (int)sdblockbuffer[24] | ((int)sdblockbuffer[25] << 8) | ((int)sdblockbuffer[26] << 16) | ((int)sdblockbuffer[27] << 24);
	wavdata.size = (int)sdblockbuffer[40] | ((int)sdblockbuffer[41] << 8) | ((int)sdblockbuffer[42] << 16) | ((int)sdblockbuffer[43] << 24);
	return 1;
}

int main(void)
{
	DirEntryAddr file;
	int player_bytecount, player_currentcluster, player_currentsector, player_currentbyte, player_maxbyte, fat_entryoffset;
	int player_playing, player_progresscount;
	int btn_last1, btn_last2, btn_last3, btn_last4;
	int btn_now1, btn_now2, btn_now3, btn_now4;
	int readdirection = 1;
	int delay;
	int btnmode = 0;
	int totalseconds;
	file.entry = -32;
	file.sector = 0;

	//fills the last chars to show in the screen with spaces
	timebuf[13] = ' ';
	timebuf[14] = ' ';
	timebuf[15] = ' ';

	//initializes structs from ctrlregs.h
	PORTS = (volatile st_PORTS*)0xBF886040;
	INT = (volatile st_INT*)0xBF881000;
	TIMERS = (volatile st_TIMERS*)0xBF800600;
	SPI = (volatile st_SPI*)0xBF805800;
	ADC = (volatile st_ADC*)0xBF809000;
	OC = (volatile st_OC*)0xBF803000;
	IC = (volatile st_IC*)0xBF802000;
	CN = (volatile st_CN*)0xBF8861C0;

	//initialize shit
	display_init();
	ui_init();
	sd_init();
	FAT_init();
	sndio_init();
	enable_interrupts();

	while (1)
	{
		//checks which way to search for file
		if (readdirection)
		{
			file.entry += 32;
			FAT_findnextwavfile(FAT_FIRSTCLUS, &file);
			if (file.entry >= 512)
			{
				file.entry = -32;
				file.sector = 0;
				continue;
			}
		}
		else
		{
			file.entry -= 32;
			FAT_findprevwavfile(FAT_FIRSTCLUS, &file);
			if (file.entry <= -32)
			{
				file.entry = 512;
				file.sector = FAT_SECPERCLUS - 1;
				continue;
			}
		}

		//something is wrong with FAT_findprevfile. not going to waste time on it for now.
		if (!iswavfile(2, &file)) // DO NOT REMOVE: ESSENTIAL FOR HUMANITY'S EXISTENCE
			continue;

		//writes song name to screen
		spacemem(strbuf, 16);
		cpymem(sdblockbuffer + file.entry, strbuf, 8);
		display_string(0, strbuf);
		display_update();

		//finds the first cluster of the file and reads its first block
		player_currentcluster = (int)sdblockbuffer[file.entry + 26] | ((int)sdblockbuffer[file.entry + 27] << 8) | ((int)sdblockbuffer[file.entry + 20] << 16) | ((int)sdblockbuffer[file.entry + 21] << 24);
		sd_readblock(FAT_clusnumtoaddr(player_currentcluster));
		if (!parsewavheader())
			continue;

		//set samplerate and reset sound
		sndio_settings.sampleperiod = 80000000 / wavdata.samplerate;
		if (!sndio_reset())
			continue;

		//initializes the buttons to not work until the play loop is entered
		btn_last1 = 1;
		btn_last2 = 1;
		btn_last3 = 1;
		btn_last4 = 1;

		player_maxbyte = 512;
		player_currentbyte = 44;
		player_bytecount = 0;
		player_playing = 1;

		totalseconds = wavdata.size / wavdata.samplerate;
		timebuf[3] = ':';
		timebuf[6] = '/';
		dectostr(totalseconds / 60, timebuf + 7, 3);
		timebuf[10] = ':';
		dectostr(totalseconds % 60, timebuf + 11, 2);

		do
		{
			int currentseconds;

			//view time
			currentseconds = player_bytecount / wavdata.samplerate;
			dectostr(currentseconds / 60, timebuf, 3);
			dectostr(currentseconds % 60, timebuf + 4, 2);
			display_string(1, timebuf);
			display_update();

			//read cluster
			for (player_currentsector = 0; player_currentsector != FAT_SECPERCLUS; player_currentsector++)
			{
				//sample buttons
				btn_now1 = PORTS->F.PORT.BTN1;
				btn_now2 = PORTS->D.PORT.BTN.BTN2;
				btn_now3 = PORTS->D.PORT.BTN.BTN3;
				btn_now4 = PORTS->D.PORT.BTN.BTN4;

				if (player_playing)
				{
					//read sector
					sd_readblock(FAT_clusnumtoaddr(player_currentcluster) + player_currentsector);
					if (wavdata.size - player_bytecount < 512)
						player_maxbyte = wavdata.size - player_bytecount;
					for (; player_currentbyte != player_maxbyte; player_currentbyte++)
					{
						while (!sndbuf_write(sdblockbuffer[player_currentbyte]));
						player_bytecount++;
					}
					if (player_currentbyte != 512)
						goto endsong;
					player_currentbyte = 0;
				}
				else player_currentsector--;

				switch (btnmode)
				{
				case 0:
				{
					if (btn_now2 && !btn_last2)
					{
						goto endsong; //next song
					}
					if (btn_now3 && !btn_last3)
					{
						player_playing = !player_playing; //toggle pause/play
					}
					if (btn_now4 && !btn_last4)
					{
						readdirection = 0;
						goto dontsetsearchdir; //previous song
					}
				} break;
				case 1:
				{

				} break;
				default:
					break;
				}

				//change button mode
				if (btn_now1 && !btn_last1)
				{
					if (++btnmode == 2) btnmode = 0;

					spacemem(strbuf, 15);
					if (btnmode == 1) cpymem("LOCK", strbuf, 6);
					display_string(3, strbuf);
					display_update();
				}

				btn_last1 = btn_now1;
				btn_last2 = btn_now2;
				btn_last3 = btn_now3;
				btn_last4 = btn_now4;

			}
		nextcluster:

			//load the next cluster
			sd_readblock(FAT_FBA + (player_currentcluster / 128));
			fat_entryoffset = (player_currentcluster % 128) * 4;
			player_currentcluster = (int)sdblockbuffer[fat_entryoffset] | ((int)sdblockbuffer[fat_entryoffset + 1] << 8) |
				((int)sdblockbuffer[fat_entryoffset + 2] << 16) | ((int)sdblockbuffer[fat_entryoffset + 3] << 24);

		} while (player_currentcluster < 0xFFFFFFF8);
	endsong:
		readdirection = 1;
	dontsetsearchdir:

		//wait for song to stop playing
		while (snd_readpos != snd_writepos);

		continue;
	}

	return 0;
}

void ISR(void)
{
	if (INT->IFS.T2)
	{
		//did readpos catch up to writepos? dont read anything if so
		if (snd_readpos != snd_writepos)
		{
			unsigned char data = soundbuffer[snd_readpos & SOUNDBUFFERMASK]; //best buffer ever
			OC->OC2.RS = (int)(((float)sndio_settings.sampleperiod / 256) * (float)data);
			snd_readpos++;
		}
		INT->IFS.T2 = 0;
	}
}