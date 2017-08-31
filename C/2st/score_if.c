#include <stdio.h>
int main()
{
	int score;
	puts("input your score:");
	scanf("%d",&score);
	if(score < 0 || score > 100)
	{
		puts("input error");
		return -1;
	}
	if(score >= 60)
	{
		if(score >= 70)
		{
			if(score >= 80)
			{
				if(score >= 90)
					puts("A");
				else
					puts("B");
			}
			else 
				puts("C");
		}else
			puts("D");
	}
	else
		puts("NO pass!");
	return 0;
}
