#include <stdio.h>

void main (int argc, char *argv[])
  {
  FILE *fd, *fd1;
  unsigned char ulawChar;
  unsigned int ulawInt;
  int linearPCMInt;
  short linearPCMShort;
  int i,n = 0;

  fd = fopen (argv[2], "rb");
  if(fd==NULL)
    {
    printf("error: cannot open source_file\n");
    exit(1);
    }
  fd1 = fopen (argv[3], "wb");
  if(fd1==NULL)
    {
    printf("error: cannot open destination_file\n");
    exit(1);
    }

  if( (*argv[1]=='-') && (*(argv[1]+1) == 'u') )
    {
    while(1)
      { 
      i = fscanf(fd, "%u", &ulawInt);
      if(i != 1)
        {
        printf("ulaw file size: %d elements\n",n);
        fclose(fd);
        fclose(fd1);
        exit(1);
        }
      n++;
      ulawChar = (unsigned char) ulawInt;
      fwrite(&ulawChar, sizeof(unsigned char), 1, fd1);
      }
    }

  if( (*argv[1]=='-') && (*(argv[1]+1) == 'p') )
    {
    while(1)
      {
      i = fscanf(fd, "%d", &linearPCMInt);
      if(i != 1)
        {
        printf("linearPCM file size: %d elements\n",n);
        fclose(fd);
        fclose(fd1);
        exit(1);
        }
      n++;
      linearPCMShort = (short)linearPCMInt;
      fwrite(&linearPCMShort, sizeof(short), 1, fd1);
      }
    }

  }
