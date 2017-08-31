#include <stdio.h>
#include "sequeue.h"
#ifndef N
#define N 5
#endif
void DFS(int matrix[N][N],int s[],int v);
void BFS(int matrix[N][N],int s[],int v);

int firstadj(int matrix[N][N],int v)
{
	int i;
	for(i=0;i<N;i++)
		if(matrix[v][i]==1)
			return i;
	return -1;
}
int nextadj(int matrix[N][N],int v,int u)
{
	int i;
	for(i=u+1;i<N;i++)
		if(matrix[v][i]==1)
			return i;
	return -1;
}

//1、访问v，s【v】置位；2、取v的第一临界点u
//3、若u>=0,转4，否则退出；4、若u未访问则DFS（matrix，s，u）
//再访问下一个节点，u = vnextadj(matrix,s,u);再转3.
void DFS(int matrix[N][N],int s[],int v)//深度优化搜索。
{
	int u;
	printf("V%d ",v);
	s[v]=1;
	u = firstadj(matrix,v);
	while(u>=0)
	{
		if(s[u]!=1)
		{
			DFS(matrix,s,u);
		}
		u=nextadj(matrix,v,u);
	}
}
void BFS(int matrix[N][N],int s[],int v)//对图G从序号V的顶点开始遍历，按BFS遍历；
{
	int u;
	sequeue *sq;
	sq = Createsequeue();//创建队列并置空；
	printf("V%d ",v);//访问V定点，输出；
	s[v]=1;//对v定点置1；
	Ensequeue(sq,v);//v进队列；
	while(!Emptysequeue(sq))//当队列未空时，依次出队，
	{
		v = Desequeue(sq);	
		u=firstadj(matrix,v);//先找到他的第一临接点；
		while(u>=0)//u》=0；表示访问v定点的所有临接点；
		{
			if(!s[u])//判断临节点标志是否为1，如果是找下个临界点；依次遍历
			{
				printf("v%d ",u);
				s[u]=1;
				Ensequeue(sq,u);//有临界点时，访问 置标识1，并进队列～
			}
			u = nextadj(matrix,v,u);//找v定点的下一临界点，
		}
	}
}


int main()
{
	int matrix[N][N]={0};
	int i,j,s[N]={0};
	while(1)
	{
		scanf("%d%d",&i,&j);
		if ( i == j)
			break;
		matrix[i][j]=1;
		matrix[j][i]=1;
	}

	// DFS(matrix,s,0);

	//********************************************

	BFS(matrix,s,0);
#if 0
	for(i=0;i<N;i++)
	{
		printf("V%d: ",i);
		for(j=0;j<N;j++)
		{
			if(matrix[i][j] == 1)
				printf("V%d ",j);
		}
		puts("");
	}
#endif
	return 0;
}





