#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
	int input[20];//存储入栈顺序
	int output[20];//记录保存
	int * * stack;//出栈记录（留着去重）
	int flag[20];//标记是否出栈
	int num;//记录个数
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
	int catalan[20] = { 0 };//第20个超出int范围，就不用long long了，反正很快又会超范围的O(∩_∩)O！
	Catalan(catalan);
	SeqStack * S;
	S = (SeqStack *)malloc(sizeof(SeqStack));
	printf("请输入堆栈个数(0结束）");
	while (scanf("%d", &n) && n > 0)
	{
		memset(S->flag, 0, sizeof(S->flag));
		S->num = n;
		S->stack = (int **)calloc(catalan[n], sizeof(int *));//分配二维数组
		for (i = 0; i < catalan[n]; i++)
		{
			S->stack[i] = (int *)calloc(n, sizeof(int));
		}
		memset(S->flag, 0, sizeof(S->flag));
		//S->top = 0;//初始化(默认第一个入栈)
		for (i = 0; i < n; i++)
		{
			scanf("%d", &S->input[i]);
		}
		a = Print(S, n - 1, 0, 0);//默认进第一个，则少一个入栈数。
		Delete(S, catalan);
		printf("请输入堆栈个数(0结束）");
		*a = -1;//静态变量a归初始化，重复使用^_^
	}
	return 0;
}
int * Print(SeqStack * S, int n, int top1, int top2)//打印int类型,n为多少未进站,top1为入栈的指针，top2为记录的指针。返回静态变量a的地址，用于归0.
{
	int i,j=0,temp = 0;
	static int a = -1;
	if (n == 0)
	{
		a++;
		for (i = 0; i < top2; i++)//将结果保存到stack数组，用于去重
		{
			S->stack[a][i] = S->output[i];
		}
		for (i = 0; i < S->num; i++)//全部进栈后，有未出栈的一次性出栈(从后往前保存)
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
		Print(S, n - 1, Push(S, top1), top2);//数目-1，记录顶部不变
		temp = Pop(S, top1, top2);
		if (temp != -1)//如果无元素在栈中则不执行递归
		{
			Print(S, n, temp, top2 + 1);//出栈不改变未进栈数目,记录顶部+1
			S->flag[top1] = 0;//回溯
		}
	}
	return &a;
}
int Push(SeqStack * S, int top) //入栈，返回顶部
{
	do//移动至未入栈的元素
	{
		top++;
	} while (S->flag[top] == 1);
	return top;
}
int Pop(SeqStack * S, int top1, int top2)
{
	int flag = 0, temp = top1;
	if (S->flag[top1] == 1)//栈内无元素，返回0不执行递归。
		return -1;
	S->output[top2] = S->input[top1];//将出栈元素保存
	S->flag[top1] = 1;
	while (S->flag[top1] == 1)//移动至未出栈的元素
	{
		top1--;
		if (top1 < 0)//全部出栈
		{
			top1 = temp;//恢复top位置
			return temp;
		}
	}
	return top1;
}
void Catalan(int a[])//计算卡特兰数（没事非要去重（抠鼻），我还得用数组记录比较一下！）
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
void Delete(SeqStack * S, int catalan[])//无辜的去重复函数，时间空间复杂度增加的有点多····(自带输出功能)
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
				if (S->stack[i][m] == S->stack[j][m])//一样标记+1
					temp++;
			}
			if (temp == S->num)
				flag[j] = 1;//重复标记为1
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
