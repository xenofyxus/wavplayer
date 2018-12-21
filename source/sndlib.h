#ifndef SNDLIB_H
#define SNDLIB_H

#define SOUNDBUFFERSIZE 1024
#define SOUNDBUFFERMASK (SOUNDBUFFERSIZE - 1)

struct
{
	unsigned int output_on : 1;
	unsigned int volume_microphone : 7;
	unsigned int mic_loopback : 1;
	unsigned int sampleperiod;
} sndio_settings;

unsigned char soundbuffer[SOUNDBUFFERSIZE];
int snd_writepos;
int snd_readpos;

void sndio_init(void);
int sndio_reset(void);
int sndbuf_write(unsigned char data);
int sndbuf_getfreespace(void);

#endif // SNDLIB
