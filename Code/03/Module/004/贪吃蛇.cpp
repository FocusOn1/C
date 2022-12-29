#include<stdafx.h>			//vc自带头文件
#include<stdio.h>			//标准输入输出函数库
#include<time.h>			//用于获得随机数
#include<windows.h>			//控制dos界面
#include<stdlib.h>			//即standard library标志库头文件，里面定义了一些宏和通用工具函数
#include<conio.h>			//接收键盘输入输出

/*******宏  定  义*******/
#define U 1
#define D 2
#define L 3 
#define R 4      //蛇的状态，U：上 ；D：下；L:左 R：右

/*******定  义  全  局  变  量 *******/
typedef struct snake 		//蛇身的一个节点
{
    int x;
    int y;
    struct snake *next;
}snake;
int score=0,add=10;			//总得分与每次吃食物得分
int HighScore = 0;			//最高分
int status,sleeptime=200;	//蛇前进状态，每次运行的时间间隔
snake *head, *food;			//蛇头指针，食物指针
snake *q;					//遍历蛇的时候用到的指针
int endgamestatus=0;		//游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。
HANDLE hOut;				//控制台句柄


/*******函  数  声  明 *******/
void gotoxy(int x,int y);   //设置光标位置
int color(int c);           //更改文字颜色
void printsnake();          //字符画---蛇
void welcometogame();       //开始界面
void createMap();           //绘制地图
void scoreandtips();		//游戏界面右侧的得分和小提示
void initsnake();           //初始化蛇身，画蛇身
void createfood();          //创建并随机出现食物
int biteself();             //判断是否咬到了自己
void cantcrosswall();       //设置蛇撞墙的情况
void speedup();				//加速
void speeddown();			//减速
void snakemove();           //控制蛇前进方向
void keyboardControl();     //控制键盘按键
void Lostdraw();            //游戏结束界面
void endgame();             //游戏结束
void choose();				//游戏失败之后的选择
void File_out();            //在文件中读取最高分
void File_in();            	//储存最高分进文件
void explation();           //游戏说明

/**
 * 设置光标位置
 */
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
 
/**
 * 文字颜色函数      此函数的局限性：1、只能Windows系统下使用   2、不能改变背景颜色
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}

/*
*   字符画---蛇
*/
void printsnake()
{
	gotoxy(35,1);
	color(6);
	printf("/^\\/^\\");      //蛇眼睛

	gotoxy(34,2);
	printf("|__|  O|");      //蛇眼睛

	gotoxy(33,2);
	color(2);
	printf("_");

	gotoxy(25,3);
	color(12);
	printf("\\/");      	//蛇信

	gotoxy(31,3);
	color(2);
	printf("/");

	gotoxy(37,3);
	color(6);
	printf(" \\_/");     	//蛇眼睛

	gotoxy(41,3);
	color(10);
	printf(" \\");

	gotoxy(26,4);
	color(12);
	printf("\\____");   	//舌头

	gotoxy(32,4);
	printf("_________/");

	gotoxy(31,4);
	color(2);
	printf("|");

	gotoxy(43,4);
	color(10);
	printf("\\");

	gotoxy(32,5);
	color(2);
	printf("\\_______");    //蛇嘴

	gotoxy(44,5);
	color(10);
	printf("\\");

	gotoxy(39,6);
	printf("|     |                  \\");  //下面都是画蛇身

	gotoxy(38,7);
	printf("/      /                   \\");

	gotoxy(37,8);
	printf("/      /                    \\ \\");

	gotoxy(35,9);
	printf("/      /                       \\ \\");

	gotoxy(34,10);
	printf("/     /                          \\  \\");

	gotoxy(33,11);
	printf("/     /             _----_         \\   \\");

	gotoxy(32,12);
	printf("/     /           _-~      ~-_         |  |");

	gotoxy(31,13);
	printf("(      (        _-~    _--_    ~-_     _/  |");

	gotoxy(32,14);
	printf("\\     ~-____-~    _-~    ~-_    ~-_-~    /");

	gotoxy(33,15);
	printf("~-_           _-~          ~-_       _-~");

	gotoxy(35,16);
	printf("~--______-~                ~-___-~");
}


/**
 * 开始界面
 */
void welcometogame()
{
	int n;
	int i,j = 1;
	gotoxy(43,18);
	color(11);
	printf("贪 吃 蛇 大 作 战");
	color(14);          			//黄色边框
	for (i = 20; i <= 26; i++)   	//输出上下边框┅
	{
		for (j = 27; j <= 74; j++)  //输出左右边框┇
		{
			gotoxy(j, i);
			if (i == 20 || i == 26)
			{
				printf("-");
            }
			else if (j == 27 || j == 74)
            {
				printf("|");
            }
		}
	}
	color(12);
	gotoxy(35, 22);
	printf("1.开始游戏");
	gotoxy(55, 22);
	printf("2.游戏说明");
	gotoxy(35, 24);
	printf("3.退出游戏");
	gotoxy(29,27);
	color(3);
	printf("请选择[1 2 3]:[ ]\b\b");        //\b为退格，使得光标处于[]中间
	color(14);
    scanf("%d", &n);    		//输入选项
    switch (n)
    {
    	case 1:
    		system("cls");
			createMap();        //创建地图
    		initsnake();        //初始化蛇身
    		createfood();       //创建食物
    		keyboardControl();	//按键控制
        	break;
    	case 2:
        	
        	break;
    	case 3:
        	exit(0);     		//退出游戏
        	break;
		default:				//输入非1~3之间的选项
			color(12);
			gotoxy(40,28);
			printf("请输入1~3之间的数!");
			getch();			//输入任意键
			system("cls");		//清屏
			printsnake();
			welcometogame();
    }
}

/**
 * 创建地图
 */
void createMap()
{
    int i,j;
    for(i=0;i<58;i+=2)		//打印上下边框
    {
        gotoxy(i,0);
		color(5);			//深紫色的边框
        printf("□");
        gotoxy(i,26);
        printf("□");
    }
    for(i=1;i<26;i++)		//打印左右边框
    {
        gotoxy(0,i);
        printf("□");                        
        gotoxy(56,i);
        printf("□");        
    }
	for(i = 2;i<56;i+=2)	//打印中间网格
	{
		for(j = 1;j<26;j++)
		{
			gotoxy(i,j);
			color(3);
			printf("■");
		}
	}
}

 /**
 *  游戏界面右侧的得分和小提示
 */
void scoreandtips()
{
	File_out();
	gotoxy(64,4);
	color(11);
	printf("☆最高记录☆：%d",HighScore);
	gotoxy(64,8);
	color(14);
	printf("得分：%d  ",score);
	color(13);
	gotoxy(73,11);
	printf("小 提 示");
	gotoxy(60,13);
	color(6);
	printf("╬ ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ ╬");
	gotoxy(60,25);
	printf("╬ ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ ╬");
	color(3);
	gotoxy(64,14);
	printf("每个食物得分：%d分",add);
	gotoxy(64,16);
	printf("不能穿墙，不能咬到自己");
	gotoxy(64,18);
	printf("用↑ ↓ ← →分别控制蛇的移动");
	gotoxy(64,20);
	printf("F1 为加速，F2 为减速");
	gotoxy(64,22);
	printf("space：暂停游戏");
	gotoxy(64,24);
    printf("ESC ：退出游戏");
}

 /**
 * 初始化蛇身，画蛇身
 */
void initsnake()
{
    snake *tail;
    int i;
    tail=(snake*)malloc(sizeof(snake));//从蛇尾开始，头插法，以x,y设定开始的位置//
    tail->x=24;         	//蛇的初始位置（24,5）
    tail->y=5;
    tail->next=NULL;
    for(i=1;i<=4;i++)       //设置蛇身，长度为5
    {
        head=(snake*)malloc(sizeof(snake)); //初始化蛇头
        head->next=tail;        //蛇头的下一位为蛇尾
        head->x=24+2*i;         //设置蛇头位置
        head->y=5;
        tail=head;              //蛇头变成蛇尾，然后重复循环
    }
    while(tail!=NULL)		//从头到尾，输出蛇身
    {
        gotoxy(tail->x,tail->y);
		color(14);
        printf("★");       //输出蛇身，蛇身使用★组成
        tail=tail->next;    //蛇头输出完毕，输出蛇头的下一位，一直输出到蛇尾
    }
}

 /**
 * 随机出现食物
 */
void createfood()
{
    snake *food_1;
    srand((unsigned)time(NULL));        	//初始化随机数
    food_1=(snake*)malloc(sizeof(snake));   //初始化food_1
    while((food_1->x%2)!=0)    				//保证其为偶数，使得食物能与蛇头对其，然后食物会出现在网格线上
    {
        food_1->x=rand()%52+2;              //食物随机出现
    }
    food_1->y=rand()%24+1;
    q=head;
    while(q->next==NULL)
    {
        if(q->x==food_1->x && q->y==food_1->y) //判断蛇身是否与食物重合
        {
            free(food_1);               //如果蛇身和食物重合，那么释放食物指针
            createfood();               //重新创建食物
        }
        q=q->next;
    }
    gotoxy(food_1->x,food_1->y);
    food=food_1;
	color(12);
    printf("●");           //输出食物
}
 
 /**
 * 判断是否咬到了自己
 */
int biteself()
{
    snake *self;            //定义self为蛇身上的一个节点
    self=head->next;        //self是蛇头之外的蛇身上的节点
    while(self!=NULL)
    {
        if(self->x==head->x && self->y==head->y)    //如果self和蛇身上的节点重合
        {
            return 1;       //返回1
        }
        self=self->next;
    }
    return 0;
}

 /**
 * 设置蛇撞墙的情况
 */
void cantcrosswall()
{  
    if(head->x==0 || head->x==56 ||head->y==0 || head->y==26) //如果蛇头碰到了墙壁
    {
        endgamestatus=1;        //返回第一种情况
 
    }
}



/**
 *  加速，蛇吃到食物会自动提速，并且按F1会加速
 */
void speedup()
{
	if(sleeptime>=50)
	{
		sleeptime=sleeptime-10;
		add=add+2;

    }
}

/**
 *  加速，按F2会减速
 */
void speeddown()
{
	if(sleeptime<350)               //如果时间间隔小于350
    {
        sleeptime=sleeptime+30;     //时间间隔加上30
        add=add-2;                  //每吃一次食物的得分减2

    }
}

/**
 *  控制方向    问题：为什么要设置status，而不使用前两章中接收键盘按键的方法
 */
void snakemove()	//蛇前进,上U,下D,左L,右R
{
	snake * nexthead;
    cantcrosswall();
    nexthead=(snake*)malloc(sizeof(snake));		//为下一步开辟空间
    if(status==U)
    {
        nexthead->x=head->x;        //向上前进时，x坐标不动，y坐标-1
        nexthead->y=head->y-1;
        nexthead->next=head;
        head=nexthead;
        q=head;                 //指针q指向蛇头
        if(nexthead->x==food->x && nexthead->y==food->y)	//如果下一个有食物 下一个位置的坐标和食物的坐标相同
        {
            
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
				color(14);
                printf("★");       //原来食物的位置，从●换成★
                q=q->next;          //指针q指向的蛇身的下一位也执行循环里的操作
				
            }
            score=score+add;        //吃了一个食物，在总分上加上食物的分
			speedup();
            createfood();           //创建食物
        }
        else                        
        {
            while(q->next->next!=NULL)	//如果没遇到食物
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");           //蛇正常往前走，输出当前位置的蛇身
                q=q->next;              //继续输出整个蛇身
            }
            gotoxy(q->next->x,q->next->y);  //经过上面的循环，q指向蛇尾，蛇尾的下一位，就是蛇走过去的位置
			color(3);
            printf("■");
            free(q->next);      //进行输出■之后，释放指向下一位的指针
            q->next=NULL;       //指针下一位指向空
        }
    }
    if(status==D)
    {
        nexthead->x=head->x;        //向下前进时，x坐标不动，y坐标+1
        nexthead->y=head->y+1;
        nexthead->next=head;
        head=nexthead;
        q=head;
        if(nexthead->x==food->x && nexthead->y==food->y)  //有食物
        {
            
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q=q->next;
            }
            score=score+add;
			speedup();
            createfood();
        }
        else                               //没有食物
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q=q->next;
            }
            gotoxy(q->next->x,q->next->y);
			color(3);
            printf("■");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==L)
    {
        nexthead->x=head->x-2;        //向左前进时，x坐标向左移动-2，y坐标不动
        nexthead->y=head->y;
        nexthead->next=head;
        head=nexthead;
        q=head;
        if(nexthead->x==food->x && nexthead->y==food->y)//有食物
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q=q->next;
            }
            score=score+add;
			speedup();
            createfood();
        }
        else                                //没有食物
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q=q->next;        
            }
            gotoxy(q->next->x,q->next->y);
			color(3);
            printf("■");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==R)
    {
        nexthead->x=head->x+2;        //向右前进时，x坐标向右移动+2，y坐标不动
        nexthead->y=head->y;
        nexthead->next=head;
        head=nexthead;
        q=head;
        if(nexthead->x==food->x && nexthead->y==food->y)//有食物
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q=q->next;
            }
            score=score+add;
			speedup();
            createfood();
        }
        else                                         //没有食物
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("★");
                q=q->next;        
            }
            gotoxy(q->next->x,q->next->y);
			color(3);
            printf("■");
            free(q->next);
            q->next=NULL;
        }
    }
    if(biteself()==1)       //判断是否会咬到自己
    {
        endgamestatus=2;

    }
}


/**
 * 控制键盘按键
 */
void keyboardControl()
{
	status=R;       //初始蛇向右移动
    while(1)
    {
		scoreandtips();
        if(GetAsyncKeyState(VK_UP) && status!=D)            //GetAsyncKeyState函数用来判断函数调用时指定虚拟键的状态
        {
            status=U;           //如果蛇不是向下前进的时候，按上键，执行向上前进操作
        }
        else if(GetAsyncKeyState(VK_DOWN) && status!=U)     //如果蛇不是向上前进的时候，按下键，执行向下前进操作
        {
            status=D;
        }
        else if(GetAsyncKeyState(VK_LEFT)&& status!=R)      //如果蛇不是向右前进的时候，按左键，执行向左前进
        {
            status=L;
        }
        else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)     //如果蛇不是向左前进的时候，按右键，执行向右前进
        {
            status=R;
        }
        if(GetAsyncKeyState(VK_SPACE))		//按暂停键，执行pause暂停函数
        {
            while(1)
			{
				Sleep(300); //sleep()函数，头文件#include <unistd.h>  另进程暂停，知道达到里面设定的参数的时间。
				if(GetAsyncKeyState(VK_SPACE))      //按空格键暂停
				{
					break;
				}
				
			}       
        }
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            endgamestatus=3;    //按esc键，直接到结束界面
            break;
        }
        else if(GetAsyncKeyState(VK_F1))    //按F1键，加速
        {
            speedup();
        }
        else if(GetAsyncKeyState(VK_F2))    //按F2键，减速
        {
        	speeddown();
            
        }
        Sleep(sleeptime);
        snakemove();
    }
}




/**
 * 在文件中读取最高分
 */
void File_out()
{
	FILE *fp;
	fp = fopen("save.txt", "a+");       //打开文件save.txt
	fscanf(fp, "%d", &HighScore);       //把文件中的最高分读出来
	fclose(fp);                         //关闭文件
}






/**
* 主函数
*/
int main()
{	
	system("mode con cols=100 lines=30");   //设置控制台的宽高
	printsnake();
    welcometogame();
	File_out();
    keyboardControl();
	return 0;
}
