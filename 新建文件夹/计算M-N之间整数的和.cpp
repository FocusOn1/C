#include <stdio.h>
#include <math.h>
//实现累加功能 
int sum(int a,int b){
	int num;
	for(;a<=b;a++){	
		num = a + num;	//或者写成： num += a; 
		printf("num = %d\n", num);
	}
	return num;
}	
int main()
{    
    int m,n;	 
    scanf("%d %d", &m,&n);
    
    printf("num = %d\n", sum(m,n));
    return 0;
}


