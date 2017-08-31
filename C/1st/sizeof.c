#include <stdio.h>
#include <string.h>

int main()
{
	printf("sizeof (char) = %d\n",sizeof(char));
	printf("sizeof (short) = %d\n",sizeof(short));
	printf("sizeof (int) = %d\n",sizeof(int));
	printf("sizeof (long) = %d\n",sizeof(long));
	printf("sizeof (float) = %d\n",sizeof(float));
	printf("sizeof (double) = %d\n",sizeof(double));
	printf("sizeof (longlong) = %d\n",sizeof(long long));
	printf("sizeof (\"hello\") = %d\n",sizeof("hello"));
	printf("strlen (\"hello\") = %d\n",strlen("hello"));
	return 0;
}
