#include <stdio.h>

void main (int argc, char *argv[])
  {
  FILE *fdNew, *fdOrg1, *fdOrg2;
  int num1, num2, flag1, flag2, n = 0;

  /*
   * Check if number of arguments is correct
   */

  if(argc!=4)
    {
    printf("usage: mesher lowerSB_file higherSB_file destfile\n");
    exit(1);
    }

  /*
   * Open source and destination files
   */

  fdOrg1 = fopen (argv[1], "r");
  if(fdOrg1==NULL)
    {
    printf("mesher: cannot open lowerSB_file\n");
    exit(1);
    }

  fdOrg2 = fopen (argv[2], "r");
  if(fdOrg2==NULL)
    {
    printf("mesher: cannot open higherSB_file\n");
    exit(1);
    }

  fdNew = fopen (argv[3], "w");
  if(fdNew==NULL)
    {
    printf("mesher: cannot open destination file\n");
    exit(1);
    }

  /*
   * merge the two files into one
   */

  while(1)
    {
    flag1 = fscanf(fdOrg1, "%d", &num1);
    flag2 = fscanf(fdOrg2, "%d", &num2);
    if(flag1 != 1 || flag2 != 1)
      {
      printf("destination file size: %d elements\n",n);
      fclose(fdOrg1);
      fclose(fdOrg2);
      fclose(fdNew);
      exit(1);
      }
    n += 2;
    fprintf(fdNew, "%d\n", num1);
    fprintf(fdNew, "%d\n", num2);
    }
  }
