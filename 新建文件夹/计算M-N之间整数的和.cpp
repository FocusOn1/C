#include <stdio.h>
#include <math.h>
//ʵ���ۼӹ��� 
int sum(int a,int b){
	int num;
	for(;a<=b;a++){	
		num = a + num;	//����д�ɣ� num += a; 
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


