/*************************************************************************
 > File Name: sort.c
 > Author:  jinshaohui
 > Mail:    jinshaohui789@163.com
 > Time:    18-09-07
 > Desc:    
 ************************************************************************/
#include<stdio.h>

/*快速排序*/

void quicsort(int * s,int low,int high)
{
	int i = low;
	int j = high;
	int tmp = s[i];

	while(i < j)
	{
		/*从右向左找到第一个小于 tmp的数字，*/
		while((i < j) && (s[j] > tmp))
		{
			j --;
		}
		if (i < j)
		{
			s[i] = s[j];
		}
	    /*从左向右找到第一个大于tmp的数字*/
		while ((i < j) && (s[i] < tmp))
		{
			i++;
		}
		if (i < j)
		{
			s[j] = s[i];
		}

	}
    /*i = j 时，将tmp填入中间位置，这样右边都是小于tmp
	 * 左边都是大于tmp的数值*/
	s[i] = tmp;

	if((i-1) > low)
	{
		quicsort(s,low,i-1);
	}

	if ((i+1) < high)
	{
		quicsort(s,i+1, high);
	}

	return;
}

int main()
{
	int i = 0;
	int len = 0;
	int s[] = {14,27,9,55,16,48,32,22};

	len = sizeof(s)/sizeof(int);
    
	quicsort(s,0,len-1);

	for (i = 0; i < len; i++)
	{
		printf("%d,",s[i]);
	}
	return 0;
}
