#include <stdio.h>
int entry();
int search(int);
int list();
char *str1[80];
int a[80]={0};
char *str2[80];

int main()
{
	list();
	char ch;
	int n;
	while(ch!='#')
	{
	scanf("%c",&ch);
		if(ch=='1')
		{		
			entry();
		}
		else
			if(ch=='2')
				puts("the students number:");
		scanf("%d",&n);

		search(n);
		continue;
	}
	return 0;
}

int list()
{
	puts("***********************************************");
	puts("*               1、录入                       *");
	puts("*               2、查询                       *");
	puts("*               #、退出                       *");
	puts("***********************************************");
	return 0;
}
int entry()
{
	static int i=0;
	puts("input the students name:");
	scanf("%s%d%c",str1[i],&a[i],str2[i]);
	i++;

}
int search(int n)
{
	puts("name      number         sex ");
	int i,k;
	char ch;
	for(i=0;i<80;i++)
		if(a[i]==n)
			k=i;
	printf("%s   %d     %s",str1[k],a[k],str2[k]);
	return 0;
}




