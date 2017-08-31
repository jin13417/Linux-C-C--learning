#include <stdio.h>

#include <stdlib.h>

typedef int datatype;
typedef struct dnode {
	datatype data;
	struct dnode *prior,*next;
}dlinkdnode,*dlinklist;
dlinklist createdlinklist()
{
	dlinklist h;
	h = (dlinklist)malloc(sizeof(dlinkdnode));
	h -> prior = NULL;
	h -> next = NULL;
	h -> data = 0;
}
int insertlinklist(dlinklist h,datatype x,int i)//插入一节点
{
	dlinklist q, p;
   p = Getlist(h ,i);
   if(p == NULL )
	   return;
   else
    {
		q= (dlinklist)malloc(sizeof(dlinkdnode));
		q -> data = x;
		q -> prior = p -> prior;
		q -> next = p;
		(p -> prior) -> next = q;
		p -> prior = q;
	}
}
int deletedlinklist(dlinklist h ,int i)
{
	h = Getlist(h,i);
	if(h == NULL)
		return;
	else
	{
		(h -> prior) -> next = h -> next;
		(h -> next) -> prior = h -> prior;
		free(h);
	}
}
int main()
{
	return 0;
}




