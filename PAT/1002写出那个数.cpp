#include <stdio.h>

int main(){
	int n;
	int n1=0;
	int sum=0;//�����ۼӵ��� 
	
	//��������n
	printf("����������n��"); 
	scanf("%d",&n);
	
	//��n�����ֳ�����ۼ�
	while(n>0){
		n1=n%10;//ȡ��λ���ϵ�����
		n/=10;//ȥ����λ��
		sum+=n1;//�Ѹ�λ�������ۼ����� 
	}
	
	//����������ֵ�ƴ�� 
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
