#include <stdio.h>	//标准输入输出函数库（printf、scanf）
#include <conio.h>  //为了读取方向键
#include <windows.h>//控制dos界面（获取控制台上坐标位置、设置字体颜色）
#include <math.h>   //pow函数

/*******函  数  声  明*******/
void gotoxy(int x, int y); 		//获取屏幕光标位置
int color(int c);               //设置文字颜色
int	TextColors(int i);			//根据数字修改颜色
void drawTheGameBox(); 			//绘制游戏界面
int *add(int item[]);   		//合并数字
int ifMove(int item[]); 		//判断是否能够移动数字,返回1能动，0不能动
void Gameplay();    			//开始游戏
void Replay();			       	//重新游戏
int if2n(int x);         		//判断x是否是2的n次方
int ifup();						//判断是否能够上移    可以上移（格子中的两个数相加是2的n次方），则返回1    不能移动，则返回0
int ifdown();					//判断是否能够下移    可以下移（格子中的两个数相加是2的n次方），则返回1    不能移动，则返回0
int ifleft();					//判断是否能够左移    可以左移（格子中的两个数相加是2的n次方），则返回1    不能移动，则返回0
int ifright();					//判断是否能够右移   可以右移（格子中的两个数相加是2的n次方），则返回1    不能移动，则返回0
int BOXmax();					//返回棋盘最大数
int Gamefaile();				//判断是否失败
int Gamewin();					//判断是否胜利
int keyboardControl(int key);   //键盘控制移动
void close();                   //关闭游戏
void title();                   //绘制标题（2048字符画）
void choice();                  //选择框
void Rabbit();					//绘制字符画
void regulation();              //游戏规则介绍
void explation();               //按键说明


/*******定  义  全  局  变  量*******/
int step=0;				//已执行步数
int score=0;			//存储游戏分数
long int Time;			//游戏运行时间
int BOX[4][4]={0,0,0,0, //游戏中的16个格子
               0,0,0,0,
               0,0,0,0,
               0,0,0,0};
HANDLE hOut;			//控制台句柄

/**
 * 获取屏幕光标位置
 */
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
/**
 * 文字颜色函数      此函数的局限性：1、只能Windows系统下使用   2、不能改变背景颜色
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        
	return 0;
}


/**
 * 根据数字修改颜色
 */
int TextColors(int number)
{
	switch (number)         //格子中出现的2和2的次方显示为不同颜色
	{      //数字1~15代表不同的文字颜色，超过15表示文字背景色
		case 2:
			return color(12);
			break;
		case 4:
			return color(11);
			break;
		case 8:
			return color(10);
			break;
		case 16:
			return color(14);
			break;
		case 32:
			return color(6);
			break;
		case 64:
			return color(5);
			break;
		case 128:
			return color(4);
			break;
		case 256:
			return color(3);
			break;
		case 512:
			return color(2);
			break;
		case 1024:
			return color(9);
			break;
		case 2048:
			return color(7);
			break;
	}
	return 0;
}

 /**
 * 绘制游戏界面  4*4的网格
 */
void drawTheGameBox()
{
	Rabbit();
	int i,j,k;
	gotoxy(66,3);   			//屏幕坐标位置
	color(1);      			
	printf("遊戲分數:");
	gotoxy(76,3);
	color(4);
	printf("%d",score);
	color(4);      			
	gotoxy(66,5);   			//屏幕坐标位置
	printf("執行步數:");
	gotoxy(76,5);
	color(1);
	printf("%d\n",step);
	color(14);       			
	for(j = 2;j <= 22;j += 5)   //打印棋盘边框
	{
		gotoxy(14,j);
		for(k = 1;k<50;k++)
		{
			printf("$");
		}
		printf("\n");
	}
	for (i = 3;i < 7;i ++)
	{
		gotoxy(14,i);
		printf("$           $           $           $           $");
	}
	for (i = 8;i<12;i++)
	{
		gotoxy(14,i);
		printf("$           $           $           $           $ ");
	}
	for (i = 13;i<17;i++)
	{
		gotoxy(14,i);
		printf("$           $           $           $           $ ");
	}
	for (i = 18;i<22;i++)
	{
		gotoxy(14,i);
		printf("$           $           $           $           $ ");
	}
    gotoxy(66,23);
	color(4);                                  
	printf("已用時：");  
	gotoxy(76,23);
	color(1);
	printf("%ds",time(NULL) - Time); //输出游戏运行时间
}

 /**
 * 合并数字
 */
int* add(int item[])
{
    int i = 0, j = 0;
    int tep[4] = {0, 0, 0, 0}, tmp[4] = {0, 0, 0, 0};
    for(i = 0; i < 4; i ++)
	{
        if(item[i] != 0)			//如果这个格子里有数字
		{              
            tep[j ++] = item[i];
        }
    }
	//把两个相邻的相同的数加起来
    for(i = 0; i < 4; i ++)
	{
//        if(tep[0] == 0) break;      //如果格子里没有数字，返回
        if(tep[i] == tep[i + 1])	//如果两个数字相同，则合并
		{
            tep[i] *= 2;        	//一个格子中的数字翻倍，另一个为空
            tep[i + 1] = 0;
            score=score+tep[i];		//加分，加的分数为消除的数字*2
        }
    }
    j = 0;
    for(i = 0; i < 4; i ++)
	{
        if(tep[i] != 0)
		{
            tmp[j ++] = tep[i];
        }
    }
    return (int *)(&tmp);   //tmp为指针的引用，*&指针本身可变
}


 /**
 * 判断能否移动数字,返回1能动，0不能动
 */
int ifMove(int item[])
{
    int i = 0;
    for(i = 0; i < 3; i ++)
	{
        if(item[i] != 0 && item[i] == item[i + 1])      //如果两个相邻两位上数字相同，能移动，返回1
        {
        	return 1;
		}
        if(item[i] == 0 && item[i + 1] != 0)            //如果两个相邻两位上，一个是空格子，一个上有数字，也能移动，返回1
        {
        	return 1;
		}
    }
    return 0;       //不能合并，返回0
}


 /**
 * 判断x是否是2的n次方,是2的n次方，返回1，否则返回0
 */
int if2n(int x)       
{
	int flag = 0;
	int n;
	int N = 1;   
	for(n = 1;n <= 11;n++)		//2的11次方是2048，游戏目标是达到2048
	{
		if(x == pow(2,n))       //计算2的n次方
		{
			flag = 1;
			if(n>N)
				N = n;
			return flag;
		}
	}
	return flag;
}

 /**
 * 判断是否能够上移    可以上移，则返回1    不能移动，则返回0
 */
int ifup()
{
	int i,j;
	int flag = 0;           //定义标志变量，只有0或1
	for(j = 0;j < 4;j ++)
		for(i = 0;i < 3;i ++)
		{
			if((if2n(BOX[i][j] + BOX[i+1][j]) == 1) && BOX[i+1][j])     //如果上下两个格子相加是2的n次方，并且下面的格子中有数
			{
				flag = 1;                                               //可以上移
			}
		}
		return flag;                                                    //返回1表示可以上移，返回0表示不能上移
}

 /**
 * 判断是否能够下移    可以下移，则返回1    不能移动，则返回0
 */
int ifdown()
{
	int i,j;
	int flag = 0;
	for(j = 0;j < 4;j ++)
		for(i = 3;i > 0;i --)
		{
			if((if2n(BOX[i][j] + BOX[i-1][j]) == 1) && BOX[i-1][j])     //如果上下两个格子相加是2的n次方，并且上面的格子中有数
			{
				flag = 1;                                               //可以下移
			}
		}
		return flag;                                                    //返回1表示可以下移，返回0表示不能下移
}

 /**
 * 判断是否能够左移    可以左移，则返回1    不能移动，则返回0
 */
int ifleft()
{
	int i,j;
	int flag = 0;
	for(i = 0;i < 4;i ++)
		for(j = 0;j < 3;j ++)
		{
			if((if2n(BOX[i][j] + BOX[i][j+1]) == 1) && BOX[i][j+1])     //如果左右两个格子相加是2的n次方，并且右面的格子中有数
			{
				flag = 1;                                               //可以左移
			}
		}
		return flag;                                                    //返回1表示可以左移，返回0表示不能左移
}

 /**
 * 判断是否能够右移   可以右移，则返回1    不能移动，则返回0
 */
int ifright()
{
	int i,j;
	int flag = 0;
	for(i = 0;i < 4;i ++)
		for(j = 3;j > 0;j --)
		{
			if((if2n(BOX[i][j] + BOX[i][j-1]) == 1) && BOX[i][j-1])     //如果左右两个格子相加是2的n次方，并且左面的格子中有数
			{
				flag = 1;                                               //可以下右移
			}
		}
		return flag;                                                    //返回1表示可以右移，返回0表示不能右移
}

 /**
 * 返回棋盘最大数
 */
int BOXmax()
{
	int max = BOX[0][0];       	 	//初始化BOX数组
	int i,j;
	for(i = 0;i < 4;i ++)      	//遍历整个数组
	{
		for(j = 0;j < 4;j ++)
		{
			if(BOX[i][j] > max) 	//如果数组中有数值大于max的值
			{
				max = BOX[i][j];    //将数组中的值赋值给max，这样找出数组中的最大数
			}
		}
}
	return max;                     //返回max的值。也就是当前棋盘中的最大值
}

 /**
 * 判断是否失败   加一个输出棋盘最大数
 */
int Gamefaile()
{
	int flag = 0;
	int max;
	if(ifup() + ifdown() + ifleft() + ifright() == 0)				//当上下左右都不能移动的时候，游戏失败
//	if(ifMove(BOX))
	{
		system("cls");
		gotoxy(34,3);
		color(14);
		printf("合并出的最大数是：");
		gotoxy(52,3);
		color(11);
		max = BOXmax();
		printf("%d",max);
		gotoxy(19,6);
		color(4);   //暗红色
    	printf("     ■■■■■    ■         ■    ■■     \n");  //输出end字符画
    	gotoxy(19,7);
    	printf("     ■            ■■       ■    ■  ■   \n");
    	gotoxy(19,8);
        printf("     ■            ■ ■      ■    ■    ■   \n");
        gotoxy(19,9);
		printf("     ■            ■  ■     ■    ■     ■  \n");
		gotoxy(19,10);
        printf("     ■■■■      ■   ■    ■    ■      ■  \n");
        gotoxy(19,11);
        printf("     ■            ■    ■   ■    ■     ■  \n");
        gotoxy(19,12);
		printf("     ■            ■     ■  ■    ■    ■   \n");
		gotoxy(19,13);
		printf("     ■            ■      ■ ■    ■  ■  \n");
		gotoxy(19,14);
		printf("     ■■■■■    ■       ■■    ■■     \n");
		gotoxy(34,17);
		color(13);
		printf("无法移动，游戏失败！");                             //提示文字
		flag = 1;
	}
   	return flag;                //flag的值正常是0，返回1则表示游戏失败
}

 /**
 * 判断是否胜利
 */
int Gamewin()
{
	int flag = 0;
	if(BOXmax() == 2048)            //如果棋盘中的最大值为2048，达到目标，则游戏胜利
	{
		system("cls");
		gotoxy(1,6);
		color(2);   //暗绿色
    	printf("     ■             ■             ■       ■■■■■       ■          ■  \n");  //输出胜利win的字符画
    	gotoxy(1,7);
    	printf("      ■           ■■           ■            ■           ■ ■       ■  \n");
    	gotoxy(1,8);
        printf("       ■         ■  ■         ■             ■           ■  ■      ■  \n");
        gotoxy(1,9);
		printf("        ■       ■    ■       ■              ■           ■   ■     ■   \n");
		gotoxy(1,10);
        printf("         ■     ■      ■     ■               ■           ■    ■    ■  \n");
        gotoxy(1,11);
        printf("          ■   ■        ■   ■                ■           ■     ■   ■ \n");
        gotoxy(1,12);
		printf("           ■ ■          ■ ■                 ■           ■      ■  ■    \n");
		gotoxy(1,13);
		printf("            ■■          ■■                  ■           ■       ■ ■  \n");
		gotoxy(1,14);
		printf("             ■            ■               ■■■■■       ■          ■   \n");
		gotoxy(35,17);
		color(13);
		printf("胜利啦，你真棒！！！");
		flag = 1;
	}
	 return flag;                //flag的值正常是0，返回1则表示游戏胜利
}

 /**
 * 键盘控制移动
 */
int keyboardControl(int key) {
    int i = 0, j = 0;
    int *p;
    int tp[4] = {0, 0, 0, 0};
    switch(key)			//LEFT = 75, UP = 72, RIGHT = 77, DOWN = 80;
	{	
    	case 72: 		// up
        	for(i = 0; i < 4; i++)
			{
            	tp[0] = BOX[0][i];      //把一列数移到中间变量
            	tp[1] = BOX[1][i];
            	tp[2] = BOX[2][i];
            	tp[3] = BOX[3][i];
            	p = add(tp);            //获得合并之后的数值
           	 	if(!ifMove(tp))			//判断是否可以移动，可以移动，则新出现一个数字；不能移动但按键了，也不会出现新数字
//if(ifup())
				{
					j++;        		//向上移动
				}
           	 	BOX[0][i] = p[0];       //把处理好的中间变量移回来
            	BOX[1][i] = p[1];
            	BOX[2][i] = p[2];
            	BOX[3][i] = p[3];
        	}
        	return j != 4;              //当j不超过4的时候，可以执行up操作
    	case 80: 		// down
			j  = 0;
        	for(i = 0; i < 4; i++)
			{
            	tp[0] = BOX[3][i];
            	tp[1] = BOX[2][i];
            	tp[2] = BOX[1][i];
            	tp[3] = BOX[0][i];
            	p = add(tp);
           	 	if(!ifMove(tp))
				{
					j++;
				}
            	BOX[3][i] = p[0];
            	BOX[2][i] = p[1];
            	BOX[1][i] = p[2];
           	 	BOX[0][i] = p[3];
       	 	}
        	return j != 4;
    	case 75:		// left
			j = 0;
        	for(i = 0; i < 4; i++)
			{
            	tp[0] = BOX[i][0];
            	tp[1] = BOX[i][1];
            	tp[2] = BOX[i][2];
            	tp[3] = BOX[i][3];
            	p = add(tp);
          		if(!ifMove(tp))
				{
					j++;
				};
            	BOX[i][0] = p[0];
            	BOX[i][1] = p[1];
            	BOX[i][2] = p[2];
            	BOX[i][3] = p[3];
        	}
        	return j != 4;
    	case 77: 		// right
			j = 0;
        	for(i = 0; i < 4; i++)
			{
        	    tp[0] = BOX[i][3];
            	tp[1] = BOX[i][2];
           	 	tp[2] = BOX[i][1];
            	tp[3] = BOX[i][0];
            	p = add(tp);
				if(!ifMove(tp))
//				if(ifright() == 1)
				{
					j++;
				}
            	BOX[i][3] = p[0];
           	 	BOX[i][2] = p[1];
           	 	BOX[i][1] = p[2];
            	BOX[i][0] = p[3];
        	}
        	return j != 4;
		case 27:	//按ESC
			gotoxy(20,23);
			color(12);
			printf("确定退出游戏么? (y/n)");
			char c = getch();           //获得键盘输入
			if(c == 'y' ||c == 'Y')     //如果输入的是大写或者小写的y
			{
				exit(0);                //退出游戏
			}
			if(c == 'n'||c == 'N')      //如果输入的是大写或者小写的n
			{
				gotoxy(20,23);
				printf("                        ");   //继续游戏
			}
			break;
    	default: return 0;
    }
}

 /**
 * 开始游戏
 */
void Gameplay()
{
	system("cls");      			//清屏
	int i = 0, j = 0;
	Time = time(NULL);				//取当前时间为开始时间
    drawTheGameBox();               //绘制游戏界面
    int a,b;                        //BOX[][]数组的横纵坐标
    srand(time(NULL)); 				//设置随机数种子，初始化随机数
	do
	{
    	a = rand()%4;               //获得4*4棋盘中的随机位置
    	b = rand()%4;
	}while(BOX[a][b]!=0);           //一直到棋盘中没有空格
	if(rand() % 4 == 0)      		//2或4随机出现在空格处(最开始出现在棋盘上的2或4)
	{
		BOX[a][b] = 4;
    }
	else
	{
		BOX[a][b] = 2;
    }

    for(i = 0; i < 4; i ++)         //遍历整个网格
	{
        for(j = 0; j < 4; j ++)
		{
            if(BOX[i][j] == 0)      //如果网格中有空位，就继续下去
            {
            	continue;
			}
//            gotoxy(17 + j * 8 + 3 + (j * 2), i * 4 + (i + 5));  //设置棋子显示位置
			gotoxy(15 + j * 10 +8, 2 + i * 5 + 3);  //设置棋子显示位置
            int c = BOX[i][j];  //获得棋盘上BOX[i][j]上的数字
            TextColors(c);  //设置棋子的颜色，不同数字显示不同颜色
            printf("%d", c);    //打印棋子
        }
    }

    while(1) {
        while (kbhit())            			//kbhit()检查当前是否有键盘输入，有返回1，否则返回0
        {
            if(!keyboardControl(getch()))  //如果按下的按键不是在keyboardControl()方法中定义的，会没有反应，一直到按下定义的按键为止
            {
				continue;
			}
            drawTheGameBox();       		//绘制棋盘
            for(i = 0; i < 4; i ++)         //循环整个4*4的棋盘
			{
                for(j = 0; j < 4; j ++)
				{
                    if(BOX[i][j] == 0)      //如果棋盘中有空位，则可一直进行按键
                    {
						continue;
					}
					gotoxy(15 + j * 10 +8, 2 + i * 5 + 3);//合并后的数出现的位置
                    int c = BOX[i][j];
            		TextColors(c);
            		printf("%d", c);
                }
            }
			do{
    			a = rand()%4;
    			b = rand()%4;           //获得随机位置
			}while(BOX[a][b]!=0);
    		if(rand() % 4 == 0)       //2或4随机出现在空格处(进行方向操作合并之后，在空白处出现)
			{
				BOX[a][b] = 4;          //随机位置上设置为4
    		} else {
				BOX[a][b] = 2;          //随机位置上设置为2
    		}
    		step++;                 //进行计步
//            gotoxy(17 + b * 8 + 3 + (b * 2), a * 4 + (a + 5));//合并后的数出现的位置
			gotoxy(15 +  b * 10 + 8, 2 + a * 5 + 3);     //随机出现的2或4
			int c = BOX[a][b];
		    TextColors(c);
            printf("%d", c);   
	    }
	 	if(Gamefaile()+Gamewin() != 0)  //只要Gamefaile()或者Gamewin()任意一个函数返回1，也就是成功或是失败都会出现下面的内容
	    {
	    	int n;
	    	gotoxy(20,20);
			color(12);
			printf("我要重新玩一局-------1");
			gotoxy(45,20);
			printf("不玩了，退出吧-------2\n");
			gotoxy(43,21);
			color(11);
			scanf("%d", &n);
    		switch (n)
    		{
    			case 1:
        			Replay();         //重新游戏函数
        			break;
    			case 2:
        			close();    		//关闭游戏函数
        			break;
    		}
		}
	}
}

 /**
 * 重新游戏
 */

void Replay()
{
	system("cls");                  	//清屏
	score = 0,step = 0;                 //分数、步数归零
	memset(BOX,0,16*sizeof(int));       //初始化BOX数组
	Gameplay();                         //开始游戏
}
void title()
{
	color(1);         
    gotoxy(19,2);
    printf("■■■"); 
    gotoxy(19,3);
    printf("    ■");
    gotoxy(19,4);
    printf("■■■");
    gotoxy(19,5);
    printf("■   ");
    gotoxy(19,6);
    printf("■■■");
    
    color(1);
    gotoxy(27,2);
    printf("■■■■ "); 
    gotoxy(27,3);
    printf("■    ■ ");
    gotoxy(27,4);
    printf("■    ■ ");
    gotoxy(27,5);
    printf("■    ■ ");
    gotoxy(27,6);
    printf("■■■■ ");
    
    color(4);
    gotoxy(37,2);
    printf("■  ■"); 
    gotoxy(37,3);
    printf("■  ■");
    gotoxy(37,4);
    printf("■  ■");
    gotoxy(37,5);
    printf("■■■■");
    gotoxy(37,6);
    printf("    ■");
    
    color(4);
    gotoxy(47,2);
    printf("■■■■");
    gotoxy(47,3);
    printf("■    ■");
    gotoxy(47,4);
    printf("■■■■");
    gotoxy(47,5);
    printf("■    ■");
    gotoxy(47,6);
    printf("■■■■");
}

void Rabbit()
{
    color(1);
	gotoxy(66,10);
	printf("┏--┓  ┏--┓");
	gotoxy(66,11);
	printf("┃  ┃  ┃  ┃");
	gotoxy(66,12);
	printf("┃  ┃  ┃  ┃");
	gotoxy(65,13);
	printf("_┃"); 
	gotoxy(71,13);
	color(4);
	printf("ㄨ");
	color(1);
	gotoxy(75,13); 
	printf("┃_"); 
	gotoxy(64,14);
	printf("┃");
	gotoxy(77,14); 
	printf("┃");
	gotoxy(64,15);
	printf("┃");
	gotoxy(64,16);
	printf("┃");
	gotoxy(77,15);
	printf("┃");
	gotoxy(77,16);	
	printf("┃");
	gotoxy(64,17);
	printf("┃");
	gotoxy(77,17);
	printf("┃"); 
	gotoxy(64,18);
	printf("┗━━━━┳━━┳━━━━┛"); 
	gotoxy(68,19);
	printf("┏┫  ┣┓");
	gotoxy(66,20);
	printf("—┺┻━┻┻┹—");
	color(14);
	gotoxy(68,15);
	printf("◇   ◇");
	color(13);
	gotoxy(67,17);
	printf("●");
	gotoxy(74,17);  
	printf("●");
	color(12);
	gotoxy(71,17);
	printf("┻");
	
	color(4);
	gotoxy(2,10);
	printf("┏--┓  ┏--┓");
	gotoxy(2,11);
	printf("┃  ┃  ┃  ┃");
	gotoxy(2,12);
	printf("┃  ┃  ┃  ┃");
	color(14);
	gotoxy(7,13);
	printf("┻");
	color(4);
	gotoxy(1,13);
	printf("_┃");
	gotoxy(11,13);
	printf("┃ _");
	gotoxy(0,14);
	printf("┃");
	gotoxy(13,14);
	printf("┃");
	gotoxy(0,15);
	printf("┃");
	gotoxy(13,15);
	printf("┃");
	gotoxy(0,16);
	printf("┃");
	gotoxy(13,16);
	printf("┃");
	gotoxy(0,17);
	printf("┃");
	gotoxy(13,17);
	printf("┃");
	gotoxy(0,18);
	printf("┗━━━━┳━━┳━━━━┛");	
	gotoxy(3,19);
	printf("┏┫    ┣┓");
	gotoxy(2,20);
	printf("—┺━┻━┻┹—");
	color(1);
	gotoxy(5,15);
	printf("○   ○");
	color(13);
	gotoxy(3,17);
	printf("〃");
	gotoxy(11,17);
	printf("〃");
	color(14);
	gotoxy(7,17);
	printf("ㄨ");
}


 /**
 * 主函数。程序入口
 */
int main() {
//	system("cls");      //清屏
    title();            //打印标题
    Rabbit();           //打印字符画
    choice();           //菜单选项
    
}

 void choice()
{
	int n;
    int i,j = 1;
    gotoxy(27,8);
    color(1);
    printf("賽 ");
    gotoxy(31,8);
    color(4);
    printf(" 博");
    color(1);
    gotoxy(36,8);
    printf(" 2");
    color(4);
    gotoxy(40,8);
    printf(" 0");
    color(1);
    gotoxy(44,8);
    printf(" 4");
    color(4);
    gotoxy(48,8);
    printf(" 8");
	color(14);          			
    for (i = 9; i <= 20; i++)   
	{
		for (j = 15; j <= 60; j++)  
		{
			gotoxy(j, i);
			if (i == 9 || i == 20){
				color(14); 
				printf("︾");
			}	
			else if (j == 15 || j == 60)
					printf("$");
			}	
		}
	
	
	color(12);
	gotoxy(28, 12);
	printf("[1]START");
	gotoxy(37, 14);
	printf("[2]REGULATION");
	gotoxy(23, 16);
	printf("[3]EXPLANATION");
	gotoxy(40, 18);
	printf("[4]EXIT");
	gotoxy(30,22);
	color(14);
	printf("請選擇[1 2 3 4]:[ ]\b\b");
    scanf("%d", &n);    
    switch (n)
    {
    	case 1:    
			Gameplay();    
        	break;
    	case 2:   
			regulation();  	
        	break;
    	case 3:  
    		explation();
        	break;
    	case 4:	
    		exit(0);
        	break;
    }
}


 /**
 * 退出
 */
void close()
{
    exit(0);
}

 /**
 * 游戏规则介绍
 */
void regulation()
{
	int i,j = 1;
    system("cls");
    color(14);
    gotoxy(34,3);
    printf("遊戲規則");
    color(14);
    for (i = 6; i <= 20; i++)   //输出上下边框===
	{
		for (j = 15; j <= 67; j++)  //输出左右边框||
		{
			gotoxy(j, i);
			if (i == 6 || i == 20) printf("︾");
			else if (j == 15 || j == 67) printf("$");
		}
	}
    color(14);
    gotoxy(18,8);
    printf("tip1: 玩家選擇的方向上,若有相同的數字則合並");
    color(11);
    gotoxy(18,11);
    printf("tip2: 每移動一步，空位隨機出現一個2或4");
    color(4);
    gotoxy(18,14);
    printf("tip3: 棋盤被數字填滿，無法進行有效移動，遊戲失敗");
    color(5);
    gotoxy(18,17);
    printf("tip4: 棋盤上出現2048，遊戲勝利");
    getch();                //按任意键返回主界面
    system("cls");
    main();
}

 /**
 * 按键说明
 */
void explation()
{
	gotoxy(20,22);
	color(13);
	printf("①↑、↓、←、→方向鍵進行遊戲操作!");
	gotoxy(20, 24);
	printf("②ESC鍵退出遊戲");
//	color(8);
	getch();                //按任意键返回主界面
	system("cls");
	main();
}

