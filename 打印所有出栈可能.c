#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
	int input[20];//�洢��ջ˳��
	int output[20];//��¼����
	int * * stack;//��ջ��¼������ȥ�أ�
	int flag[20];//����Ƿ��ջ
	int num;//��¼����
}SeqStack;


void Catalan(int a[]);
int * Print(SeqStack * S, int n, int top1, int top2);
int Pop(SeqStack * S, int top1, int top2);
void Catalan(int a[]);
int Push(SeqStack * S, int top);
void Delete(SeqStack * S, int catalan[]);


int main(void)
{
	int n, i;
	int * a;
	int catalan[20] = { 0 };//��20������int��Χ���Ͳ���long long�ˣ������ܿ��ֻᳬ��Χ��O(��_��)O��
	Catalan(catalan);
	SeqStack * S;
	S = (SeqStack *)malloc(sizeof(SeqStack));
	printf("�������ջ����(0������");
	while (scanf("%d", &n) && n > 0)
	{
		memset(S->flag, 0, sizeof(S->flag));
		S->num = n;
		S->stack = (int **)calloc(catalan[n], sizeof(int *));//�����ά����
		for (i = 0; i < catalan[n]; i++)
		{
			S->stack[i] = (int *)calloc(n, sizeof(int));
		}
		memset(S->flag, 0, sizeof(S->flag));
		//S->top = 0;//��ʼ��(Ĭ�ϵ�һ����ջ)
		for (i = 0; i < n; i++)
		{
			scanf("%d", &S->input[i]);
		}
		a = Print(S, n - 1, 0, 0);//Ĭ�Ͻ���һ��������һ����ջ����
		Delete(S, catalan);
		printf("�������ջ����(0������");
		*a = -1;//��̬����a���ʼ�����ظ�ʹ��^_^
	}
	return 0;
}
int * Print(SeqStack * S, int n, int top1, int top2)//��ӡint����,nΪ����δ��վ,top1Ϊ��ջ��ָ�룬top2Ϊ��¼��ָ�롣���ؾ�̬����a�ĵ�ַ�����ڹ�0.
{
	int i,j=0,temp = 0;
	static int a = -1;
	if (n == 0)
	{
		a++;
		for (i = 0; i < top2; i++)//��������浽stack���飬����ȥ��
		{
			S->stack[a][i] = S->output[i];
		}
		for (i = 0; i < S->num; i++)//ȫ����ջ����δ��ջ��һ���Գ�ջ(�Ӻ���ǰ����)
		{
			if (S->flag[i] == 0)
			{
				S->stack[a][S->num - j - 1] = S->input[i];
				j++;
			}
		}
	}
	else
	{
		Print(S, n - 1, Push(S, top1), top2);//��Ŀ-1����¼��������
		temp = Pop(S, top1, top2);
		if (temp != -1)//�����Ԫ����ջ����ִ�еݹ�
		{
			Print(S, n, temp, top2 + 1);//��ջ���ı�δ��ջ��Ŀ,��¼����+1
			S->flag[top1] = 0;//����
		}
	}
	return &a;
}
int Push(SeqStack * S, int top) //��ջ�����ض���
{
	do//�ƶ���δ��ջ��Ԫ��
	{
		top++;
	} while (S->flag[top] == 1);
	return top;
}
int Pop(SeqStack * S, int top1, int top2)
{
	int flag = 0, temp = top1;
	if (S->flag[top1] == 1)//ջ����Ԫ�أ�����0��ִ�еݹ顣
		return -1;
	S->output[top2] = S->input[top1];//����ջԪ�ر���
	S->flag[top1] = 1;
	while (S->flag[top1] == 1)//�ƶ���δ��ջ��Ԫ��
	{
		top1--;
		if (top1 < 0)//ȫ����ջ
		{
			top1 = temp;//�ָ�topλ��
			return temp;
		}
	}
	return top1;
}
void Catalan(int a[])//���㿨��������û�·�Ҫȥ�أ��ٱǣ����һ����������¼�Ƚ�һ�£���
{
	int i, j;
	a[0] = 1;
	a[1] = 1;
	for (i = 2; i < 20; i++)
	{
		for (j = 0; j < i; j++)
		{
			a[i] += a[j] * a[i - j - 1];
		}
	}
}
void Delete(SeqStack * S, int catalan[])//�޹���ȥ�ظ�������ʱ��ռ临�Ӷ����ӵ��е�ࡤ������(�Դ��������)
{
	int i, j, m, temp;
	int * flag;
	flag = (int *)calloc(catalan[S->num], sizeof(int));
	for (i = 0; i < catalan[S->num]; i++)
		for (j = i + 1; j < catalan[S->num]; j++)
		{
			temp = 0;
			for (m = 0; m < S->num; m++)
			{
				if (S->stack[i][m] == S->stack[j][m])//һ�����+1
					temp++;
			}
			if (temp == S->num)
				flag[j] = 1;//�ظ����Ϊ1
		}
	for (i = 0; i < catalan[S->num]; i++)
	{
		if (flag[i] == 1)
			continue;
		for (m = 0; m < S->num; m++)
		{
			printf("%d ", S->stack[i][m]);
		}
		printf("\n");
	}
}
