/*************************************************************************
 > File Name: houseRobber.c
 > Author:  jinshaohui
 > Mail:    jinshaohui789@163.com
 > Time:    18-09-09
 > Desc:   打家劫舍 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a):(b))

/*
题目:
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如
果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装
置的情况下，能够偷窃到的最高金额。

示例1:
输入: [2,7,9,3,1]
输出: 12
解释: 偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。

解题思路:采用动态规划思想

1.确认原问题与子问题

原问题是求n个房间的最优解，子问题是求前1个房间，前2个房间.....，前n-1个房间的最优解

2.确认状态

第i个状态即为前i个房间能够获得的最大财宝（最优解）

3.确认边界状态的值

前1个房间的最优解，就是第1个房间的财宝值

前2个房间的最优解，就是第1,2个房间中较大的值

4.确定状态转移方程

a.选择第i个房间：第i个房间+前i-2个房间的最优解

b.不选择第i个房间：前i-1个房间的最优解

转移方程：dp[i] = max( dp[i-1],  nums[i]+dp[i-2] ); i>=3
*/
int rob(int *nums,int numsSize)
{
	int *p = NULL;
	int i = 0;
	int max = 0;

	switch(numsSize)
	{
		case 1:
			max = nums[0];
			break;
		case 2:
			max = MAX(nums[0],nums[1]);
			break;
		default:
			p = (int *)malloc(numsSize * sizeof(int));
			if(p != NULL)
			{
				p[0] = nums[0];
				p[1] = MAX(nums[0], nums[1]);

				for(i = 2; i < numsSize; i++)
				{
					p[i] = MAX((p[i - 2] + nums[i]),p[i - 1]);
				}

				max = p[numsSize - 1];
				free(p);
			}
	}
	return max;
}

int main()
{
	int a[10] = {1,3,2,1,5,7,8};
	int i = 0;

	for(i = 1; i <= 7; i ++)
	{
		printf("\r\nnum %d = %d",i,rob(a,i));
	}
	return 0;
}
