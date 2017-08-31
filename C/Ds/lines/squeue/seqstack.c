#include <stdio.h>
#include <stdlib.h>

#define N 8

typedef int datatype;

typedef struct
{
	datatype data[N];
	int top;
} seqstack;

seqstack *CreateSeqstack()
{
	seqstack *s;
	
	s = (seqstack *)malloc(sizeof(seqstack));
	s->top = -1;

	return s;
}

int EmptySeqstack(seqstack *s)
{
	return (-1 == s->top);
}

int FullSeqstack(seqstack *s)
{
	return (N-1 == s->top);
}

void ClearSeqstack(seqstack *s)
{
	s->top = -1;
}

void PushSeqstack(seqstack *s, datatype x)
{
	s->data[++s->top] = x;

	return;
}

datatype PopSeqstack(seqstack *s)
{
	return s->data[s->top--];
}

datatype GetTop(seqstack *s)
{
	return s->data[s->top];
}

#if 0
int main()
{
	int i;
	seqstack *s;

	s = CreateSeqstack();
	for (i=1; i<=10; i++)
	{
		if ( ! FullSeqstack(s) ) 
			PushSeqstack(s, i);
		else 
			printf("stack is full\n");
	}

	while ( ! EmptySeqstack(s) )
	{
		printf("%d ", PopSeqstack(s));
	}
	printf("\n");

	return 0;
}
#endif
