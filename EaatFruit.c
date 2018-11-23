#include<time.h>
#include<stdio.h>
#include <stdlib.h>

struct Fruit//定义表示盘子的结构体
{
	int sort;//0表示空盘，1表示苹果，2表示橘子
	struct Fruit *next;
};
int block[3];//全局变量值默认为0，1表示阻塞，0表示就绪
//block[0], block[1], block[2]分别表示父亲，儿子，女儿的状态

struct Fruit *initFruit(int num)//构造一个循环链表来模拟水果盘上的水果队列，num为最多可放水果数
{
	int i;
	if (num == 0) return 0;
	struct Fruit *head = (struct Fruit*)malloc(sizeof(struct Fruit));//建立头结点
	struct Fruit *pnew, *ptail = head;//在现有链表中添加新节点
	for(i = 0; i < num; i++)
	{
		pnew = (struct Fruit*)malloc(sizeof(struct Fruit));
		pnew -> sort = 0;//开始都是空盘
		ptail -> next = pnew;
		ptail = pnew;
	}
	ptail -> next = head;//构建循环列表
	return head;//返回头指针
}

void Plate(struct Fruit *head)//用来打印盘子现在的状态
{
	if(!head) return;//没头指针则退出
	struct Fruit *p = head -> next;//定义一个指针指向盘子的第一个位置
	printf("Plate:");
	while (p != head)//
    {
		if(p -> sort == 0)
		{
			printf("( )");
			p = p -> next;
		}
        else if(p -> sort == 1)
        {
            printf("(A)");
            p = p -> next;
        }
        else
        {
            printf("(O)");
            p = p -> next;
        }
	}
	printf("\n\n");
}

int main()
{
	struct Fruit *head = initFruit(5);//最多五个水果
	struct Fruit *get = head;//指出取水果位置
	struct Fruit *put = head;//指出放水果位置
	int random1;//用来存放产生的随机数，0选择父亲，1选择儿子，2选择女儿
	int random2;//用来存放产生的随机数，0放苹果，1放橘子
	srand((unsigned)time(NULL));//产生随机数
	int count, i;

	printf("Please input scheduling count:\n");
	scanf("%d", &count);
	for(i = 0; i < count; i++)
    {
		do{//选择未阻塞的进程
		    random1 = rand() % 3;
		}while(block[random1]);

		if(random1 == 0)//父亲进程获得盘子操作权
        {
			printf("sched: father\n");
			if(put -> next == head) put = put -> next;//为头指针则移向下一个节点
			if(put -> next -> sort != 0)//说明盘子内水果满，放水果操作阻塞
            {
				printf("father: the plate is full, blocked me\n\n");
				block[0] = 1;
			}
            else
            {
				random2 = rand() % 2;
				if (random2 == 0)//选择放苹果
				{
					put -> next -> sort = 1;
					printf("father: put an 'A'pple\n");
					put = put -> next;
					if(block[2] == 1)//若女儿处于阻塞态，则唤醒
					{
						block[2] = 0;
						printf("daughter wakeup\n");
					}
					Plate(head);//打印盘子状态
				}
				else//选择放橘子
                {
					put -> next -> sort = 2;
					printf("father: put an 'O'range\n");
					put = put -> next;
					if(block[1] == 1)//若儿子处于阻塞态，则唤醒
					{
						block[1] = 0;
						printf("son wakeup\n");
					}
					Plate(head);//打印盘子状态
				}
			}
		}
		else
        {
			if(random1 == 1)//儿子进程获得盘子操作权
			{
				printf("sched: son\n");
				if(get -> next == head) get = get -> next;//为头指针则移向下一个节点
				if(get -> next -> sort == 0)//无水果
				{
					printf("son: no orange, blocked me\n\n");//儿子进程阻塞
					block[1] = 1;
				}
                else
                {
					if(get -> next -> sort == 1) printf("son: not orange\n\n");//是苹果
                    else//是橘子
                    {
						printf("son: eat an orange\n");
						get -> next -> sort = 0;
						get = get -> next;
						if(block[0])
						{
							block[0] = 0;//唤醒父亲进程
							printf("father wake up\n");
						}
						Plate(head);//打印盘子状态
					}
				}
			}
			else//女儿进程获得盘子操作权
            {
				printf("sched: daughter\n");
				if(get -> next == head) get = get -> next;//为头指针则移向下一个节点
				if(get -> next -> sort == 0)//无水果
                {
					printf("daughter: no apple, blocked me\n\n");
					block[2] = 1;
				}
				else
                {
					if(get -> next -> sort == 2) printf("daughter: not Apple\n\n");//是橘子
					else//是苹果
					{
						printf("daughter: eat an Apple\n");
						get -> next -> sort = 0;
						get = get -> next;
						if(block[0])
						{
							block[0] = 0;
							printf("father wake up\n");//唤醒父亲进程
						}
						Plate(head);//打印盘子状态
					}
				}
			}
		}
	}
	system("pause");
}
