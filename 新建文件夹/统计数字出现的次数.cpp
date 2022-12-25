#include<stdio.h>

int main()
{
	const int number = 10; //数组的大小 
	int x;
	int count[number];	//定义数组 
	int i;
	
	for ( i=0;i<number;i++ ) {	//初始化... 
		count[i] = 0;			//... 
	}							//...数组

	while( x != -1){
		if ( x >= 0 && x <= 9) {
			count[x] ++;	//数组参与运算 
		}
		scanf("%d",&x);
	}

	for ( i=0; i<number;i++ ) {			//遍历...	
		printf("%d:%d\n",i,count[i]);	//...数组... 
	}									//输出 
	return 0;
 } 
 

