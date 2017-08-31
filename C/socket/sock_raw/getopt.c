#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc,char *argv[])
{
	int ch,aflag = 0,bflag = 0,lflag =0; 
      int i;
	while((ch = getopt(argc,argv,"lab:")) != -1)
	{
		switch (ch)
		{
		case 'a':
			printf("option a is set\n");
			aflag = 1;
			break;
		case 'l':
			printf("option l is set\n");
			lflag = 1;
			break;
		case 'b':
			printf("option b is set");
			printf("b:%s\n",optarg);
			bflag =1;
			break;
		default:
			printf("option %c is not set\n",optopt);
			break;
		}
	}
	  for(i=0; i< argc;i++)
	  {
		  printf("%s ",argv[i]);
	  }
	  puts("");

	  return 0;
}


