#include <stdio.h>
//从文件1.c中有效读入2个整数，并讲结果输出到out.c中，屏幕上不会输出2个的和；
int main()
{
	freopen("./1.c","r",stdin);
	freopen("./out.c","w",stdout);
	int a,b;
	while(scanf("%d%d",&a,&b) != EOF)
		printf("%d\n",a+b);
	fclose(stdin);
	fclose(stdout);
	return 0;
}


