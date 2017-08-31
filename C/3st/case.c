#include <stdio.h>
int main()
{
	int score;
	puts("input your score:");
	while(scanf("%d",&score) && score)
	{
		if(score < 0 || score > 100)
		{
			puts("input error");
			continue;
		}
		switch(score / 10)
		{
		case 10:
		case 9:
			puts("A");
			break;
		case 8:
			puts("B");
			break;
		case 7:
			puts("C");
			break;
		case 6:
			puts("D");
			break;
		default:
			puts("NO PASS!");
			break;
		}

	}
	return 0;
}
