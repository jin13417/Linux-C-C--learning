#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void init_daemon()
{
	int pid;
	int i;

	if(pid = fork())
		exit(0);//创建子进程，关闭父进程；
	else if(pid<0)
		exit(-1);//如果创建不成功退出；
	setsid();//第一子进程成为新的会话组长和进程组长；
	//并与当前控制终端shell分离；

	if(pid= fork())
		exit(0);
	else if(pid<0)
		exit(-1);//禁止进程重新打开终端

	for(i = 0; i < getdtablesize(); i++)
		close(i);//关闭从父进程复制来的所有的进程
	chdir("/tmp");//更改当前工作目录到./tmp
	umask(0);//更改用户创建文件掩码；
	return;
}
