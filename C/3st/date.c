#include <stdio.h>
int main()
{
	int mouth = 0,
		day = 0,
		num = 0;
	puts("input your date:");
	scanf("%d%d",&mouth,&day);
	if(mouth < 1 || mouth > 12)
	{
		puts("invalid mouth !");
		return -1;
	}

	if(mouth <= 7 )
	{
		if((2 == mouth) && (day > 28) )
		{
			puts("invalid day !");
			return -1;
		}
		else if(mouth % 2)
		{
			if(day > 31)
			{
				puts("invalid day !");
				return -1;
			}
		}
		else if (day > 30)
		{
			puts("invalid day !");
			return -1;
		}
	}
	else 
	{
		if(mouth % 2)
		{
			if(day > 30)
			{
				puts("invalid day !");
				return -1;
			}
		}
		else if (day > 31)
		{
			puts("invalid day !");
			return -1;
		}
	}

	switch(mouth)
	{
	case 12:
		num += 30;
	case 11:
		num += 31;
	case 10:
		num += 30;
	case 9:
		num += 31;
	case 8:
		num += 31;
	case 7:
		num += 30;
	case 6:
		num += 31;
	case 5:
		num += 30;
	case 4:
		num += 31;
	case 3:
		num += 28;
	case 2:
		num += 31;
	case 1:
		break;
	}
	num += day;
	printf("the date [%d-%d] is:\n %d th days \n",mouth,day,num);
	return 0;
}
