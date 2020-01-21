// fsplit.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include "stdafx.h"
#include <string.h>

#define MAX_SPLIT 100

char *itoa(int, char *, int);

int main(int argc, char* argv[]) {
	if ((argc < 3) || (argc > (MAX_SPLIT + 2)))
	{
		printf("File splitter by TS-Labs\n");
		printf("Usage: fsplit <input> <piece 1 size> .. <piece N size>\n");
		return 1;
	}

	FILE* f_in = fopen (argv[1], "rb");
	if (!f_in)
	{
		printf ("Input file error!");
		return 1;
	}

    struct stat st;
    stat(argv[1], &st);
    int sz = st.st_size;
    void *buf = malloc(sz);
    if (!buf)
    {
        printf ("Memory alloc error!");
        return 3;
    }

    int ssz[MAX_SPLIT];
    int n = (argc - 2);
    for (int i = 0; i < n; i++)
    {
        ssz[i] = min(sz, atoi(argv[i + 2]));
        sz -= ssz[i];
        if (!sz)
            break;
    }
        
    if (sz)
        ssz[n++] = sz;

    for (int i = 0; i < n; i++)
	{
        char fout[256];
        char t[256];
        strcpy(fout, argv[1]);
        strcat(fout, ".");
        strcat(fout, itoa(i, t, 10));

        FILE *f_out = fopen(fout, "wb");
        if (!f_out)
        {
            printf ("Output file error!");
            return 2;
        }

        if (fread(buf, 1, ssz[i], f_in) != ssz[i])
        {
            printf ("Read file error!");
            return 4;
        }

        if (fwrite(buf, 1, ssz[i], f_out) != ssz[i])
        {
            printf ("Write file error!");
            return 5;
        }

        fclose(f_out);
    }

    fclose(f_in);

    printf("DONE!\n");

	return 0;
}

