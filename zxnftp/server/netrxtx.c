int netrx(char *p) {
  return 0xbeef;
}

void nettx(char *p, int n) {
  *(p++)=n&0xff;
  *p=n>>8;
}
