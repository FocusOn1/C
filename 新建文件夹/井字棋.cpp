#include <stdio.h>

int main ()
{
	const int num = 3;
	int a[num][num];
	int i,j;

	printf("�����뾮�������֣�");
	//�����鸳ֵ
	for (i=0;i<num;i++){
		for (j=0;j<num;j++){
			scanf ("%d",&a[i][j]);           
		}
	}
	
	for (i=0;i<num;i++) {
		for (j=0;j<num;j++) {
			if(j==num-1) {
				printf("%d\n",a[i][j]);
			}else {
				printf("%d ",a[i][j]);
			}
		}
	}
	
	//�����
	int ret = -1;
	int cnsto,cnstx;
	int cno,cnx;

	for (i=0;i<num;i++){// ��for�������ж�ret,��߳���ִ��Ч�ʣ�������������ʱ������xunhuan��

		cnsto = cnstx = 0;
		cno = cnx = 0;// ÿ�� for Ҫ���㣬������ۻ��ϴεļ�����

		for (j=0;j<num;j++){
			if (a[i][j]==0){
				cnsto ++;
			}else {           //1 0 1 0 0 1 0 1 0 
				cnstx ++;
			}
			
			if (a[j][i]==0){
				cno ++;
			}else {
				cnx ++;
			}
			
		}if (cnsto==num||cno==num){
			ret = 0;
		}else if(cnstx == num||cnx==num){
			ret = 1;
		}
	}

	//�����
	
	if (ret==-1){
		for (j=0;j<num&&ret==-1;j++){
			cnsto = cnstx = 0 ;
			for (i=0;i<num;i++){
				if (a[i][j]==0){
					cnsto ++;
				}else{
					cnstx ++;
				}
			}if (cnsto == num){
				ret = 0;
			}else if (cnstx == num){
				ret = 1;
			}
		}
	}
	
	//���Խ���
	if (ret == -1){
		cnsto =cnstx = 0;
		for (i=0;i<num;i++){ //101010011
			if (a[i][i] == 0){
				cnsto ++;
			}else {
				cnstx ++;
			}
		}if (cnsto == num){
			ret = 0;
		}else if(cnstx == num){
			ret = 1;
		}
	}
	// ��� ���Խ���
	if (ret == -1){
		cnsto = cnstx = 0;
		for (i=0;i<num;i++){
			if (a[i][num-i-1]==0){
				cnsto ++;
			}else {
				cnstx ++;
			}
		}if (cnsto==num){
			ret = 0;
		}else if (cnstx == num){
			ret = 1;
		}
	}
	if (ret == -1){
		printf ("����һ��");
	}else{
		printf ("ʤ������%d\n",ret);//101010100
	}
	return 0;
}
