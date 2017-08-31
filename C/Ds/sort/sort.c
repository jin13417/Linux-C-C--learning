#include <stdio.h>
#define N 8

void quicksort(int s[],int low, int high);//借助递归函数，进行。
void quicksort(int s[],int low, int high)//快速排序
{
	int i = low,j=high;
	int key=s[i];
	while(i<j)
	{
		while(i<j&&s[j] > key)
			j--;
		if(i<j)
		s[i] = s[j];
		while(i<j&&s[i]< key )
			i++;
		if(i<j)
		s[j] = s[i];
	}
	s[i]=key;
		if(i-1>low)quicksort(s,low,i-1);
		if(i+1<high)quicksort(s,i+1,high);
}

int main()
{
	int min,i,j;
	int s[N]={14,27,9,55,16,48,31,22};
	quicksort(s,0,N-1);

#if 0
	for(i=N-1;i>0;i--)//，排序的次数 交换排序，冒泡排序
	{
		min=0;
		for(j=0;j<i;j++)//查找剩余数组中最大的元素排低
			if(s[j]>s[j+1])
			{
				min =1;
				s[j]^=s[j+1];
				s[j+1]^=s[j];
				s[j]^=s[j+1];
			}
		if(min==0)//当min仍为0时，说明已经排序完成，直接跳出循环；
			break;
	}


	for(i=0;i<N-1;i++)//排序所需要的趟数，选择排序
	{
		min = i;
		for(j=i+1;j<N;j++)
			if(s[min] > s[j])
				min = j;
		if(min>i)
		{
			s[min]^=s[i];
			s[i]^=s[min];
			s[min]^=s[i];
		}
	}
#endif
	for(i=0;i<N;i++)
		printf("%d ",s[i]);
	puts("");
	return 0;
}
