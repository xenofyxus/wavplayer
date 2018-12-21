// TODO: make interrupt handler for outputting buffer data to the breakout
#include "ctrlregs.h"
#include "sndlib.h"

void sndio_init(void)
{
	sndio_settings.mic_loopback = 0;
	sndio_settings.output_on = 0;
	sndio_settings.volume_microphone = 127;
	sndio_settings.sampleperiod = 10000;

	// OC
	OC->OC2.CON.WORD = 0x0;

	OC->OC2.CON.OCM = 0x6;

	OC->OC2.CON.ON = 1;

	// Timer
	TIMERS->T2.CON.WORD = 0x0;
	TIMERS->T2.TMR = 0x0;

	// Interrupt
	INT->IPC.T2.IP = 0x7;

	// Settings
	sndio_reset();
}

//reset and check validity of samplerate
int sndio_reset(void)
{
	TIMERS->T2.CON.ON = 0;
	INT->IEC.T2 = 0;
	snd_writepos = 0;
	snd_readpos = 0;
	switch (sndio_settings.sampleperiod)
	{
		case 10000:
		case 5000:
		case 2500:
			break;
		default:
			return 0;
	}
	TIMERS->T2.PR = 2500;
	TIMERS->T2.TMR = 0x0;
	TIMERS->T2.CON.ON = 1;
	INT->IEC.T2 = 1;
	return 1;
}

//write a sample to the soundbuffer
int sndbuf_write(unsigned char data)
{
	if (snd_writepos - SOUNDBUFFERSIZE != snd_readpos)//make sure it doesn't catch up to readpos' relative position in the buffer
	{
		soundbuffer[snd_writepos & SOUNDBUFFERMASK] = data;
		snd_writepos++;
		return 1;
	}
	return 0;
}

int sndbuf_getfreespace(void)
{
	return SOUNDBUFFERSIZE - (snd_writepos - snd_readpos);
}
