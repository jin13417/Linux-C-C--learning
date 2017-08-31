#include <stdio.h>
#define N 6
#define M 1000


int main()
{
	int g[N][N]={{0,20,15,M,M,M},{2,0,4,M,10,30},\
		{M,M,0,M,M,10},{M,M,M,0,M,M},{M,M,M,15,0,10},{M,M,M,4,M,0}};
	int s[N]={0},dist[N]={0},*p;
	int v=0,u,i,count=1,min,path;
	printf("input the number <0 --%d>\n",N);
  	scanf("%d",&v);
     s[v] = 1;
	 p = g[v];
	 for(i = 0;i < N;i++)
	 {
		 dist[i] = *(p+i);
	 }
   while(count < N - 1)
   {
	   for(i=0;i<N;i++)
	   {
		   path=M;
	   while(s[i]==0&&dist[i] < path)
	   {
		   path = dist[i];
		   min = i;
	   }
	   }
	   s[min] = 1;
	   for(i=0;i<N;i++)
	   {
			   while(s[i]==0 && dist[i] > dist[min] + g[min][i])
		   {
			   dist[i] = dist[min]+g[min][i];
		   }
	   }
	   count++;
	   }
   for(i=0;i<N;i++)
	   printf("V%d ---> V%d  %d\n",v,i,dist[i]);
   return 0;
}

