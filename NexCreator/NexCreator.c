#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NexCreator.h"

FILE *fin1;
FILE *fin2;
FILE *fout;
int line = 0;
int filecount = 0;
char *ptr = NULL;
int bank = 0;
int lastBank = -1;
int address = 0;
long long filelen;
int fileadded = 0;
int palcnt;
int versionDecimal = 11; // 11 = 1.1, 12 = 1.2, etc

HEADER header512 = {
    "Next",
    "V1.1",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    { 0 },
    0,
    0,
    0,
    0,
    0,
    { 0,0,0 },
    0,
    0
};

EXTRAFILE extrafiles[65536];		// enough room for 65536 extra files
unsigned char tempHeader[0x36];
unsigned char tempPalette[256 * 4];
unsigned char dontSavePalette = 0;
unsigned short palette[256];
unsigned char loading[49152];
unsigned char loadingULA[6144 + 768 + 256];
unsigned short paletteLoRes[256];
unsigned char loadingLoRes[6144 + 6144];
unsigned char loadingHiRes[6144 + 6144 + 768 + 256];
unsigned char loadingHiCol[6144 + 6144];
int HiResColour = 0;
unsigned char bigFile[1024 * 1024 * 1024];
unsigned char temp16k[16384];
char inputLine[4096];
char filename[1024];
unsigned char SNAHeader[27];
unsigned char SNA128Header[4] = { 0,0,0,0 };
unsigned char SNABank[8] = { 1,1,1,1,1,1,1,1 };

int main(int c, char **s)
{
  int i;
  if (c != 3)
    {
      printf("Nex File Creator\nUsage :- \nNexCreator source.txt dest.big\n\n");
      return(1);
    }
  fin1 = fopen(s[1], "rt");
  if (fin1 == NULL)
    {
      printf("Can't open '%s'\n", s[1]);
      return(1);
    }
  line = 0;
  filecount = 0;
  bank = 0;
  address = 0;
  while (!feof(fin1))
    {
      memset(inputLine, 0, sizeof(inputLine));
      fgets(inputLine, sizeof(inputLine), fin1);
      if (strlen(inputLine)>0)
        {
	  if (inputLine[strlen(inputLine) - 1] == 10)	inputLine[strlen(inputLine) - 1] = 0;
	  if (strlen(inputLine)>0)
            {
	      if (inputLine[strlen(inputLine) - 1] == 13)	inputLine[strlen(inputLine) - 1] = 0;
            }
        }
      line++;
      if (inputLine[0] == '!')
        {
	  if (((inputLine[1] & 0xdf) == 'C') && ((inputLine[2] & 0xdf) == 'O') && ((inputLine[3] & 0xdf) == 'R'))
            {
	      ptr = &inputLine[4];
	      header512.CoreRequired[CORE_MAJOR] = getInt();		//Loading bar off=0/on=1
	      if (ptr[0] == ',')
                {
		  ptr++;
		  header512.CoreRequired[CORE_MINOR] = getInt();	//Loading bar Layer2 index colour
		  if (ptr[0] == ',')
                    {
		      ptr++;
		      header512.CoreRequired[CORE_SUBMINOR] = getInt();	//Delay after each bank
                    }
                }
	      printf("Requires Core %d,%d,%d or greater\n", header512.CoreRequired[CORE_MAJOR], header512.CoreRequired[CORE_MINOR], header512.CoreRequired[CORE_SUBMINOR]);
            }
	  else if (((inputLine[1] & 0xdf) == 'B') && ((inputLine[2] & 0xdf) == 'M') && ((inputLine[3] & 0xdf) == 'P'))
            {
	      ptr = &inputLine[4];
	      skipSpace();
	      if (ptr[0] == '!')
                {
		  ptr++;
		  dontSavePalette = 1;
                }
	      if (ptr[0] == '8')
                {
		  ptr++;
		  use8BitPalette = 1;
		  if (ptr[0] == ',')
                    {
		      ptr++;
                    }
                }
	      getString(filename, sizeof(filename));
	      if (ptr[0] == ',')
                {
		  ptr++;
		  header512.BorderColour = getInt();
                }
	      fin2 = fopen(filename, "rb");
	      if (fin2 != NULL)
                {
		  fread(tempHeader, 1, 0x36, fin2);
		  fread(tempPalette, 4, 256, fin2);
		  for (i = 0; i < 256; i++)
                    {
		      palette[i] = ((convert8BitTo3Bits(tempPalette[i * 4 + 0]) >> 2 & 1) << 8) + (convert8BitTo3Bits(tempPalette[i * 4 + 0]) >> 1) + (convert8BitTo3Bits(tempPalette[i * 4 + 1]) << 2) + (convert8BitTo3Bits(tempPalette[i * 4 + 2]) << 5);
		      if (use8BitPalette != 0)	palette[i] &= 255;
                    }
		  i = tempHeader[11] * 256 + tempHeader[10];
		  fseek(fin2, (long int)i, SEEK_SET);
		  for (i = 0; i < 192; i++)
                    {
		      if (tempHeader[25] < 128)
                        {
			  fread(&loading[(191 - i) * 256], 1, 256, fin2);
                        }
		      else
                        {
			  fread(&loading[i * 256], 1, 256, fin2);
                        }
                    }
		  fclose(fin2);
		  header512.LoadingScreen |= 1 + (dontSavePalette ? 128 : 0);
		  printf("Loading Screen '%s'\n", filename);
		  fileadded = 1;
		  if (ptr[0] == ',')
                    {
		      ptr++;
		      header512.loadingBar = getInt();		//Loading bar off=0/on=1
		      if (ptr[0] == ',')
                        {
			  ptr++;
			  header512.loadingColour = getInt();	//Loading bar Layer2 index colour
			  if (ptr[0] == ',')
                            {
			      ptr++;
			      header512.loadingBankDelay = getInt();	//Delay after each bank
			      if (ptr[0] == ',')
                                {
				  ptr++;
				  header512.loadedDelay = getInt();		//Delay (frames) after loading before running
                                }
                            }
                        }
                    }
                }
	      if (ptr[0] == ',')
                {
		  ptr++;
		  HiResColour = getInt();
                }
            }
	  else if (((inputLine[1] & 0xdf) == 'S') && ((inputLine[2] & 0xdf) == 'C') && ((inputLine[3] & 0xdf) == 'R'))
            {
	      ptr = &inputLine[4];
	      getString(filename, sizeof(filename));
	      fin2 = fopen(filename, "rb");
	      if (fin2 != NULL)
                {
		  fread(&loadingULA[0], 1, 6144 + 768, fin2);
		  fclose(fin2);
		  header512.LoadingScreen |= 2;
		  printf("Loading Screen '%s'\n", filename);
		  fileadded = 1;
                }
	      else
                {
		  printf("Can't find '%s'\n", filename);
                }
            }
	  else if (((inputLine[1] & 0xdf) == 'S') && ((inputLine[2] & 0xdf) == 'L') && ((inputLine[3] & 0xdf) == 'R'))
            {
	      ptr = &inputLine[4];
	      getString(filename, sizeof(filename));
	      fin2 = fopen(filename, "rb");
	      if (fin2 != NULL)
                {
		  fread(tempHeader, 1, 0x36, fin2);
		  fread(tempPalette, 4, 256, fin2);
		  for (i = 0; i < 256; i++)
                    {
		      paletteLoRes[i] = ((convert8BitTo3Bits(tempPalette[i * 4 + 0]) >> 2 & 1) << 8) + (convert8BitTo3Bits(tempPalette[i * 4 + 0]) >> 1) + (convert8BitTo3Bits(tempPalette[i * 4 + 1]) << 2) + (convert8BitTo3Bits(tempPalette[i * 4 + 2]) << 5);
                    }
		  i = tempHeader[11] * 256 + tempHeader[10];
		  fseek(fin2, (long int)i, SEEK_SET);
		  for (i = 0; i < 96; i++)
                    {
		      if (tempHeader[25] < 128)
                        {
			  fread(&loadingLoRes[(95 - i) * 128], 1, 128, fin2);
                        }
		      else
                        {
			  fread(&loadingLoRes[i * 128], 1, 128, fin2);
                        }
                    }
		  fclose(fin2);
		  header512.LoadingScreen |= 4;
		  printf("Loading Screen '%s'\n", filename);
		  fileadded = 1;
                }
	      else
                {
		  printf("Can't find '%s'\n", filename);
                }
            }
	  else if (((inputLine[1] & 0xdf) == 'S') && ((inputLine[2] & 0xdf) == 'H') && ((inputLine[3] & 0xdf) == 'R'))
            {
	      ptr = &inputLine[4];
	      getString(filename, sizeof(filename));
	      fin2 = fopen(filename, "rb");
	      if (fin2 != NULL)
                {
		  fread(&loadingHiRes[0], 1, 6144 + 6144, fin2);
		  fclose(fin2);
		  header512.LoadingScreen |= 8;
		  printf("Loading Screen '%s'\n", filename);
		  fileadded = 1;
		  if (ptr[0] == ',')
                    {
		      header512.HiResColours = getInt();
                    }
                }
	      else
                {
		  printf("Can't find '%s'\n", filename);
                }
            }
	  else if (((inputLine[1] & 0xdf) == 'S') && ((inputLine[2] & 0xdf) == 'H') && ((inputLine[3] & 0xdf) == 'C'))
            {
	      ptr = &inputLine[4];
	      getString(filename, sizeof(filename));
	      fin2 = fopen(filename, "rb");
	      if (fin2 != NULL)
                {
		  fread(&loadingHiCol[0], 1, 6144 + 6144, fin2);
		  fclose(fin2);
		  header512.LoadingScreen |= 16;
		  printf("Loading Screen '%s'\n", filename);
		  fileadded = 1;
                }
            }
	  else if (((inputLine[1] & 0xdf) == 'P') && ((inputLine[2] & 0xdf) == 'C') && ((inputLine[3] & 0xdf) == 'S') && ((inputLine[4] & 0xdf) == 'P'))
            {
	      ptr = &inputLine[5];
	      header512.PC = getInt();
	      printf("PC=$%04x\n", header512.PC);
	      if (ptr[0] == ',')
                {
		  ptr++;
		  header512.SP = getInt();
		  printf("SP=$%04x\n", header512.SP);
		  if (ptr[0] == ',')
                    {
		      ptr++;
		      // This is a v1.2+ feature. Version number is only incremented if this token is parsed and the bank is > 0
		      header512.EntryBank = getInt();
		      if (header512.EntryBank > 0 && versionDecimal < 12)
                        {
			  versionDecimal = 12;
			  memcpy(header512.VersionNumber, "V1.2", 4);
			  printf("Entry Bank=%d\n", header512.EntryBank);
                        }
                    }
                }
            }
	  else if (((inputLine[1] & 0xdf) == 'M') && ((inputLine[2] & 0xdf) == 'M') && ((inputLine[3] & 0xdf) == 'U'))
            {
	      int bank8k, address8k;
	      ptr = &inputLine[4];
	      getString(filename, sizeof(filename));
	      if (ptr[0] == ',')
                {
		  ptr++;
		  bank8k = getInt();
		  bank = bank8k / 2;
		  if (ptr[0] == ',')
                    {
		      ptr++;
		      address = getHex();
		      address8k = address;
		      if (bank8k != (bank * 2)) address += 0x2000;
                    }
                }
	      printf("File '%s' 8K bank %d, %04x (16K bank %d, %04x)\n", filename, bank8k, address8k, bank, address);
	      addFile(filename);
            }
	  else if (((inputLine[1] & 0xdf) == 'B') && ((inputLine[2] & 0xdf) == 'A') && ((inputLine[3] & 0xdf) == 'N') && ((inputLine[4] & 0xdf) == 'K'))
            {
	      // This is a v1.2+ feature. Version number is only incremented if this token is parsed and the bank is > 0
	      ptr = &inputLine[5];
	      header512.EntryBank = getInt();
	      if (header512.EntryBank > 0 && versionDecimal < 12)
                {
		  versionDecimal = 12;
		  memcpy(header512.VersionNumber, "V1.2", 4);
		  printf("Entry Bank=%d\n", header512.EntryBank);
                }
            }
        }
      else if (inputLine[0] != ';' && inputLine[0] != 0)
        {
	  ptr = inputLine;
	  getString(filename, sizeof(filename));
	  if (ptr[0] == ',')
            {
	      ptr++;
	      bank = getInt();
	      if (ptr[0] == ',')
                {
		  ptr++;
		  address = getHex();
                }
            }
	  printf("File '%s' 16K bank %d, %04x\n", filename, bank, address);
	  for (int i = 0; i < 8; i++)
            {
	      if (ptr[0] == ',')
                {
		  ptr++;
		  SNABank[i] = getInt();
		  //printf("SNABank[%d]=%d\n", i, SNABank[i]);
                }
	      else break;
            }
	  addFile(filename);
        }
      //		printf("line %d='%s'\n",line,inputLine);
    }
  fclose(fin1);
  if ((lastBank>-1) || (fileadded != 0))
    {
      printf("Generating NEX file in %s format\n", header512.VersionNumber);
      for (i = 0; i < 64 + 48; i++)
        {
	  if (header512.Banks[i] > 0) header512.NumBanksToLoad++;
	  if (i >= 48) header512.RAM_Required = 1;
        }
      fout = fopen(s[2], "wb");
      if (fout == NULL)
        {
	  printf("Can't open '%s'\n", s[2]);
	  return(1);
        }
      fwrite(&header512, 1, 512, fout);
      if (header512.LoadingScreen)
        {
	  if (header512.LoadingScreen & 1)
            {
	      if (!(header512.LoadingScreen & 128))	fwrite(palette, 2, 256, fout);
	      fwrite(loading, 256, 192, fout);
            }
	  if (header512.LoadingScreen & 2)
            {
	      fwrite(loadingULA, 1, 6144 + 768 + 256, fout);
            }
	  if (header512.LoadingScreen & 4)
            {
	      if (!(header512.LoadingScreen & 128))	fwrite(paletteLoRes, 2, 256, fout);
	      fwrite(loadingLoRes, 1, 6144 + 6144, fout);
            }
	  if (header512.LoadingScreen & 8)
            {
	      fwrite(loadingHiRes, 1, 6144 + 6144, fout);
            }
	  if (header512.LoadingScreen & 16)
            {
	      fwrite(loadingHiCol, 1, 6144 + 6144, fout);
            }
        }
      for (i = 0; i<112; i++)
        {
	  if (header512.Banks[getBankOrder(i)])
            {
	      fwrite(&bigFile[i * 16384], 1, 16384, fout);
            }
        }
      fclose(fout);
    }
}
