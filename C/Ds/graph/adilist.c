#include <stdio.h>
#include <stdlib.h>
#define N 5

typedef int datatype;

typedef struct node{
	datatype data;
	struct node *next;
}linknode,*linklist;
void insertlinknode(linklist l,datatype x)
{
	linklist q, p=l;
	q = (linklist)malloc(sizeof(linknode));
	q -> data = x;
	q -> next =NULL;
  
		while((p -> next != NULL)&& p->next->data<x)
		{
				p= p-> next;
		}
		q -> next = p -> next;
		p -> next = q;
}

int fristadj(linknode s[N],int v)
{
	return s[v].next -> data;
}
int nextadj(linknode s[N],int v,int u)
{
	while(s[v] -> next -> data !=u)
		s[v] = s[v] -> next;
	return s[v].next -> data;
}

int main()
{
	int i,j;
	int v;
	linknode s[N]={NULL};
   while(scanf("%d%d",&i,&j)== 2 && i !=j)
   {
       insertlinknode(s[i],j);
	   insertlinknode(s[j],i);
   }

 return 0;
}

