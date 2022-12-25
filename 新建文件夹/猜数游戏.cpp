#include<stdio.h>
#include<stdlib.h>	//rand()函数需要的头文件是：<stdlib.h>
#include <time.h>	//这是time(NULL)函数需要的头文件 
int main()
{
//使用srand()函数设置随机数种子  
	int number = rand()%100+1;
	int count = 0;
	int a = 0;
	printf("我已经想好了一个1到100之间的数。");
	do {
		printf("请猜这个1到100之间数：");
		scanf("%d", &a);
		if ( a > number ) {
			printf("你猜的数大了。");
		} else if ( a < number ) {
			printf("你猜的数小了。");
		}
		count ++;
	} while (a != number);
	printf("太好了，你用了%d次就猜到了答案。\n", count);

	return 0;
}
