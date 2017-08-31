#include <stdio.h>

int add(int x,int y);
int dec(int x,int y);
int mul(int x,int y);
int rem(int x,int y);
float div(int x,int y);
int main()
{
	int i,x,y;
	puts("input the number:");
	scanf("%d%d",&x,&y);
	int (*p[5])(int,int)={add,dec,mul,rem,div};
	char q[5][4]={"add","dec","mul","rem","div"};
	int a[5]={43,45,42,47,37};
	for(i=0;i<5;i++)
	{
		if(i<4)
	printf("%s:%d %c %d=%d\n",q[i],x,a[i],y,p[i](x,y));
		else
	printf("%s:%d %c %d=%f\n",q[i],x,a[i],y,((float (*)(int,int))p[i])(x,y));
	}
	return 0;
}
int add(int x,int y)
{
	return x+y;
}
int dec(int x,int y)
{
	return x-y;
}
int mul(int x,int y)
{
	return x*y;
}
int rem(int x,int y)
{
	return x%y;
}
float div(int x,int y)
{
	return (float)x/y;
}
