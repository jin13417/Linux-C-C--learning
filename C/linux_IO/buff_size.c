#include <stdio.h>
#define M 0
#define N 1
//测试缓存区大小，341*3+1=1024；
int main()
{
#if M
	int i = 0;
	for ( i = 0; i < 379; i++)//每次向缓存写三个字符；
	{
		if (i >= 100)
			fprintf(stdout,"%d",i);
		else
			if (i >= 10)
				fprintf(stdout,"0%d",i);
			else
				if (i >= 0)
					fprintf(stdout,"00%d",i);
	}
	while(1);//强制执行，如果取消，程序结束时将会输出所有字符，看不到效果
#endif
#if N
	int i = 0;
	for(i = 0; i < 400;i++)
		fprintf(stdout,"%03d",i);
	while(1);
#endif

}
