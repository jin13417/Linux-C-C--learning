/*************************************************************************
 > File Name: countDigitOne.c
 > Author:  jinshaohui
 > Mail:    jinshaohui789@163.com
 > Time:    18-09-10
 > Desc:    
 ************************************************************************/
#include<stdio.h>

int countDigitOne(int n)
{
	int digit = 1;
	int high = 0;
	int low = 0;
	int cur = 0;
	int count = 0;

#if 0
	while((n/digit) != 0)
	{
		high = n/(digit*10);
		low = n - n/digit*digit;
		cur = (n/digit)%10;

		if (cur == 0)
		{
			count += high*digit;
		}
		else if (cur ==1)
		{
			count += high*digit + low + 1;
		}
		else
		{
			count += (high + 1)*digit;
		}
		digit *=10;

	}
#else
	int a = 1;
	int b = 1;
	while(n > 0)
	{
		count += (n + 8)/10 *a + ((n%10 == 1)?1:0)*b;
		b += n%10*a;
		a *=10;
		n /=10;
	}
#endif

	return count;
}

int main()
{
	int i = 0;

	for (i = 100; i < 200; i++)
	{
		printf("\r\n i[%d]=%d",i,countDigitOne(i));
	}
	return 0;
}
