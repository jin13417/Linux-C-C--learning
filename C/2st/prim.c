#include <stdio.h>
#include <math.h>
int main()
{
	int num;
	int i;
	for(num = 1; num <= 100; num ++)
	{
		for(i = 2; i < num / 2 ; i ++)
		{
			if (num % i == 0)
				break;
		}

		if (i > sqrt(num))
			printf("%3d",num);

	}
	return 0;

}
