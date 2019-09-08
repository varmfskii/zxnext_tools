#include <stdio.h>

int main() {
  int r, g, b;

  puts("P3\n32 32\n7");
  for(b=0; b<8; b++)
    for(g=0; g<8; g++) {
      for(r=0; r<8; r++)
	printf("%d %d %d %d %d %d ", r, g, b, r, g, b);
      if (g&3==3) putchar('\n');
    }
  return 0;
}
