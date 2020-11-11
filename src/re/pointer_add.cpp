int main()
{
  int *p;
  char *pstr;
  char str[5] = {'a', 'b', 'c', 'd', 'e'};

  p = (int *)str;
  pstr = (char *)str;

  p += 1;
  pstr += 1;

  return 0;
}
