/*
  The test result:
  pqy@sda1:~/UNP/bin$ ./p108 
  x86_64-unknown-linux-gnu: little-end
 */


#include "unp.h"

int main(int argc, char **argv)
{
  union
  {
    short s;
    char c[sizeof(short)];
  } un;

  un.s = 0x0102;

  printf("%s: ", CPU_VENDOR_OS);
  if (sizeof(short) == 2)
    {
      if (un.c[0] == 1 && un.c[1] == 2)
	printf("big-end\n");
      
      else if (un.c[0] == 2 && un.c[1] == 1)
	printf("little-end\n");

      else
	printf("unknown\n");
    }

  else
    printf("size of short = %d\n", (int)sizeof(short));
  
  exit(0);
}
