#include <stdio.h>
#include <stdlib.h>

typedef int datatype;
typedef struct node{
	datatype coef;
	datatype exp;
	struct node *next;
}linknode,*linklist;

linklist creatlinklist()
{
	linklist l;
	l=(linklist)malloc(sizeof(linknode));
	l -> next =NULL;
	return l;
}

int insertlinklist(linklist l)
{
	int i,j;
	linklist p;
	while(1)
	{
	scanf("%d%d",&i,&j);
		if(0==i)
			break;

		p = (linklist)malloc(sizeof(linknode));
		p -> coef = i;
		p -> exp = j;
		p -> next = NULL;
		l -> next =p;
		l = l -> next;
	}
	return 0;
}

int visitlinklist(linklist l)
{
	linklist p;
	while(l -> next != NULL)
	{
		p = l -> next;
		printf("%dX%d ",p -> coef, p -> exp);
		l -> next =p -> next;
		free(p);
	}
	return 0;
}
int mergelinklist(linklist ha,linklist hb)
{
	linklist p;
	
	hb = hb -> next;
	while(hb != NULL)
	{
		if(ha -> next == NULL)
		{
			ha -> next = hb;
			break;
		}
		if( hb -> exp > ha -> next -> exp)
		{
			p = hb;
			hb = hb -> next;
			p -> next = ha -> next;
			ha -> next = p;
			ha = ha -> next;
		}
		else if (hb -> exp == ha -> next -> exp )
		{

			ha -> next -> coef += hb -> coef;
			ha = ha -> next;
			p = hb;
			hb = hb -> next;
			free(p);
		}
		else
			ha = ha -> next;
	}
return 0;
}

int main()
{
	linklist ha,hb;
	ha = creatlinklist();
	hb = creatlinklist();
	insertlinklist(ha);
	insertlinklist(hb);
	mergelinklist(ha,hb);
	visitlinklist(ha);

	return 0;
}



