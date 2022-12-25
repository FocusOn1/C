#include<stdio.h>
//求和函数
void sum(int begin,int end)
{
	int i;
	int sum = 0;
	for(i = begin;i <= end;i++)
	{
		sum += i;
	}
	printf("%d与%d的和为%d\n",begin,end,sum);
}

//主函数
int main()
{
	sum(1,5);
	sum(10,20);
	sum(35,45);
	return 0;
 } 
