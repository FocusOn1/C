// ̰����.cpp : Defines the entry point for the console application.

//#include "stdafx.h"

#include<stdio.h>			//��׼�������������
#include<time.h>			//���ڻ�������
#include<windows.h>			//����dos����
#include<stdlib.h>			//��standard library��־��ͷ�ļ������涨����һЩ���ͨ�ù��ߺ���
#include<conio.h>			//���ռ����������
/***�궨��***/

#define U 1

#define D 2

#define L 3

#define R 4



/***����ȫ�ֱ���***/

typedef struct snake

{

	int x;

	int y;

	struct snake *next;

}snake;

int score=0,add=10;

int HighScore=0;

int status,sleeptime=200;

snake *head,*food;

snake *q;

int endgamestatus=0;

HANDLE hOut;



//��������//

void gotoxy(int x,int y);

int color(int c);

void printsnake();

void welcometogame();

void createMap();

void scoreandtips();

void initsnake();

void createfood();

void biteself();

void cantcrosswall();

void speedup();

void speeddown();

void snakemove();

void keyboradControl();

void Lostdraw();

void endgame();

void choose();

void File_out();

void File_in();

void explation();



/**

 *������ɫ����

 */

int color(int c)

{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);

	return 0;

}



/**

 *���ù��λ��

 */

void gotoxy(int x,int y)

{

	COORD c;

	c.X=x;

	c.Y=y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);

}



/*

*   �ַ���---��

*/

void printsnake()

{

	gotoxy(35,1);

	color(15);

	printf("/^\\/^\\");      //���۾�



	gotoxy(34,2);

	printf("|__|  O|");      //���۾�



	gotoxy(33,2);

	color(14);

	printf("_");



	gotoxy(25,3);

	color(3);

	printf("\\/");      		//����



	gotoxy(31,3);

	color(4);

	printf("/");



	gotoxy(37,3);

	color(5);

	printf(" \\_/");     		//���۾�



	gotoxy(41,3);

	color(6);

	printf(" \\");



	gotoxy(26,4);

	color(7);

	printf("\\____");   		//��ͷ



	gotoxy(32,4);

	printf("_________/");



	gotoxy(31,4);

	color(8);

	printf("|");



	gotoxy(43,4);

	color(9);

	printf("\\");



	gotoxy(32,5);

	color(10);

	printf("\\_______");     //����



	gotoxy(44,5);

	color(11);

	printf("\\");



	gotoxy(39,6);

	printf("|     |                  \\");  //���涼�ǻ�����



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
������
*/
int main()
{
	system("mode con cols=100 lines=30");//���ÿ���̨�Ŀ��
	printsnake();//�����ַ���
	welcometogame();//��ӭ����
	File_out();//��ȡ�ļ���Ϣ
	keyboardControl();//
	return 0;
}
//3.5.3
/**
��ӭ����
*/
void welcometogame()
{
	int n;
	int i,j = 1;
	gotoxy(43,18);
	color(11);
	printf("����̰���ߴ���ս");
	color(14);
	for(i = 20;i <= 26;i++)
	{
		for(j = 27;j <= 74;j++)
		{
			gotoxy(j,i);
			if(i==20 || i==26)
			{
				printf("-");
			}
			else if(j==27 || j==74){
				printf("|");
			}
		}
	}
	color(12);
	gotoxy(35,22);
	printf("1.��ʼ��Ϸ");
	gotoxy(55,22);
	printf("2.��Ϸ˵��");
	gotoxy(35,24);
	printf("3.�˳���Ϸ");
	gotoxy(29,27);
	color(3);
	printf("��ѡ��[1 2 3]��[ ]\b\b");
	color(14);
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			system("cls");
			createMap();
			initsnake();
			createfood();
			break;
		case 2:
			break;
		case 3:
			exit(0);//�˳�����
			break;
		default:
			color(12);
			gotoxy(40,28);
			printf("������1~3֮�������");
			getch();//���������
			system("cls");//����
			printsnake();
			welcometogame();

	}
}
/**
������ͼ
*/
void createMap()
{
	int i,j;
	for(i = 0;i < 58;i+=2)
	{
		gotoxy(i,0);
		color(5);
		printf("��");
		gotoxy(i,26);
		printf("��");
	}
	for(i=1;i<26;i++)
	{
		gotoxy(0,i);
		printf("��");
		gotoxy(56,i);
		printf("��");
	}
	for(i=2;i<56;i+=2)
	{
		for(j=1;j<26;j++)
		{
			gotoxy(i,j);
			color(3);
			printf("��\n\n");
		}
	}
}
/**
��Ϸ�����Ҳ�ĵ÷ֺ�С��ʾ
*/
void scoreandtips()
{
	File_out();
	gotoxy(64,4);
	color(11);
	printf("����߼�¼�%d",HighScore);
	gotoxy(64,8);
	color(14);
	printf("�÷֣�%d ",score);
	color(13);
	gotoxy(73,11);
	printf("С��ʾ");
	gotoxy(60,13);
	color(6);
	printf("�p�����������������������p");//��ӡ�߿�
	gotoxy(60,25);
	printf("�p�����������������������p");
	color(3);
	gotoxy(64,14);
	printf("ÿ��ʳ��÷֣�%d��",add);
	gotoxy(64,16);
	printf("����ײǽ������ҧ���Լ�");
	gotoxy(64,18);
	printf("�á��������ֱ�����ߵ��ƶ�");
	gotoxy(64,20);
	printf("Space:��ͣ��Ϸ");
	gotoxy(64,24);
	printf("Esc:�˳���Ϸ");
}
/**
���ļ��ж�ȡ��߷�
*/
void File_out()
{
	FILE *fp;
	fp = fopen("save.txt","a+");//���ļ�save.txt
	fscanf(fp,"%d",&HighScore);//���ļ��е���߷ֶ�����
	fclose(fp);//�ر��ļ�
}
/**
��ʼ������������
*/
void initsnake()
{
	snake *tail;
	int i;
	tail=(snake*)malloc(sizeof(snake));//����ʼ��ͷ�巨����x��y�趨��ʼ��λ��
	tail->x=24;//�ߵĳ�ʼλ�ã�24��5��
	tail->y=5;
	tail->next=	NULL;
	for(i=1;i<=4;i++)//������������Ϊ25
	{
		head=(snake*)malloc(sizeof(snake));//��ʼ����ͷ
		head->next=tail;//��ͷ��һλΪ��β
		head->x=24+2*i;//������ͷλ��
		head->y=5;
		tail=head;//��ͷ�����β��Ȼ���ظ�ѭ��
	}
	while(tail!=NULL)//��ͷ��β�������β
	{
		gotoxy(tail->x,tail->y);
		color(14);
		printf("��");//�����������ʹ�á����
		tail=tail->next;//��ͷ�����ϣ������ͷ����һλ��һֱ�������β
	}
}
/*
�������ʳ��
*/
void createfood()
{
	snake *food_1;
	srand((unsigned)time(NULL));//��ʼ�������
	food_1=(snake*)malloc(sizeof(snake));//��ʼ��food_1
	//��֤��Ϊż����ʹ��ʳ��������ͷ���룬Ȼ��ʳ����������������
	while((food_1->x%2)!=0)
	{
		food_1->x=rand()%52+2;//����ʳ���x����������֣�ʳ���x������2~53֮��
	}
	food_1->y=rand()%24+1;//ʳ���y������1~24֮��
	q=head;
	while(q->next!=NULL)
	{
		if(q->x==food_1->x && q->y==food_1->y)//�ж������Ƿ��ʳ���غ�
		{
			free(food_1);//��������ʳ���غϣ���ô�ͷ�ʳ��ָ��
			createfood();//���´���ʳ��
		}
		q=q->next;
	}
	gotoxy(food_1->x,food_1->y);//����ʳ���λ��
	food=food_1;
	color(12);
	printf("��");//���ʳ��
}
/**
*�ж��Ƿ�ҧ���Լ�
*/
int biteself()
{
       snake *self;//����selfΪ�����ϵ�һ���ڵ�
       self = head->next;//self����ͷ֮��������ϵĽڵ�
       while(self!NULL)
       {
              if(self->x == head->x  &&  self->y==head->y)//���self����ͷ�ϵĽڵ��غ�
              {
                     return 1;//����1����ҧ���Լ�����Ϸʧ��
              }
              self=self->next;//ѭ�������ϵ�ÿһ���ڵ�
       }
       return 0;
}
/**
*�ж��Ƿ�ײǽ
*/
void cantcrosswall()
{
       if(head->x==0 || head->x==56 || head->y==0 || head->y==26)//�����ͷײ����ǽ��
       {
              endgamestatus=1;//������Ϸ�����ĵ�һ�����������ײ��ǽ
}
/**
*���٣��߳Ե�ʳ����߰�F1�������Զ�����
*/
void speedup()
{
       if(sleeptime>=50)//���ʱ�������ڵ���50
       {
              sleeptime=sleeptime-10;//ʱ������10
              add=add+2;//ÿ��һ��ʳ��ĵ÷ּ�2
       }
}
/**
*���٣���F2�������Զ�����
*/
void speeddpwn()
{
       if(sleeptime<350)//���ʱ����С��350
       {
              sleeptime=sleeptime+30;//ʱ��������30
              add=add-2;//ÿ��һ��ʳ��ĵ÷ּ�2
              if(sleeptime==350)
              {
                     add=1;//��֤��ͷ�Ϊ1
              }
       }
}
/**
*���Ʒ���
*/
void snakemove()//��ǰ������U��D��L��R
{
       snake *nexthead;
       cantcrosswall();
       nexthead=(snake*)malloc(sizeof(snake));//Ϊ��һ�����ٿռ�
       if(status==U)
       {
              nexthead->x=head->x;//����ǰ��ʱ��x���겻�䣬y����-1
              nexthead->y=head->y-1;
              nexthead->next=head;
              head=nexthead;
              q=head;//ָ��qָ����ͷ
			  //�����һ��λ������ʳ���һ��λ�õ������ʳ���������ͬ 
			  if(nexthead->x==food->x && nexthead->y==food->y)
              {
                     while(q!=NULL)
                     {
                            gotoxy(q->x,q->y);
                            color(14);
                            printf("��");//ԭ��ʳ���λ�ã���ʳ��񻻳��ߡ�
                            q=q->next;//ָ��qָ����������һλ��Ҳִ��ѭ����Ĳ���
                     }
                     score=score+add;//����һ��ʳ����ܷ��ϼ���ʳ��ķ�
                     speedup();
                     creatfood();//����ʳ��
              }else{
                     while(q->next->next!=NULL)//���û����ʳ��
                     {
                            gotoxy(q->x,q->y);
                            color(14);
                            printf("��");//��������ǰ�ߣ������ǰλ�õ�����
                            q=q->next;//���������������
                     }
					 //���������ѭ����qָ����β����β����һλ���������߹�ȥ��λ��
                     gotoxy(q->next->x,q->next->y);
                     color(3);
                     printf("��");
                     free(q->next);//�����֮���ͷ�ָ����һλ��ָ��
                     q->next=NULL;//ָ����һλָ���
              }
       }
       if(status==D)
       {
              nexthead->x=head->x;//����ǰ��ʱ��x���겻�䣬y����+1
              nexthead->y=head->y+1;
              nexthead->next=head;
              head=nexthead;
              q=head;
              if(nexthead->x==food->x && nexthead->y==food->y)//��ʳ��
              {
                     while(q!=NULL)
                     {
                            gotoxy(q->x,q->y);//ʳ���������ϵ�һ���֣������߳Ե�
                            color(14);
                            printf("��");
                            q=q->next;
                     }
                     score=score+add;//�÷�
                     speedup();//����
                     creatfood();//��������ʳ��
              }else{//û��ʳ��
                     while(q->next->next!NULL){
                            gotoxy(q->x,q->y);
                            color(14);
                            printf("��");
                            q=q->next;                           
                     }
                     gotoxy(q->next->y,q->next->x);//���߹���·�߱������ԭ�е�ͼ��
                     color(3);
                     printf("��");
                     free(q->next);//�ͷ�ָ��
                     q->next=NULL;
              }
       }
       if(status==L)
       {
              nexthead->x=head->x-2;//����ǰ��ʱ��x���������ƶ�-2��y���겻��
              nexthead->y=head->y;
              nexthead->next=head;
              q=head;
              if(nexthead->x==food->x && nexthead->y==food->y){//��ʳ��
                     while(q!NULL)
                     {
                            gotoxy(q->x,q->y);
                            color(14);
                            printf("��");
                            q=q->next;
                     }
                     score=score+add;
                     speedup();
                     creatfood();
              }else{//û��ʳ��
                     while(q->next->next!=NULL)
                     {
                            gotoxy(q->x,q->y);
                            color(14);
                            printf("��");
                            q=q->next;
                     }
              gotoxy(q->next->x,q->next->y);
              color(3);
              printf("��");
              free(q->next);
              q->next=NULL;
              }
       }
       if(status==R)
       {
              nexthead->x=head->x-2;//����ǰ��ʱ��x���������ƶ�+2��y���겻��
              nexthead->y=head->y;
              nexthead->next=head;
              q=head;
              if(nexthead->x==food->x && nexthead->y==food->y){//��ʳ��
                     while(q!NULL)
                     {
                            gotoxy(q->x,q->y);
                            color(14);
                            printf("��");
                            q=q->next;
                     }
                     score=score+add;
                     speedup();
                     creatfood();
              }else{//û��ʳ��
                     while(q->next->next!=NULL)
                     {
                            gotoxy(q->x,q->y);
                            color(14);
                            printf("��");
                            q=q->next;
                     }
              gotoxy(q->next->x,q->next->y);
              color(3);
              printf("��");
              free(q->next);
              q->next=NULL;
              }
       }
		if(biteself()==1)//�ж��Ƿ�ҧ���Լ�
		{
			endgamestatus=2;
		}
}
/**
*���Ƽ��̰���
*/
void keyboardControl()
{
	status=R;//��ʼ�������ƶ�
	while(1)
	{
		scoreandtips();//��Ϸ�����Ҳ�ĵ÷ֺ�С��ʾ
		//GetAsyncKeyState���������жϺ�������ʱָ���������״̬
		if(GetAsyncKeyState(VK_UP) && status!=D)
		{
			status=U;//����߲�������ǰ��ʱ�������ϼ�����ִ������ǰ������
		}else if(GetAsyncKeyState(VK_DOWN) && status!=U)
		{
			status=D;//����߲�������ǰ��ʱ�������¼�����ִ������ǰ������
		}else if(GetAsyncKeyState(VK_LEFT) && status!=R)
		{
			status=L;//����߲�������ǰ��ʱ�������������ִ������ǰ������
		}else if(GetAsyncKeyState(VK_RIGHT) && status!=L)
		{
			status=R;//����߲�������ǰ��ʱ�������Ҽ�����ִ������ǰ������
		}
		if(GetAsyncKeyState(VK_SPACE))//����ͣ����ִ��Sleep()������ͣ����
		{
			while(1)
			{
		//Sleep()������ͷ�ļ�#include<unistd.h>���������ͣ��ֱ���ﵽ�����趨�Ĳ�����ʱ��
				Sleep(300);
				if(GetAsyncKeyState(VK_SPACE))//���ո����ͣ
				{
					break;
				}

			}
		}else if(GetAsyncKeyState(VK_ESCAPE))
		{
			endgamestatus=3;//��<ESC>����ֱ����ת����������
			break;
		}else if(GetAsyncKeyState(VK_f1))//��F1��������
		{
			speedup();
		}else if(GetAsyncKeyState(VK_F2))//��f2��������
		{
			speeddown();//���ü��ٺ���
		}
		Sleep(sleeptime);
		snakemove();//������ʱ���߱���ǰ��
	}
}





























 


