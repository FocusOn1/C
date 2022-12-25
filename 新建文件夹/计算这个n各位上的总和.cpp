
#include <stdio.h>
int main(){
    int n;//要输入的正整数
    scanf("%d",&n);//输入n
    int sum=0; //总和
    int count=0;//位数
    char a[10]={'ling','yi','er','san','si','wu','liu','qi','ba','jiu'};
    int n1;//每一位的数字
    //计算这个n各位上的总和
    for(int i=1;i<=n;i++){
        n1=n%10;//取最小位数的数字
        n/=10;//n去掉个位上的数字
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
        if(count==0){//最后一位
            continue;
        }else{
            printf(" ");
        }
    }
    return 0;
}
