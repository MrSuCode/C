#include<time.h>
#include<stdio.h>
#include <stdlib.h>

struct Fruit//�����ʾ���ӵĽṹ��
{
	int sort;//0��ʾ���̣�1��ʾƻ����2��ʾ����
	struct Fruit *next;
};
int block[3];//ȫ�ֱ���ֵĬ��Ϊ0��1��ʾ������0��ʾ����
//block[0], block[1], block[2]�ֱ��ʾ���ף����ӣ�Ů����״̬

struct Fruit *initFruit(int num)//����һ��ѭ��������ģ��ˮ�����ϵ�ˮ�����У�numΪ���ɷ�ˮ����
{
	int i;
	if (num == 0) return 0;
	struct Fruit *head = (struct Fruit*)malloc(sizeof(struct Fruit));//����ͷ���
	struct Fruit *pnew, *ptail = head;//����������������½ڵ�
	for(i = 0; i < num; i++)
	{
		pnew = (struct Fruit*)malloc(sizeof(struct Fruit));
		pnew -> sort = 0;//��ʼ���ǿ���
		ptail -> next = pnew;
		ptail = pnew;
	}
	ptail -> next = head;//����ѭ���б�
	return head;//����ͷָ��
}

void Plate(struct Fruit *head)//������ӡ�������ڵ�״̬
{
	if(!head) return;//ûͷָ�����˳�
	struct Fruit *p = head -> next;//����һ��ָ��ָ�����ӵĵ�һ��λ��
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
	struct Fruit *head = initFruit(5);//������ˮ��
	struct Fruit *get = head;//ָ��ȡˮ��λ��
	struct Fruit *put = head;//ָ����ˮ��λ��
	int random1;//������Ų������������0ѡ���ף�1ѡ����ӣ�2ѡ��Ů��
	int random2;//������Ų������������0��ƻ����1������
	srand((unsigned)time(NULL));//���������
	int count, i;

	printf("Please input scheduling count:\n");
	scanf("%d", &count);
	for(i = 0; i < count; i++)
    {
		do{//ѡ��δ�����Ľ���
		    random1 = rand() % 3;
		}while(block[random1]);

		if(random1 == 0)//���׽��̻�����Ӳ���Ȩ
        {
			printf("sched: father\n");
			if(put -> next == head) put = put -> next;//Ϊͷָ����������һ���ڵ�
			if(put -> next -> sort != 0)//˵��������ˮ��������ˮ����������
            {
				printf("father: the plate is full, blocked me\n\n");
				block[0] = 1;
			}
            else
            {
				random2 = rand() % 2;
				if (random2 == 0)//ѡ���ƻ��
				{
					put -> next -> sort = 1;
					printf("father: put an 'A'pple\n");
					put = put -> next;
					if(block[2] == 1)//��Ů����������̬������
					{
						block[2] = 0;
						printf("daughter wakeup\n");
					}
					Plate(head);//��ӡ����״̬
				}
				else//ѡ�������
                {
					put -> next -> sort = 2;
					printf("father: put an 'O'range\n");
					put = put -> next;
					if(block[1] == 1)//�����Ӵ�������̬������
					{
						block[1] = 0;
						printf("son wakeup\n");
					}
					Plate(head);//��ӡ����״̬
				}
			}
		}
		else
        {
			if(random1 == 1)//���ӽ��̻�����Ӳ���Ȩ
			{
				printf("sched: son\n");
				if(get -> next == head) get = get -> next;//Ϊͷָ����������һ���ڵ�
				if(get -> next -> sort == 0)//��ˮ��
				{
					printf("son: no orange, blocked me\n\n");//���ӽ�������
					block[1] = 1;
				}
                else
                {
					if(get -> next -> sort == 1) printf("son: not orange\n\n");//��ƻ��
                    else//������
                    {
						printf("son: eat an orange\n");
						get -> next -> sort = 0;
						get = get -> next;
						if(block[0])
						{
							block[0] = 0;//���Ѹ��׽���
							printf("father wake up\n");
						}
						Plate(head);//��ӡ����״̬
					}
				}
			}
			else//Ů�����̻�����Ӳ���Ȩ
            {
				printf("sched: daughter\n");
				if(get -> next == head) get = get -> next;//Ϊͷָ����������һ���ڵ�
				if(get -> next -> sort == 0)//��ˮ��
                {
					printf("daughter: no apple, blocked me\n\n");
					block[2] = 1;
				}
				else
                {
					if(get -> next -> sort == 2) printf("daughter: not Apple\n\n");//������
					else//��ƻ��
					{
						printf("daughter: eat an Apple\n");
						get -> next -> sort = 0;
						get = get -> next;
						if(block[0])
						{
							block[0] = 0;
							printf("father wake up\n");//���Ѹ��׽���
						}
						Plate(head);//��ӡ����״̬
					}
				}
			}
		}
	}
	system("pause");
}
