#include <stdio.h>

int main(){
	int n;
	int n1=0;
	int sum=0;//后面累加的数 
	
	//输入数字n
	printf("请输入数字n："); 
	scanf("%d",&n);
	
	//把n的数字抽出来累加
	while(n>0){
		n1=n%10;//取个位数上的数字
		n/=10;//去掉个位数
		sum+=n1;//把个位数数字累加起来 
	}
	
	//依次输出数字的拼音 
	while(sum>0){
		n=sum%10;
		sum/=10;
		switch(n){
			case 0:
				printf("ling");
				break;
			case 1:
				printf("yi");
				break;
			case 2:
				printf("er");
				break;
			case 3:
				printf("san");
				break;
			case 4:
				printf("si");
				break;
			case 5:
				printf("wu");
				break;
			case 6:
				printf("liu");
				break;
			case 7:
				printf("qi");
				break;
			case 8:
				printf("ba");
				break;
			case 9:
				printf("jiu");	
				break;
		}
	}
	return 0;	
} 
