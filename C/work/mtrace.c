/*************************************************************************
 > File Name: mtrace.c
 > Author:  jinshaohui
 > Mail:    jinshaohui789@163.com
 > Time:    18-11-07
 > Desc:    
 ************************************************************************/
#include<assert.h>

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<mcheck.h>


int main()
{
	int *p = NULL;

	setenv("MALLOC_TRACE","1.log",1);
	mtrace();

	p = malloc(100);
	
	muntrace();

	return;
}
