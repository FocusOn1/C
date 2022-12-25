#include <stdio.h>

int main ()
{
	const int num = 3;
	int a[num][num];
	int i,j;

	printf("请输入井字棋数字：");
	//给数组赋值
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
	
	//检查行
	int ret = -1;
	int cnsto,cnstx;
	int cno,cnx;

	for (i=0;i<num;i++){// 在for在增加判断ret,提高程序执行效率，即有连续三个时，结束xunhuan。

		cnsto = cnstx = 0;
		cno = cnx = 0;// 每次 for 要清零，否则会累积上次的计数；

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

	//检查例
	
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
	
	//检查对角线
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
	// 检查 反对角线
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
		printf ("再来一局");
	}else{
		printf ("胜利者是%d\n",ret);//101010100
	}
	return 0;
}
