#include <stdio.h>
#include <string.h>
#define N 3

int add(int ,int y);
int del(int ,int y);
int mul(int ,int y);
float div(int ,int y);

int main()
{

	int x = 10,y = 20;
	printf("%d + %d = %d\n",x,y,add(x,y));
	printf("%d - %d = %d\n",x,y,del(x,y));
	printf("%d * %d = %d\n",x,y,mul(x,y));
	printf("%d / %d = %.2f\n",x,y,div(x,y));
	return 0;
}

int add(int x ,int y)
{
	return x + y;
}
int del(int x,int y)
{
	return x - y;
}
int mul(int x,int y)
{
	return x * y;
}
float div(int x,int y)
{
	return x / (float)y;
}

