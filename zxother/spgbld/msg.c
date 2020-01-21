
#include "stdafx.h"

void print_help()
{
	printf(STR(SB_VER));
	printf("\n\n");
	printf("Build:	  spgbld -b <input.ini> <output.spg> [-c <pack method>] [-v]\n");
	printf("Unpack:	  spgbld -u <input.spg>\n");
	//printf("Info:	  spgbld -i <input.spg>\n");
	//printf("Re-build:  spgbld -r <input.spg> <output.spg> [-c <pack method>]\n");
	printf("\n");
}
