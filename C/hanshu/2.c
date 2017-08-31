#include <stdio.h>

int sum(int);
int main()
{
  int z,b;
  z=sum(100);
  printf("%d\n",z);
  b=sum1(100);
  printf("%d\n",z);
	return 0;

}
int sum(int x)
{
	if(x<=0)
		return 0;
	return x+sum(x-1);
}
int sum1(int x)
{
	int i,sum=0;
	for(i=0;i<=x;i++)
		sum+=i;
	return sum;
}

