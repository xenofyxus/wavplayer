#ifndef SDHCIO_H
#define SDHCIO_H

#define UNIMPL(x) unsigned : x
#define SDBLOCKSIZE 512

unsigned char *sdblockbuffer;
void sd_init(void);
void sd_readblock(unsigned int address);

#endif // SDIO
