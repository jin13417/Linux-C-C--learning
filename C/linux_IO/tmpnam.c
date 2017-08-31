#include <stdio.h>
int main()
{
	char *path;
	int i;
	for(i=0;i<2000;i++)
	{
		path = tmpnam(NULL);
//		printf("%s\n",path);
		FILE *fp = fopen(path,"w+");
		if(NULL == fp)
		{

			printf("%d\n",i);
			return -1;
		}

	}
	return 0;
}

