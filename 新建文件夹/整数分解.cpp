//整数分解
#include<stdio.h>

int main()
{
	int x;
	scanf("%d",&x);
	
	int t = 0;
	do {
		int d = x % 10;	//  d =（x最右边的数字） 
		t = t*10+d;		//  t =（x的数字慢慢从右积累） 
		x /= 10;		//  x =（x去掉最右一位数字的数） 
	}while (x>0);
	printf("x=%d,t=%d\n",x,t);
	x = t;
	do {
		int d = x % 10;
		printf("%d", d);
		if(x > 9) {
			printf(" ");
		}
		x /= 10;
		}while ( x > 0);
		printf("\n");
		
	return 0;
 } 
