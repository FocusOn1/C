
#include <stdio.h>
int main(){
    int n;//Ҫ�����������
    scanf("%d",&n);//����n
    int sum=0; //�ܺ�
    int count=0;//λ��
    char a[10]={'ling','yi','er','san','si','wu','liu','qi','ba','jiu'};
    int n1;//ÿһλ������
    //�������n��λ�ϵ��ܺ�
    for(int i=1;i<=n;i++){
        n1=n%10;//ȡ��Сλ��������
        n/=10;//nȥ����λ�ϵ�����
        sum+=n1;
        count++;
    }
    while(sum>=0){
        n1=sum%10;
        sum/=10;
        count--;
        switch(n1){
            case 0:   printf(a[0]);
            case 1:   printf(a[1]);
            case 2:   printf(a[2]);
            case 3:   printf(a[3]);
            case 4:   printf(a[4]);
            case 5:   printf(a[5]);
            case 6:   printf(a[6]);
            case 7:   printf(a[7]);
            case 8:   printf(a[8]);
            case 9:   printf(a[9]);
        }
        if(count==0){//���һλ
            continue;
        }else{
            printf(" ");
        }
    }
    return 0;
}
