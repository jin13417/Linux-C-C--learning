#include <stdio.h>
int main()
{
  FILE *fp= fdopen(1,"W+");
  fprintf(fp,"%s\n","hell0");

}
