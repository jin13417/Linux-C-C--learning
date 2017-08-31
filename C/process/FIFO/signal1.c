#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int wait_mark;
void waiting(),stop();

int main(int argc,char *argv[])
{
  int p1,p2;
  signal(SIGINT,stop);
  while((p1 = fork()) == -1);
  if(p1 > 0)
  {
	  while((p2 = fork())== -1);
	  if(p2 > 0)
	  {
		  wait_mark = 1;
		  waiting();
		  kill(p1,10);//10,signusr1;给p1发信号
		  kill(p2,12);//12,signusr2;给p2发信号
		  wait(NULL);//等待子进程关闭；
		  wait(NULL);//等待子进程关闭；
		  printf("parent process exit!\n");
		  exit(0);
	  }
	  else
	  {
		  wait_mark = 1;
		  signal(12,SIG_IGN);
		  waiting();
		  lockf(1,1,0);
		  printf("child process 2 is kill by parent!\n");
		  lockf(1,0,0);
		  exit(0);
	  }
  }
  else
  {
		  wait_mark = 1;
		  signal(10,SIG_IGN);
		  waiting();
		  lockf(1,1,0);
		  printf("child process 1 is kill by parent!\n");
		  lockf(1,0,0);
		  exit(0);
  }
}

void waiting()
{
	while(wait_mark != 0);
}
void stop()
{
	wait_mark = 0;
}



