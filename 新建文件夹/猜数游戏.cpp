#include<stdio.h>
#include<stdlib.h>	//rand()������Ҫ��ͷ�ļ��ǣ�<stdlib.h>
#include <time.h>	//����time(NULL)������Ҫ��ͷ�ļ� 
int main()
{
//ʹ��srand()�����������������  
	int number = rand()%100+1;
	int count = 0;
	int a = 0;
	printf("���Ѿ������һ��1��100֮�������");
	do {
		printf("������1��100֮������");
		scanf("%d", &a);
		if ( a > number ) {
			printf("��µ������ˡ�");
		} else if ( a < number ) {
			printf("��µ���С�ˡ�");
		}
		count ++;
	} while (a != number);
	printf("̫���ˣ�������%d�ξͲµ��˴𰸡�\n", count);

	return 0;
}
