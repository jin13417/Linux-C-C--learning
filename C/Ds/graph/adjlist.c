#include <stdio.h>
#include <stdlib.h>

#define N 5

typedef struct _node_
{
	int vertex;
	struct _node_ *next;
} linknode, *linklist;

void AddEdge(linknode s[], int i, int j)
{
	linklist p, q;

	p = s + i;
	while (p->next != NULL && p->next->vertex < j) p = p->next;
	q = (linklist)malloc(sizeof(linknode));
	q->vertex = j;
	q->next = p->next;
	p->next = q;

	return;
}

int FirstAdj(linknode s[], int v)
{
	return s[v].next->vertex;
}

int NextAdj(linknode s[], int v, int u)
{
	linklist p;

	p = s[v].next;
	while (p->vertex != u) p = p->next;
	return (p->next == NULL ? -1 : p->next->vertex);
}

int main()
{
	linknode s[N] = {{0, NULL}};
	int i, j;
	linklist p;

	while (scanf("%d,%d", &i, &j) == 2 && i != j)
	{
		AddEdge(s, i, j);
		AddEdge(s, j, i);
	}

	for (i=0; i<N; i++)
	{
		printf("V%d : ", i);
		p = s[i].next;
		while (p != NULL)
		{
			printf("V%d ", p->vertex);
			p = p->next;
		}
		printf("\n");
	}

	return 0;
}
