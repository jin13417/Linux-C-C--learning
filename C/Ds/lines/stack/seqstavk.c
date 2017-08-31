#include <stdio.h>

#include <stdlib.h>
#define N 9

typedef int datatype;
typedef struct
{
	datatype data[N];//栈顶元素
	int top;         //栈顶元素下标；
}seqstack,*seqstacklist;
seqstacklist Create()//创建栈；
{
	seqstacklist s;
	s=(seqstacklist)malloc(sizeof(seqstack));
	s -> top = -1;
	return s;
}
int emptyseqstack(seqstacklist s)//判断栈是否空；
{
	return (s -> top ==-1);
}
int fullseqstack(seqstacklist s)//判断栈是否满；
{
	return (s ->top ==N-1);
}
void pushseqstack(seqstacklist s,datatype x)//X进栈；
{
	s -> data[++s -> top] = x;
	return;
}
datatype popstack (seqstacklist s)//元素出栈
{
	return s ->data[s -> top--]; 
}
datatype gettopseqstack(seqstacklist s)//取栈定
{
	return s-> data[s -> top];
}
void clearseqstack(seqstacklist s)
{
	s -> top = -1;
}
int main()
{
	int i;

	seqstacklist s;
	s = Create();
	for(i=1;i<10;i++)
	{
		if(!fullseqstack(s))
			pushseqstack(s,i);
		else 
			printf("stack is full \n");
	}
	while(!emptyseqstack(s))
	{
		printf("%d",popstack(s));
	}
	return 0;
}
