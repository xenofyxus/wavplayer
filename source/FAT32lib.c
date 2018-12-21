#include "FAT32lib.h"
#include "sdhcio.h"
#include "ctrlregs.h"

//check if entry is pointing at .WAV file
int iswavfile(int cluster, DirEntryAddr* file)
{
	if (sdblockbuffer[file->entry] == 0xE5) //unused file?
		return 0;
	if (sdblockbuffer[file->entry + 11] & 0x10) //is directory?
		return 0;
	if ((sdblockbuffer[file->entry + 11] & 0xF) == 0xF) //is long name?
		return 0;
	if (sdblockbuffer[file->entry + 11] & 0xC0) //invalid type?
		return 0;
	if (!(sdblockbuffer[file->entry + 8] == 'W' && sdblockbuffer[file->entry + 9] == 'A' && sdblockbuffer[file->entry + 10] == 'V')) //not .WAV?
		return 0;
	return 1;
}

//search for a .WAV file
void FAT_findnextwavfile(int cluster, DirEntryAddr* file)
{
	for (; file->sector < FAT_SECPERCLUS; file->sector++)
	{
		sd_readblock(FAT_clusnumtoaddr(cluster) + file->sector);
		for (; file->entry < 512; file->entry += 32)
		{
			if (sdblockbuffer[file->entry] == 0x0)
			{
				file->entry = 512;
				return;
			}
			if (!iswavfile(cluster, file))
				continue;
			return;
		}
		file->entry = 0;
	}
	file->entry = 512;
}

//do findnextwavfile but backwards
void FAT_findprevwavfile(int cluster, DirEntryAddr* file)
{
	for (; file->sector >= 0; file->sector--)
	{
		sd_readblock(FAT_clusnumtoaddr(cluster) + file->sector);
		for (; file->entry >= 0; file->entry -= 32)
		{
			if (sdblockbuffer[file->entry] == 0x0)
				continue;
			if (!iswavfile(cluster, file))
				continue;
			return;
		}
		file->entry = 480;
	}
	file->entry = -32;
}

//find .WAV file that matches with name
DirEntryAddr FAT_findwavfile(int cluster, char* name)
{
	int i;
	DirEntryAddr file;
	file.entry = 0;
	file.sector = 0;
	do
	{
		FAT_findnextwavfile(cluster, &file);
		for (i = 0; i != 8; i++)
		{
			if (sdblockbuffer[file.entry + i] != name[i])
			{
				file.entry += 32;
				continue;
			}
		}
		break;
	} while (file.entry != 512);

	return file;
}

void FAT_init(void)
{
	sd_readblock(0x0); //read MBR
	FAT_LBA = (int)sdblockbuffer[454] | ((int)sdblockbuffer[455] << 8) | ((int)sdblockbuffer[456] << 16) | ((int)sdblockbuffer[457] << 24); //first partition start
	FAT_SECTORS = (int)sdblockbuffer[458] | ((int)sdblockbuffer[459] << 8) | ((int)sdblockbuffer[460] << 16); //sector count in the FAT

	sd_readblock(FAT_LBA); //read partition header
	FAT_SECPERCLUS = sdblockbuffer[13]; //sector count per file cluster
	FAT_FBA = FAT_LBA + ((int)sdblockbuffer[14] | ((int)sdblockbuffer[15] << 8)); //start address for FAT
	FAT_FATLEN = ((int)sdblockbuffer[36] | ((int)sdblockbuffer[37] << 8) | ((int)sdblockbuffer[38] << 16) | ((int)sdblockbuffer[39] << 24)); //length of each FAT
	FAT_CBA = FAT_FBA + (2 * FAT_FATLEN); //start address of file clusters
	FAT_FIRSTCLUS = (int)sdblockbuffer[44] | ((int)sdblockbuffer[45] << 8) | ((int)sdblockbuffer[46] << 16) | ((int)sdblockbuffer[47] << 24); //Root directory cluster number
}