#include <stdlib.h>

int main()
{
  char *pchar_malloc;
  char *pchar_new;

  pchar_malloc = (char *)malloc(10);
  pchar_new = new char[7];

  if (pchar_malloc != NULL){
    free(pchar_malloc);
    pchar_malloc = NULL;
  }

  if (pchar_new != NULL){
    delete [] pchar_new;
    pchar_new = NULL;
  }

  return 0;
}
