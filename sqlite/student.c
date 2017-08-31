#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#define N 64
char buf[256];
char *errmsg;
int callback(void *para,int f_num,char **f_value,char **f_name);
//typedef (int(*sqlite3_callback)(void *para,int f_num,char **f_value,char **f_name)) callback;
void do_help()
{
	puts("********************************");
	printf("        1: insert\n");
	printf("        2: delete\n");
	printf("        3: query\n");
	printf("        4: get_table\n");
	printf("        5: quit\n");
	puts("********************************");
}
void do_insert(sqlite3 *dp)
{
  int no;
  char name[N];
  float score;
  printf("input a student number:\n");
  scanf("%d%*c",&no);
  printf("input a student name:\n");
  fgets(name,N,stdin);
  name[strlen(name)-1] = 0;
  printf("input a student score:\n");
  scanf("%f%*c",&score);
  memset(buf,0,sizeof(buf));
  sprintf(buf,"insert into student values (%d,'%s',%f)",no,name,score);
  if(sqlite3_exec(dp,buf,NULL,NULL,&errmsg) != SQLITE_OK)
  {
	  printf("error :%s \n",errmsg);
	  exit(-1);
  }
  else
  {
	  puts("insert OK!");
  }
  do_help();
}

void do_delete(sqlite3 *dp)
{
	char expression[N];
	printf("input a expression:\n");
	fgets(expression,N,stdin);
	expression[strlen(expression) - 1] = 0;
  memset(buf,0,sizeof(buf));
  sprintf(buf,"delete from student where %s", expression);
  if(sqlite3_exec(dp,buf,NULL,NULL,&errmsg) != SQLITE_OK)
  {
	  printf("error :%s \n",errmsg);
	  exit(-1);
  }
  else
  {
	  puts("delete OK!");
  }
  do_help();
}

void do_query(sqlite3 * dp)
{
	if(sqlite3_exec(dp,"select *from student",callback,NULL,&errmsg)!=SQLITE_OK)
	{
		printf("error :%s\n",errmsg);
		exit(-1);
	}
  do_help();
}
int callback(void *para,int f_num,char **f_value,char **f_name)
{
	int i;
	printf("******************************\n");
	for(i = 0;i<f_num;i++)
	{
		printf("%s:%s\n",f_name[i],f_value[i]);
	}
	return 0;
}

void do_get_table(sqlite3 *dp)
{
	char **resultp;
	int nrow,ncolumn,i,j,index;
	char buf[256];
//	sprintf(buf,"%s"
	if(sqlite3_get_table(dp,"select * from student",&resultp,&nrow,&ncolumn,&errmsg) != SQLITE_OK)
	{
		printf("error :%s\n",errmsg);
		exit(-1);
	}
	index = ncolumn;
	for(i = 0;i < nrow;i++)
	{
		for(j = 0;j < ncolumn;j++)
		{
			printf("[%s]:%s | ",resultp[j],resultp[index++]);
		}
		puts("");
	}
  do_help();
}


int main(int argc,char *argv[])
{
	int n;
	sqlite3 *dp;
	if(sqlite3_open("mystudent.db",&dp) != SQLITE_OK)
	{
		printf("error:%s\n",sqlite3_errmsg(dp));
		exit(-1);
	}


	do_help();
	while(scanf("%d%*c",&n) == 1)
	{
		switch(n)
		{
		case 1:
			do_insert(dp);break;
		case 2:
			do_delete(dp);break;
		case 3:
			do_query(dp);break;
		case 4:
			do_get_table(dp);break;
		case 5:
			exit(0);
		default:
			do_help();
			break;
		}
	}
	return 0;
}
