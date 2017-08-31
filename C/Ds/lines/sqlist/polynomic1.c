#include <stdio.h>
#include <stdlib.h>

typedef int datatype;
typedef struct node{
	datatype conf;
	datatype index;
	struct node *next;
}linknode,*linkist;


linkist creatlinklist(linkist ha);
void addpoly(linkist ha,linkist hb);
void addpoly(linkist ha,linkist hb)
{
	linkist p,h;
	h=ha;
	hb = hb -> next;
	while(hb != NULL)
	{
		if(h -> next == NULL)
			h -> next = hb;
		if(h -> next ->index < hb -> index)
		{
			p = hb;
			hb = hb -> next;
			p -> next = h -> next;
			h -> next = p;
				h = h -> next;
		}
		else
			if(h->next -> index = hb -> index)
			{
				h -> next -> conf += hb -> conf;
				h = h -> next;
				p =hb;
					hb = hb -> next;
				free(p);
			}
			else
			{
				h = h-> next;
			}
	}
}

int main()
{
	linkist ha,hb;
	ha = (linkist)malloc(sizeof(linknode));
	ha -> next = NULL;
	hb = (linkist)malloc(sizeof(linknode));
	hb -> next = NULL;

ha = creatlinklist(ha);
	hb = creatlinklist(hb);
	 addpoly(ha,hb);
	visitlinklist(ha);

	return 0;
}
linkist creatlinklist(linkist ha)
{

	int i,j;
	linkist q = ha;
	while(1)
	{
		scanf("%d%d",&i,&j);
		if(i == 0)
			break;
		q -> next  = (linkist)malloc(sizeof(linknode));
		q = q ->next;
		q -> conf = i;
		q -> index = j;
		q -> next = NULL;
	}
	return ha;
}
int visitlinklist(linkist h)
{
	h = h -> next;
	while(h != NULL)
	{
		printf("%dX%d ",h -> conf, h -> index);
		h = h -> next;
	}
	puts("");
}


