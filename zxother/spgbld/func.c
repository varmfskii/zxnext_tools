#include <ctype.h>
#include <unistd.h>
#include "stdafx.h"
#define false 0
#define true 1

extern HDR hdr;
extern BLK blk[256];
extern CONF conf;

int parse_arg(int argc, char* argv[], char* arg)
{
  for (int i = 1; i < argc; i++)
    if (!strcmp(argv[i], arg))
      return i + 1;

  return 0;
}

void parse_args(int argc, char* argv[])
{
  int i;
  conf.packer = PM_AUTO;
  conf.verbose = false;

  if (i = parse_arg(argc, argv, "-v"))
    conf.verbose = true;

  if (i = parse_arg(argc, argv, "-b"))
  {
    conf.mode = M_BLD;
    conf.in_fname = argv[i];
    conf.out_fname = argv[i+1];
    if (i = parse_arg(argc, argv, "-c"))
      conf.packer = (C_PACK)atoi(argv[i]);
    return;
  }
  else if (i = parse_arg(argc, argv, "-u"))
  {
    conf.mode = M_UNP;
    conf.in_fname = argv[i];
    return;
  }
  
  print_help();
  error(ARG);
}

void init_hdr()
{
  memset(&hdr, 0, sizeof(hdr));
  strncpy(hdr.magic, STR(SPG_MAGIC), sizeof(hdr.magic));
  strncpy(hdr.creator, STR(SB_CRT), sizeof(hdr.creator));
  hdr.ver = SPG_VER;
  hdr.subver = SPG_SUBVER;
  hdr.sp = SPG_SP;
  hdr.page3 = SPG_PAGE3;
  hdr.clk = SPG_CLK;
  hdr.ei = SPG_INT;
  hdr.pager = SPG_PGR;
  hdr.resid = SPG_RES;
  time_t t1 = time(NULL);
  struct tm* t2 = localtime(&t1);
  hdr.day = t2->tm_mday;
  hdr.month = t2->tm_mon + 1;
  hdr.year = t2->tm_year - 100;
  hdr.second = t2->tm_sec;
  hdr.minute = t2->tm_min;
  hdr.hour = t2->tm_hour;
}

u32 num(char *ns)
{
  int n;

  if ((ns[0] == '0') && ns[1] == 'x')
  {
    sscanf(ns, "%x", &n);
    return n;
  }

  if ((ns[0] == '#') || (ns[0] == '$'))
  {
    sscanf(ns + 1, "%x", &n);
    return n;
  }

  else
  {
    sscanf(ns, "%d", &n);
    return n;
  }
}

void load_ini(char *name)
{
  char t[256];
  char v[256];
  char v1[256];
  char v2[256];
  int a = 0;
  int b = 0;
    int nblk = 0;

  FILE* f = fopen(name, "rt");
  if (!f)
    error(INI);

  while (!feof(f))
  {
    *t = 0;
    fscanf(f, "%256[^ =\n\r\t]%*[ =]%256[^\n\r]%*c", t, v);
    if (!*t)
    {
      fscanf(f, "%*c");
      continue;
    }

    else if (t[0] == ';')
      continue;

    strlwr(t);

    // description string
    if (!strcmp(t, STR(F_DESC)))
    {
      strncpy(hdr.desc, v, 32);
      printf("Description:\t%s\n", v);
    }

    // stack address
    else if (!strcmp(t, STR(F_SP)))
    {
      hdr.sp = (u16)num(v);
      printf("SP:\t\t#%04X\n", hdr.sp);
    }

    // resident address
    else if (!strcmp(t, STR(F_RES)))
    {
      hdr.resid = (u16)num(v);
      printf("Resident at:\t#%04X\n", hdr.resid);
    }

    // pager address
    else if (!strcmp(t, STR(F_PAGER)))
    {
      hdr.pager = (u16)num(v);
      if (hdr.pager)
        printf("Pager at:\t#%04X\n", hdr.pager);
      else
        printf("Pager:\t\tNot used\n");
    }

    // start address
    else if (!strcmp(t, STR(F_START)))
    {
      hdr.start = (u16)num(v);
      printf("Start:\t\t#%04X\n", hdr.start);
    }

    // page3
    else if (!strcmp(t, STR(F_PAGE3)))
    {
      hdr.page3 = (u8)num(v);
      printf("Page #C000:\t#%02X\n", hdr.page3);
    }

    // clock
    else if (!strcmp(t, STR(F_CLOCK)))
    {
      hdr.clk = (u8)num(v);
      printf("Clock:\t\t");
      switch (hdr.clk)
      {
        case 0: { printf("3.5"); break; }
        case 1: { printf("7"); break; }
        case 2: { printf("14"); break; }
        case 3: { printf("14+"); break; }
      }
      printf(" MHz\n");
    }

    // INT
    else if (!strcmp(t, STR(F_INT)))
    {
      hdr.ei = num(v);
      printf("Interrupts:\t");
      if (hdr.ei)
        printf("EI\n");
      else
        printf("DI\n");
    }

    // compression
    else if (!strcmp(t, STR(F_CMP)))
    {
      conf.packer = (C_PACK)num(v);
      printf("Compression: \t%s\n", pack_txt[conf.packer + 1]);
    }

    // block
    else if (!strcmp(t, STR(F_BLK)))
    {
      int size;
      int offset = 0;

      sscanf(v, "%[^ ,\t]%*[ ,\t]%[^ ,\t]%*[ ,\t]%s", v1, v2, v);
      a = num(v1);
      b = num(v2);

      if (a & 0x1FF)
        error(ALGN);

      a &= 0x3FFF;

      printf("Block:\t\tStart: #%04X  Page: #%02X  File: %s\n", a, b, v);

      struct stat st;
      stat(v, &st);
      size = st.st_size;

      if (size < 0)
      {
        printf("%s: ", v);
        error(FNFD);
      }

      if (size == 0)
      {
        printf("%s: ", v);
        error(ZERO);
      }

      while (size)
      {
        int curr_size = min(size, 0x4000 - a);
        strncpy(blk[nblk].fname, v, sizeof(blk[nblk].fname));
        hdr.blk[nblk].addr = a >> 9;
        hdr.blk[nblk].page = b++;
        blk[nblk].offset = offset;
        blk[nblk].size = curr_size;
        blk[nblk].packer = conf.packer;

        a = 0;
        offset += curr_size;
        size -= curr_size;

        if (++nblk == 256)
          goto end_of_ini;
      }
    }

    // unknown tag
    else
    {
      printf("%s: ", t);
      error(UNK);
    }
  }

end_of_ini:
  if (!nblk)
    error(0BLK);

  conf.n_blocks = nblk;
  hdr.num_blk = conf.n_blocks;
  hdr.blk[conf.n_blocks - 1].last = 1;

  fclose(f);
}

void rand_name(char* name)
{
  for (int i=0; i<11; i++)
  {
    name[i] = 65 + (rand() & 15);
  }
  name[11] ='.', name[12] ='t', name[13] ='m', name[14] ='p', name[15] = 0;
}

void store_block(int i, char* fn, int s)
{
  memset(blk[i].data, 0, sizeof(blk[i].data));
  blk[i].size = s;
  hdr.blk[i].size = sz(blk[i].size);
  FILE* f = fopen(fn, "rb");
  fread(blk[i].data, 1, s, f);
  fclose(f);
}

void pack_blocks()
{
  struct stat st;
  int s1, s2, sz1, sz2;
  C_PACK p;

  for (int i = 0; i < conf.n_blocks; i++)
  {
    char f1n[16], f2n[16], f3n[16];
    char cmdl[256];
    rand_name(f1n); rand_name(f2n); rand_name(f3n);

    // add errors check here!!!
    FILE* f1 = fopen(f1n, "wb");
    fwrite(blk[i].data, 1, blk[i].size, f1);
    fclose(f1);

    s1 = s2 = 16384;
    sz1 = sz2 = 31;

    if ((blk[i].packer == PM_AUTO) || (blk[i].packer == PM_MLZ))
    {
      sprintf(cmdl, "mhmt -mlz %s %s", f1n, f2n);
      if (execl("/bin/sh", "sh", "-c", cmdl, NULL) < 0) error(MHMT);
      stat(f2n, &st); s1 = st.st_size; sz1 = sz(st.st_size);
    }

    if ((blk[i].packer == PM_AUTO) || (blk[i].packer == PM_HST))
    {
      sprintf(cmdl, "mhmt -hst %s %s", f1n, f3n);
      if (execl("/bin/sh", "sh", "-c", cmdl, NULL) < 0) error(MHMT);
      stat(f3n, &st); s2 = st.st_size; sz2 = sz(st.st_size);
    }

    remove(f1n);

    if (sz(blk[i].size) <= min(sz1, sz2))   // if unpacked chunk has the same size as packed, leave it unpacked
      p = PM_NONE;

    else
      p = (sz1 <= sz2) ? PM_MLZ : PM_HST;   // if MegaLZ gives the same chunk size as Hrust, use it as faster

    hdr.blk[i].comp = p;

    switch (p)
    {
      case PM_MLZ:
      {
        store_block(i, f2n, s1);
        break;
      }
      case PM_HST:
      {
        store_block(i, f3n, s2);
        break;
      }
    }

    remove(f2n); remove(f3n);
  }
}

void save_spg(char* name)
{
  FILE* f = fopen(name, "wb");

  // save header
  fwrite(&hdr, 1, sizeof(hdr), f);

  // save blocks
  for (int i = 0; i < conf.n_blocks; i++)
  {
    fwrite(&blk[i].data, 1, (hdr.blk[i].size + 1) << 9, f);
  }

  fclose(f);
}

void load_files()
{
  for (int i = 0; i < conf.n_blocks; i++)
  {
    FILE* f = fopen(blk[i].fname, "rb");
    if (!f) error(FNFD);

    hdr.blk[i].size = sz(blk[i].size);
      fseek(f, blk[i].offset, SEEK_SET);
    fread(blk[i].data, 1, blk[i].size, f);
    fclose(f);
  }
}

void unpack_spg(char* name)
{
  char fu[1024];
  char fa[1024];
  char fa1[1024];
  sprintf(fa, "%s", name);

  // Read input SPG
  FILE* f = fopen(name, "rb");
  if (!f) error(FERR);

  struct stat st;
  stat(name, &st);
  void *fbuf = malloc(st.st_size);

  if (!fbuf)
    error(MALC);

  fread(fbuf, 1, st.st_size, f);
  fclose(f);

  // Create INI
  sprintf(fu, "%s.ini", name);
  f = fopen(fu, "wt");
  if (!f) error(FERR);

  HDR *hdr = (HDR*)fbuf;
  fprintf(f, "Desc = %s\n", hdr->desc);
  fprintf(f, "Start = 0x%0X\n", hdr->start);
  fprintf(f, "Stack = 0x%0X\n", hdr->sp);
  fprintf(f, "Resident = 0x%0X\n", hdr->resid);
  fprintf(f, "Page3 = %u\n", hdr->page3);
  fprintf(f, "Clock = %u\n", hdr->clk);
  fprintf(f, "INT = %u\n", hdr->ei);
  fprintf(f, "Pager = 0x%0X\n", hdr->pager);

  int nblk;
  for (int i = 0; i < hdr->num_blk; i++)
  {
    fprintf(f, "Block = 0x%0X, %u, %s.%03u\n", hdr->blk[i].addr * 512 + 0xC000, hdr->blk[i].page, fa, i);
    nblk = i + 1;
    // if (hdr->blk[i].last) break;
  }

  fclose(f);

  // Save files
  u8 *data = (u8*)fbuf + sizeof(HDR);

  for (int i = 0; i < nblk; i++)
  {
    int size = (hdr->blk[i].size + 1) * 512;
    void *addr = data;
    data += size;

    if (hdr->blk[i].comp == PM_NONE)
    {
      sprintf(fu, "%s.%03u", name, i);
      f = fopen(fu, "wb");
    }

    else
    {
      rand_name(fa);
      sprintf(fa1, "%s.%03u", name, i);
      f = fopen(fa, "wb");
    }

    if (!f) error(FERR);
    fwrite(addr, 1, size, f);
    fclose(f);

    if (hdr->blk[i].comp != PM_NONE)
    {
      switch (hdr->blk[i].comp)
      {
        case PM_MLZ:
          if (execl("mhmt", "dummy", "-d", "-mlz", fa, fa1, NULL) < 0) error(MHMT);
        break;

        case PM_HST:
          if (execl("mhmt", "dummy", "-d", "-hst", fa, fa1, NULL) < 0) error(MHMT);
        break;
      }

      remove(fa);
    }
  }

  free(fbuf);
}

char *strlwr(char *s) {
  int i;
  for(i=0; s[i]; i++) s[i]=tolower(s[i]);
  return s;
}
  
