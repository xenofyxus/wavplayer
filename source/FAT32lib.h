#ifndef FAT32LIB_H
#define FAT32LIB_H

#define DIR_ATTR_READ_ONLY      0x01
#define DIR_ATTR_HIDDEN         0x02
#define DIR_ATTR_SYSTEM         0x04
#define DIR_ATTR_VOLUME_ID      0x08
#define DIR_ATTR_DIRECTORY      0x10
#define DIR_ATTR_ARCHIVE        0x20
#define DIR_ATTR_LONG_NAME      0x0F
#define DIR_ATTR_LONG_NAME_MASK 0x3F

#define FAT_clusnumtoaddr(num) (FAT_CBA + ((num - 2) * FAT_SECPERCLUS))

typedef struct
{
	int sector;
	int entry;
} DirEntryAddr;

unsigned int FAT_LBA;
unsigned int FAT_SECTORS;
unsigned int FAT_SECPERCLUS;
unsigned int FAT_FBA;
unsigned int FAT_FATLEN;
unsigned int FAT_CBA;
unsigned int FAT_FIRSTCLUS;

void FAT_init(void);
void FAT_findnextwavfile(int cluster, DirEntryAddr* file);
int iswavfile(int cluster, DirEntryAddr* file);
DirEntryAddr FAT_findwavfile(int cluster, char* name);
void FAT_findprevwavfile(int cluster, DirEntryAddr* file);

#endif // FATLIB
