#include <stdio.h>
#include <stdlib.h>
#define N 8
typedef int datatype;
typedef struct
{
	datatype data[N];
	int last;
}sqlist;
void clearsqlist(sqlist *L);
void clearsqlist(sqlist *L);
int insertsqlist(sqlist *L,datatype x,int i);
int deletesqlist(sqlist *L,int i);
int lengthsqlist(sqlist *L);
int emptysqlist(sqlist *L,datatype x,int i);
int fullsqlist(sqlist *L,datatype x,int i);

int main()
{
sqlist *L;
L=(sqlist *)malloc(sizeof(sqlist));
sqlist *crteatesqlist();
}

void clearsqlist(sqlist *L)//清除顺序表
{
	L -> last = -1;
}
int insertsqlist(sqlist *L,datatype x,int i)//在第i个数前插入X
{
	int j;
	if((L -> last>=N-1)||(i<0)||(i > L -> last+1))
		return 0;
	else
	{
		for(j = L -> last;j>=i;j--)
			L -> data[j + 1] = L -> data[j];
		L -> data[ i ]=x;
		L -> last ++;
	}
	return 0;
}
int deletesqlist(sqlist *L,int i)//删除第i个数
{
	int j;
	if(((i<0)||(i > L -> last+1)))
		return 0;
	else
	{
	for(j = i ;j<=L -> last;j++)
			L -> data[j - 1] = L -> data[j];
    L -> last--;
	}
	return 0;
}
int lengthsqlist(sqlist *L)//计算l长度，last下标是last+1
{
	return L -> last+1;
}
int emptysqlist(sqlist *L,datatype x,int i)//清空
{
	if(L -> last == -1)
		return 0;
	else
		return 1;

}
int fullsqlist(sqlist *L,datatype x,int i)//判断是否满
{
	if(L -> last == N -1)
		return 1;
	else
		return 0;
}
int getsqlist(sqlist *L,int i)
{
	return L -> data[i];
}
int locate(sqlist *L, datatype x)
{
	int i=0;
	while(i <= L -> last && L -> data[i] 

