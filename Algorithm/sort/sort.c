/*************************************************************************
 > File Name: sort.c
 > Author:  jinshaohui
 > Mail:    jinshaohui789@163.com
 > Time:    18-09-07
 > Desc:    
 ************************************************************************/
#include<stdio.h>

/*冒泡排序 交换排序*/
void sort_1(int *s,int size)
{
	int i = 0;
	int j = 0;
	int chage = 0;

	for(i = size-1; i > 0; i--)
	{
		chage = 0;
		for(j = 0; j < i; j ++)
		{
			if (s[j] > s[j+1])
			{
				s[j] ^= s[j+1];
				s[j+1] ^= s[j];
				s[j] ^= s[j+1];
				chage = 1;

			}

		}
		if(chage == 0)
		{
			break;
		}
	}
	return;
}

/*选择排序*/
void sort_2(int *s,int size)
{
	int i = 0;
	int j = 0;
	int min = 0;

	for(i = 0; i < size -1; i++)
	{
		min = i;
		for(j=i+1;j < size; j ++)
		{
			if(s[j] < s[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			s[i] ^= s[min];
			s[min] ^= s[i];
			s[i] ^= s[min];
		}
	}
}

/*插入排序*/

void insort(int *s,int size)
{
	int i = 0;
	int j = 0;
	int key = 0;

	for(i = 1; i < size; i++)
	{
		key = s[i];
		j = i - 1;
		while((j >= 0)&&(s[j] > key))
		{
			s[j+1] = s[j];
			j--;
		}
		s[j+1] = key;
	}

	return;
}
int main()
{
	int i = 0;
	int len = 0;
	int s[] = {14,27,9,55,16,48,32,22};

	len = sizeof(s)/sizeof(int);
    
	insort(s,len);

	for (i = 0; i < len; i++)
	{
		printf("%d,",s[i]);
	}
	return 0;
}
