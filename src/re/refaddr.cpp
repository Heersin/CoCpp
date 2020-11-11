
int incsrc(int &src, int inc);
int decsrc(int src, int dec);

int main()
{
  int origin;

  origin = 0;
  int &origin_ref = origin;

  incsrc(origin, 3);
  decsrc(origin_ref, 5);

  return 0;
}

int incsrc(int &src, int inc)
{
  src += inc;
  return 0;
}

int decsrc(int src, int dec)
{
  src -= dec;
  return 0;
}
