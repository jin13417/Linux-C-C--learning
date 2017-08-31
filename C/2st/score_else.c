#include <stdio.h>
int main()
{
	int score;
	puts("input your score:");
	scanf("%d",&score);
	if(score < 0 || score > 100)
	{
		puts("input error!");
		return -1;
	}
	else if(score < 60)
		puts("NO PASS!");
	else if (score < 70)
		puts("D");
	else if (score < 80)
		puts("C");
	else if (score < 90)
		puts("B");
	else
		puts("A");
	return 0;
}
