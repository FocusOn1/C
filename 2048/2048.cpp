#include <stdio.h>	//��׼������������⣨printf��scanf��
#include <conio.h>  //Ϊ�˶�ȡ�����
#include <windows.h>//����dos���棨��ȡ����̨������λ�á�����������ɫ��
#include <math.h>   //pow����

/*******��  ��  ��  ��*******/
void gotoxy(int x, int y); 		//��ȡ��Ļ���λ��
int color(int c);               //����������ɫ
int	TextColors(int i);			//���������޸���ɫ
void drawTheGameBox(); 			//������Ϸ����
int *add(int item[]);   		//�ϲ�����
int ifMove(int item[]); 		//�ж��Ƿ��ܹ��ƶ�����,����1�ܶ���0���ܶ�
void Gameplay();    			//��ʼ��Ϸ
void Replay();			       	//������Ϸ
int if2n(int x);         		//�ж�x�Ƿ���2��n�η�
int ifup();						//�ж��Ƿ��ܹ�����    �������ƣ������е������������2��n�η������򷵻�1    �����ƶ����򷵻�0
int ifdown();					//�ж��Ƿ��ܹ�����    �������ƣ������е������������2��n�η������򷵻�1    �����ƶ����򷵻�0
int ifleft();					//�ж��Ƿ��ܹ�����    �������ƣ������е������������2��n�η������򷵻�1    �����ƶ����򷵻�0
int ifright();					//�ж��Ƿ��ܹ�����   �������ƣ������е������������2��n�η������򷵻�1    �����ƶ����򷵻�0
int BOXmax();					//�������������
int Gamefaile();				//�ж��Ƿ�ʧ��
int Gamewin();					//�ж��Ƿ�ʤ��
int keyboardControl(int key);   //���̿����ƶ�
void close();                   //�ر���Ϸ
void title();                   //���Ʊ��⣨2048�ַ�����
void choice();                  //ѡ���
void Rabbit();					//�����ַ���
void regulation();              //��Ϸ�������
void explation();               //����˵��


/*******��  ��  ȫ  ��  ��  ��*******/
int step=0;				//��ִ�в���
int score=0;			//�洢��Ϸ����
long int Time;			//��Ϸ����ʱ��
int BOX[4][4]={0,0,0,0, //��Ϸ�е�16������
               0,0,0,0,
               0,0,0,0,
               0,0,0,0};
HANDLE hOut;			//����̨���

/**
 * ��ȡ��Ļ���λ��
 */
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
/**
 * ������ɫ����      �˺����ľ����ԣ�1��ֻ��Windowsϵͳ��ʹ��   2�����ܸı䱳����ɫ
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        
	return 0;
}


/**
 * ���������޸���ɫ
 */
int TextColors(int number)
{
	switch (number)         //�����г��ֵ�2��2�Ĵη���ʾΪ��ͬ��ɫ
	{      //����1~15����ͬ��������ɫ������15��ʾ���ֱ���ɫ
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
 * ������Ϸ����  4*4������
 */
void drawTheGameBox()
{
	Rabbit();
	int i,j,k;
	gotoxy(66,3);   			//��Ļ����λ��
	color(1);      			
	printf("�[��֔�:");
	gotoxy(76,3);
	color(4);
	printf("%d",score);
	color(4);      			
	gotoxy(66,5);   			//��Ļ����λ��
	printf("���в���:");
	gotoxy(76,5);
	color(1);
	printf("%d\n",step);
	color(14);       			
	for(j = 2;j <= 22;j += 5)   //��ӡ���̱߿�
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
	printf("���Õr��");  
	gotoxy(76,23);
	color(1);
	printf("%ds",time(NULL) - Time); //�����Ϸ����ʱ��
}

 /**
 * �ϲ�����
 */
int* add(int item[])
{
    int i = 0, j = 0;
    int tep[4] = {0, 0, 0, 0}, tmp[4] = {0, 0, 0, 0};
    for(i = 0; i < 4; i ++)
	{
        if(item[i] != 0)			//������������������
		{              
            tep[j ++] = item[i];
        }
    }
	//���������ڵ���ͬ����������
    for(i = 0; i < 4; i ++)
	{
//        if(tep[0] == 0) break;      //���������û�����֣�����
        if(tep[i] == tep[i + 1])	//�������������ͬ����ϲ�
		{
            tep[i] *= 2;        	//һ�������е����ַ�������һ��Ϊ��
            tep[i + 1] = 0;
            score=score+tep[i];		//�ӷ֣��ӵķ���Ϊ����������*2
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
    return (int *)(&tmp);   //tmpΪָ������ã�*&ָ�뱾��ɱ�
}


 /**
 * �ж��ܷ��ƶ�����,����1�ܶ���0���ܶ�
 */
int ifMove(int item[])
{
    int i = 0;
    for(i = 0; i < 3; i ++)
	{
        if(item[i] != 0 && item[i] == item[i + 1])      //�������������λ��������ͬ�����ƶ�������1
        {
        	return 1;
		}
        if(item[i] == 0 && item[i + 1] != 0)            //�������������λ�ϣ�һ���ǿո��ӣ�һ���������֣�Ҳ���ƶ�������1
        {
        	return 1;
		}
    }
    return 0;       //���ܺϲ�������0
}


 /**
 * �ж�x�Ƿ���2��n�η�,��2��n�η�������1�����򷵻�0
 */
int if2n(int x)       
{
	int flag = 0;
	int n;
	int N = 1;   
	for(n = 1;n <= 11;n++)		//2��11�η���2048����ϷĿ���Ǵﵽ2048
	{
		if(x == pow(2,n))       //����2��n�η�
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
 * �ж��Ƿ��ܹ�����    �������ƣ��򷵻�1    �����ƶ����򷵻�0
 */
int ifup()
{
	int i,j;
	int flag = 0;           //�����־������ֻ��0��1
	for(j = 0;j < 4;j ++)
		for(i = 0;i < 3;i ++)
		{
			if((if2n(BOX[i][j] + BOX[i+1][j]) == 1) && BOX[i+1][j])     //��������������������2��n�η�����������ĸ���������
			{
				flag = 1;                                               //��������
			}
		}
		return flag;                                                    //����1��ʾ�������ƣ�����0��ʾ��������
}

 /**
 * �ж��Ƿ��ܹ�����    �������ƣ��򷵻�1    �����ƶ����򷵻�0
 */
int ifdown()
{
	int i,j;
	int flag = 0;
	for(j = 0;j < 4;j ++)
		for(i = 3;i > 0;i --)
		{
			if((if2n(BOX[i][j] + BOX[i-1][j]) == 1) && BOX[i-1][j])     //��������������������2��n�η�����������ĸ���������
			{
				flag = 1;                                               //��������
			}
		}
		return flag;                                                    //����1��ʾ�������ƣ�����0��ʾ��������
}

 /**
 * �ж��Ƿ��ܹ�����    �������ƣ��򷵻�1    �����ƶ����򷵻�0
 */
int ifleft()
{
	int i,j;
	int flag = 0;
	for(i = 0;i < 4;i ++)
		for(j = 0;j < 3;j ++)
		{
			if((if2n(BOX[i][j] + BOX[i][j+1]) == 1) && BOX[i][j+1])     //��������������������2��n�η�����������ĸ���������
			{
				flag = 1;                                               //��������
			}
		}
		return flag;                                                    //����1��ʾ�������ƣ�����0��ʾ��������
}

 /**
 * �ж��Ƿ��ܹ�����   �������ƣ��򷵻�1    �����ƶ����򷵻�0
 */
int ifright()
{
	int i,j;
	int flag = 0;
	for(i = 0;i < 4;i ++)
		for(j = 3;j > 0;j --)
		{
			if((if2n(BOX[i][j] + BOX[i][j-1]) == 1) && BOX[i][j-1])     //��������������������2��n�η�����������ĸ���������
			{
				flag = 1;                                               //����������
			}
		}
		return flag;                                                    //����1��ʾ�������ƣ�����0��ʾ��������
}

 /**
 * �������������
 */
int BOXmax()
{
	int max = BOX[0][0];       	 	//��ʼ��BOX����
	int i,j;
	for(i = 0;i < 4;i ++)      	//������������
	{
		for(j = 0;j < 4;j ++)
		{
			if(BOX[i][j] > max) 	//�������������ֵ����max��ֵ
			{
				max = BOX[i][j];    //�������е�ֵ��ֵ��max�������ҳ������е������
			}
		}
}
	return max;                     //����max��ֵ��Ҳ���ǵ�ǰ�����е����ֵ
}

 /**
 * �ж��Ƿ�ʧ��   ��һ��������������
 */
int Gamefaile()
{
	int flag = 0;
	int max;
	if(ifup() + ifdown() + ifleft() + ifright() == 0)				//���������Ҷ������ƶ���ʱ����Ϸʧ��
//	if(ifMove(BOX))
	{
		system("cls");
		gotoxy(34,3);
		color(14);
		printf("�ϲ�����������ǣ�");
		gotoxy(52,3);
		color(11);
		max = BOXmax();
		printf("%d",max);
		gotoxy(19,6);
		color(4);   //����ɫ
    	printf("     ����������    ��         ��    ����     \n");  //���end�ַ���
    	gotoxy(19,7);
    	printf("     ��            ����       ��    ��  ��   \n");
    	gotoxy(19,8);
        printf("     ��            �� ��      ��    ��    ��   \n");
        gotoxy(19,9);
		printf("     ��            ��  ��     ��    ��     ��  \n");
		gotoxy(19,10);
        printf("     ��������      ��   ��    ��    ��      ��  \n");
        gotoxy(19,11);
        printf("     ��            ��    ��   ��    ��     ��  \n");
        gotoxy(19,12);
		printf("     ��            ��     ��  ��    ��    ��   \n");
		gotoxy(19,13);
		printf("     ��            ��      �� ��    ��  ��  \n");
		gotoxy(19,14);
		printf("     ����������    ��       ����    ����     \n");
		gotoxy(34,17);
		color(13);
		printf("�޷��ƶ�����Ϸʧ�ܣ�");                             //��ʾ����
		flag = 1;
	}
   	return flag;                //flag��ֵ������0������1���ʾ��Ϸʧ��
}

 /**
 * �ж��Ƿ�ʤ��
 */
int Gamewin()
{
	int flag = 0;
	if(BOXmax() == 2048)            //��������е����ֵΪ2048���ﵽĿ�꣬����Ϸʤ��
	{
		system("cls");
		gotoxy(1,6);
		color(2);   //����ɫ
    	printf("     ��             ��             ��       ����������       ��          ��  \n");  //���ʤ��win���ַ���
    	gotoxy(1,7);
    	printf("      ��           ����           ��            ��           �� ��       ��  \n");
    	gotoxy(1,8);
        printf("       ��         ��  ��         ��             ��           ��  ��      ��  \n");
        gotoxy(1,9);
		printf("        ��       ��    ��       ��              ��           ��   ��     ��   \n");
		gotoxy(1,10);
        printf("         ��     ��      ��     ��               ��           ��    ��    ��  \n");
        gotoxy(1,11);
        printf("          ��   ��        ��   ��                ��           ��     ��   �� \n");
        gotoxy(1,12);
		printf("           �� ��          �� ��                 ��           ��      ��  ��    \n");
		gotoxy(1,13);
		printf("            ����          ����                  ��           ��       �� ��  \n");
		gotoxy(1,14);
		printf("             ��            ��               ����������       ��          ��   \n");
		gotoxy(35,17);
		color(13);
		printf("ʤ�����������������");
		flag = 1;
	}
	 return flag;                //flag��ֵ������0������1���ʾ��Ϸʤ��
}

 /**
 * ���̿����ƶ�
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
            	tp[0] = BOX[0][i];      //��һ�����Ƶ��м����
            	tp[1] = BOX[1][i];
            	tp[2] = BOX[2][i];
            	tp[3] = BOX[3][i];
            	p = add(tp);            //��úϲ�֮�����ֵ
           	 	if(!ifMove(tp))			//�ж��Ƿ�����ƶ��������ƶ������³���һ�����֣������ƶ��������ˣ�Ҳ�������������
//if(ifup())
				{
					j++;        		//�����ƶ�
				}
           	 	BOX[0][i] = p[0];       //�Ѵ���õ��м�����ƻ���
            	BOX[1][i] = p[1];
            	BOX[2][i] = p[2];
            	BOX[3][i] = p[3];
        	}
        	return j != 4;              //��j������4��ʱ�򣬿���ִ��up����
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
		case 27:	//��ESC
			gotoxy(20,23);
			color(12);
			printf("ȷ���˳���Ϸô? (y/n)");
			char c = getch();           //��ü�������
			if(c == 'y' ||c == 'Y')     //���������Ǵ�д����Сд��y
			{
				exit(0);                //�˳���Ϸ
			}
			if(c == 'n'||c == 'N')      //���������Ǵ�д����Сд��n
			{
				gotoxy(20,23);
				printf("                        ");   //������Ϸ
			}
			break;
    	default: return 0;
    }
}

 /**
 * ��ʼ��Ϸ
 */
void Gameplay()
{
	system("cls");      			//����
	int i = 0, j = 0;
	Time = time(NULL);				//ȡ��ǰʱ��Ϊ��ʼʱ��
    drawTheGameBox();               //������Ϸ����
    int a,b;                        //BOX[][]����ĺ�������
    srand(time(NULL)); 				//������������ӣ���ʼ�������
	do
	{
    	a = rand()%4;               //���4*4�����е����λ��
    	b = rand()%4;
	}while(BOX[a][b]!=0);           //һֱ��������û�пո�
	if(rand() % 4 == 0)      		//2��4��������ڿո�(�ʼ�����������ϵ�2��4)
	{
		BOX[a][b] = 4;
    }
	else
	{
		BOX[a][b] = 2;
    }

    for(i = 0; i < 4; i ++)         //������������
	{
        for(j = 0; j < 4; j ++)
		{
            if(BOX[i][j] == 0)      //����������п�λ���ͼ�����ȥ
            {
            	continue;
			}
//            gotoxy(17 + j * 8 + 3 + (j * 2), i * 4 + (i + 5));  //����������ʾλ��
			gotoxy(15 + j * 10 +8, 2 + i * 5 + 3);  //����������ʾλ��
            int c = BOX[i][j];  //���������BOX[i][j]�ϵ�����
            TextColors(c);  //�������ӵ���ɫ����ͬ������ʾ��ͬ��ɫ
            printf("%d", c);    //��ӡ����
        }
    }

    while(1) {
        while (kbhit())            			//kbhit()��鵱ǰ�Ƿ��м������룬�з���1�����򷵻�0
        {
            if(!keyboardControl(getch()))  //������µİ���������keyboardControl()�����ж���ģ���û�з�Ӧ��һֱ�����¶���İ���Ϊֹ
            {
				continue;
			}
            drawTheGameBox();       		//��������
            for(i = 0; i < 4; i ++)         //ѭ������4*4������
			{
                for(j = 0; j < 4; j ++)
				{
                    if(BOX[i][j] == 0)      //����������п�λ�����һֱ���а���
                    {
						continue;
					}
					gotoxy(15 + j * 10 +8, 2 + i * 5 + 3);//�ϲ���������ֵ�λ��
                    int c = BOX[i][j];
            		TextColors(c);
            		printf("%d", c);
                }
            }
			do{
    			a = rand()%4;
    			b = rand()%4;           //������λ��
			}while(BOX[a][b]!=0);
    		if(rand() % 4 == 0)       //2��4��������ڿո�(���з�������ϲ�֮���ڿհ״�����)
			{
				BOX[a][b] = 4;          //���λ��������Ϊ4
    		} else {
				BOX[a][b] = 2;          //���λ��������Ϊ2
    		}
    		step++;                 //���мƲ�
//            gotoxy(17 + b * 8 + 3 + (b * 2), a * 4 + (a + 5));//�ϲ���������ֵ�λ��
			gotoxy(15 +  b * 10 + 8, 2 + a * 5 + 3);     //������ֵ�2��4
			int c = BOX[a][b];
		    TextColors(c);
            printf("%d", c);   
	    }
	 	if(Gamefaile()+Gamewin() != 0)  //ֻҪGamefaile()����Gamewin()����һ����������1��Ҳ���ǳɹ�����ʧ�ܶ���������������
	    {
	    	int n;
	    	gotoxy(20,20);
			color(12);
			printf("��Ҫ������һ��-------1");
			gotoxy(45,20);
			printf("�����ˣ��˳���-------2\n");
			gotoxy(43,21);
			color(11);
			scanf("%d", &n);
    		switch (n)
    		{
    			case 1:
        			Replay();         //������Ϸ����
        			break;
    			case 2:
        			close();    		//�ر���Ϸ����
        			break;
    		}
		}
	}
}

 /**
 * ������Ϸ
 */

void Replay()
{
	system("cls");                  	//����
	score = 0,step = 0;                 //��������������
	memset(BOX,0,16*sizeof(int));       //��ʼ��BOX����
	Gameplay();                         //��ʼ��Ϸ
}
void title()
{
	color(1);         
    gotoxy(19,2);
    printf("������"); 
    gotoxy(19,3);
    printf("    ��");
    gotoxy(19,4);
    printf("������");
    gotoxy(19,5);
    printf("��   ");
    gotoxy(19,6);
    printf("������");
    
    color(1);
    gotoxy(27,2);
    printf("�������� "); 
    gotoxy(27,3);
    printf("��    �� ");
    gotoxy(27,4);
    printf("��    �� ");
    gotoxy(27,5);
    printf("��    �� ");
    gotoxy(27,6);
    printf("�������� ");
    
    color(4);
    gotoxy(37,2);
    printf("��  ��"); 
    gotoxy(37,3);
    printf("��  ��");
    gotoxy(37,4);
    printf("��  ��");
    gotoxy(37,5);
    printf("��������");
    gotoxy(37,6);
    printf("    ��");
    
    color(4);
    gotoxy(47,2);
    printf("��������");
    gotoxy(47,3);
    printf("��    ��");
    gotoxy(47,4);
    printf("��������");
    gotoxy(47,5);
    printf("��    ��");
    gotoxy(47,6);
    printf("��������");
}

void Rabbit()
{
    color(1);
	gotoxy(66,10);
	printf("��--��  ��--��");
	gotoxy(66,11);
	printf("��  ��  ��  ��");
	gotoxy(66,12);
	printf("��  ��  ��  ��");
	gotoxy(65,13);
	printf("_��"); 
	gotoxy(71,13);
	color(4);
	printf("��");
	color(1);
	gotoxy(75,13); 
	printf("��_"); 
	gotoxy(64,14);
	printf("��");
	gotoxy(77,14); 
	printf("��");
	gotoxy(64,15);
	printf("��");
	gotoxy(64,16);
	printf("��");
	gotoxy(77,15);
	printf("��");
	gotoxy(77,16);	
	printf("��");
	gotoxy(64,17);
	printf("��");
	gotoxy(77,17);
	printf("��"); 
	gotoxy(64,18);
	printf("�����������ש����ש���������"); 
	gotoxy(68,19);
	printf("����  �ǩ�");
	gotoxy(66,20);
	printf("���ީߩ��ߩߩݡ�");
	color(14);
	gotoxy(68,15);
	printf("��   ��");
	color(13);
	gotoxy(67,17);
	printf("��");
	gotoxy(74,17);  
	printf("��");
	color(12);
	gotoxy(71,17);
	printf("��");
	
	color(4);
	gotoxy(2,10);
	printf("��--��  ��--��");
	gotoxy(2,11);
	printf("��  ��  ��  ��");
	gotoxy(2,12);
	printf("��  ��  ��  ��");
	color(14);
	gotoxy(7,13);
	printf("��");
	color(4);
	gotoxy(1,13);
	printf("_��");
	gotoxy(11,13);
	printf("�� _");
	gotoxy(0,14);
	printf("��");
	gotoxy(13,14);
	printf("��");
	gotoxy(0,15);
	printf("��");
	gotoxy(13,15);
	printf("��");
	gotoxy(0,16);
	printf("��");
	gotoxy(13,16);
	printf("��");
	gotoxy(0,17);
	printf("��");
	gotoxy(13,17);
	printf("��");
	gotoxy(0,18);
	printf("�����������ש����ש���������");	
	gotoxy(3,19);
	printf("����    �ǩ�");
	gotoxy(2,20);
	printf("���ީ��ߩ��ߩݡ�");
	color(1);
	gotoxy(5,15);
	printf("��   ��");
	color(13);
	gotoxy(3,17);
	printf("��");
	gotoxy(11,17);
	printf("��");
	color(14);
	gotoxy(7,17);
	printf("��");
}


 /**
 * ���������������
 */
int main() {
//	system("cls");      //����
    title();            //��ӡ����
    Rabbit();           //��ӡ�ַ���
    choice();           //�˵�ѡ��
    
}

 void choice()
{
	int n;
    int i,j = 1;
    gotoxy(27,8);
    color(1);
    printf("ِ ");
    gotoxy(31,8);
    color(4);
    printf(" ��");
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
				printf("��");
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
	printf("Ո�x��[1 2 3 4]:[ ]\b\b");
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
 * �˳�
 */
void close()
{
    exit(0);
}

 /**
 * ��Ϸ�������
 */
void regulation()
{
	int i,j = 1;
    system("cls");
    color(14);
    gotoxy(34,3);
    printf("�[��Ҏ�t");
    color(14);
    for (i = 6; i <= 20; i++)   //������±߿�===
	{
		for (j = 15; j <= 67; j++)  //������ұ߿�||
		{
			gotoxy(j, i);
			if (i == 6 || i == 20) printf("��");
			else if (j == 15 || j == 67) printf("$");
		}
	}
    color(14);
    gotoxy(18,8);
    printf("tip1: ����x��ķ�����,������ͬ�Ĕ��քt�ρK");
    color(11);
    gotoxy(18,11);
    printf("tip2: ÿ�Ƅ�һ������λ�S�C���Fһ��2��4");
    color(4);
    gotoxy(18,14);
    printf("tip3: ��P��������M���o���M����Ч�Ƅӣ��[��ʧ��");
    color(5);
    gotoxy(18,17);
    printf("tip4: ��P�ϳ��F2048���[�����");
    getch();                //�����������������
    system("cls");
    main();
}

 /**
 * ����˵��
 */
void explation()
{
	gotoxy(20,22);
	color(13);
	printf("�١������������������I�M���[�����!");
	gotoxy(20, 24);
	printf("��ESC�I�˳��[��");
//	color(8);
	getch();                //�����������������
	system("cls");
	main();
}

