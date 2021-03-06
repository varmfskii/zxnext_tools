
#include "stdafx.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "tsspiffs.h"
#include <getopt.h>
#include <stdint.h>

#define SPI_SIZE (4096 * 1024)
#define BLK_SIZE 4096

uint8_t buf[256];

char *img_name;
char *add_name;
uint32_t spi_size;
uint32_t blk_size;
uint8_t *mem = 0;
int is_debug = 0;

TSF_CONFIG cfg;
TSF_VOLUME vol;
TSF_FILE file;

TSF_RESULT spi_read(uint32_t addr, void *buf, uint32_t size)
{
  if (is_debug) printf("spi_read: %08X, %u\n", addr, size);
  memcpy(buf, &mem[addr], size);
  return TSF_RES_OK;
}

TSF_RESULT spi_write(uint32_t addr, const void *buf, uint32_t size)
{
  if (is_debug) printf("spi_write: %08X, %u\n", addr, size);
  memcpy(&mem[addr], buf, size);
  return TSF_RES_OK;
}

TSF_RESULT spi_erase(uint32_t addr)
{
  if (is_debug) printf("spi_erase: %08X, %u\n", addr, BLK_SIZE);
  memset(&mem[addr], 255, BLK_SIZE);
  return TSF_RES_OK;
}

void img_read()
{
  FILE *fp = fopen(img_name, "rb");

  if (fp)
  {
    fread(mem, 1, spi_size, fp);
    fclose(fp);
  }
}

void img_write()
{
  FILE *fp = fopen(img_name, "wb");

  if (fp)
  {
    fwrite(mem, 1, spi_size, fp);
    fclose(fp);
  }
}

void img_config()
{
  cfg.hal_read_func  = spi_read;
  cfg.hal_write_func = spi_write;
  cfg.hal_erase_func = spi_erase;

  cfg.buf = buf;
  cfg.buf_size = sizeof(buf);

  cfg.bulk_start = 0;
  cfg.bulk_size = spi_size;
  cfg.block_size = blk_size;
}

void img_create()
{
  mem = (uint8_t*)malloc(spi_size);

  tsf_format(&cfg);

  img_write();
  free(mem);
}

void img_add()
{
  mem = (uint8_t*)malloc(spi_size);
  img_read();

  FILE *fp = fopen(add_name, "rb");
  if(!fp) return;

  fseek(fp, 0 , SEEK_END);
  int fsize = ftell(fp);
  fseek(fp, 0 , SEEK_SET);

  uint8_t *buf = (uint8_t*)malloc(fsize);
  fread(buf, 1, fsize, fp);
  fclose(fp);

  tsf_mount(&cfg, &vol);
  tsf_open(&vol, &file, add_name, TSF_MODE_CREATE_WRITE);
  tsf_write(&file, buf, fsize);
  tsf_close(&file);

  free(buf);

  img_write();
  free(mem);
}

void img_list()
{
  mem = (uint8_t*)malloc(spi_size);
  img_read();

  tsf_mount(&cfg, &vol);
  tsf_list(&vol, TSF_LIST_START);
  
  while (tsf_list(&vol, TSF_LIST_NEXT) == TSF_RES_OK)
  {
    TSF_FILE_STAT stat;
    char name[256];
    sprintf(name, "%s", cfg.buf);
    tsf_stat(&vol, &stat, name);
    printf("%u\t%s\n", stat.size, name);
  }
  
  printf("\nFiles: %u\n", vol.files_number);
  printf("Free:  %u bytes\n", vol.free);
  
  free(mem);
}

void img_free()
{
}

void img_delete()
{
}

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    printf("SPIFFS utility\n");
    printf("\nUsage:\n");
    printf("spiffs.exe <options> <operations>\n");
    printf("\nOptions:\n");
    printf(" i <filename> - new or existing image filename\n");
    printf(" s <size> - image size in kB\n");
    printf(" b <size> - block size in kB\n");
    printf("\nOperations (sequence of a few is allowed):\n");
    printf(" c - create new image\n");
    printf(" a <filename> - add a file to image\n");
    printf(" l - list files\n");
    printf(" f - get free space in bytes\n");
    printf("\nExample:\n");
    printf("spiffs.exe -i spif.img -s 4096 -c -a conf.rbf -a ts.mlz\n");
    exit(1);
  }

  spi_size = SPI_SIZE;
  img_name = "new.img";
  img_config();

  int c = 0;
  while ((c = getopt (argc, argv, "i:cs:b:a:l")) != -1)
    switch(c)
    {
      // image name
      case 'i':
        img_name = optarg;
      break;

      // image size
      case 's':
        spi_size = atoi(optarg) * 1024;
        img_config();
      break;

      // block size
      case 'b':
        blk_size = atoi(optarg) * 1024;
        img_config();
      break;

      // create new image
      case 'c':
        img_create();
      break;

      // list files
      case 'l':
        img_list();
      break;

      // get free space
      case 'f':
        img_free();
      break;

      // add a file
      case 'a':
        add_name = optarg;
        img_add();
      break;

      default:
        exit(2);
    }

  return 0;
}
