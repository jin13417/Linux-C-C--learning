
#include <stdio.h>
#include <stdlib.h>
#define N 8
typedef int datatype;
typedef struct node
{
	datatype data;
	struct node *next;
}linknode,*linklist;

linknode * createlinklist()
{
	linklist h;
	h=(linklist)malloc(sizeof(linknode));
	h->next=NULL;
	return h;
}
#if 0   //2个指针创建链表；
int main()
{
	int i;
	linklist q,r
		r=h;

	for(i = 1; i <= 10;i++)
	{
		q=(linklist)malloc(sizeof(linknode));

		q -> data = i;
		q = r -> next;
		q -> next = NULL;

	}
	//一个指针创建链表；
	int main()
	{
		int i;
		linklist l = h;
			for(i = 0; i <= 10; i++)
			{
				l -> next=(linklist)malloc(sizeof(linknode));
				l -> data = i;
				l -> next =NULL;
			}
	}
#endif
	int emptylinklist(linklist h)//判断是否为空链表
	{
		return (h -> next ==NULL);
	}
	int lengthlinklist(linklist h)//输出链表的长度
	{
		int  i = 0;
		while(h -> next != NULL)
		{
			i++;
			h = h -> next; 
		}
		return i;
	}
	void visitlinklist(linklist h)//遍历，打印数值
	{
		h = h -> next;
		while(h != NULL)
		{
			printf("%d\t",h -> data);
			h = h -> next;
		}
		puts("");
	}
	int searchlinklist(linklist h,datatype x)//输出 x在链表中的位置
	{
		int pos=0;
		h = h -> next;
		while(h != NULL)
		{
			if(h -> data = x)
				return pos;
				pos++;
				h = h -> next;
		}
		return pos;
	}

int insertlinklist1(linklist h,int pos,datatype x) //将x插入到pos位置。
{                                                  //头节点为-1，表头节点为0；
linklist q;                                     
 if(pos< 0 || pos > lengthlinklist(h) )
	 return -1;
while(pos--)      //pos-- 完毕 ，h是 POS位置的前一个节点；
	h = h -> next;
q = (linklist)malloc(sizeof(linknode));
q -> data = x;
q -> next = h -> next;
h -> next = q;
return 0;
}
void insertlinklist2(linklist h,datatype x)//遍历H，在顺序插入X；
{

}
int deletelinklist1(linklist h, int pos)//删除在pos位置的节点
{
	linklist p;
	if(pos < 0 || pos > lengthlinklist(h) - 1)
		return -1;
	while(pos--)
		h = h -> next;
	p = h -> next;
	h -> next = p -> next;
	free(p);
	return 0;
}
void deletelinklist2(linklist h,datatype x)//删除x数值所在的节点
{
	linklist p = h -> next;

   while ( p != NULL)
   {
	   if( p -> data == x)
	    {
			h -> next = p -> next;
			free(p);
		}
	   else
		   h = h -> next;
		   p = h -> next;
   }
   return;
}
void clearlinklist(linklist h)Z
{
	linklist p;
	while( h -> next != NULL)
	{
		p = h -> next;
		h -> next = p -> next;
		free(p);
	}
	return;
}
void reverselinklist(linklisth h)//翻转链表。。
{
  linklist p ,q;
  p = h -> next;
  q = p-> next;
  h -> next = NULL;
  while( q != NULL)
  {

}
		








int main()
{
	return 0;
}





