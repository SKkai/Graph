#ifndef _H_Graph_
#define _H_Graph_
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//���������б�
typedef int status;
typedef int ElemType;
#define TRUE 1
#define ERROR 0
#define FALSE 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20

typedef struct ArcNode { //�������Ͷ���
    int adjvex;                          //����λ�ñ��
    struct ArcNode *next;    //��һ������ָ��
    int *info;
} ArcNode;

typedef struct VNode{//ͷ��㼰���������Ͷ���
    char index[20];
    int key;         //������Ϣ
    ArcNode *firstarc;      //ָ���һ����
    }VNode,AdjList[MAX_VERTEX_NUM],**defination;

typedef  struct {  //�ڽӱ�����Ͷ���
        AdjList vertices;                //ͷ�������
        int vexnum,arcnum;         //������������
       } ALGraph, *Graph;

typedef struct defination{
    defination df;
    int n;
}Defination;

typedef struct Queue
{
    int data;
    struct Queue *next,*front,*rear;
}Queue,LinkQueue,*QueuePtr;

void input(int *op)
{
    char ch;
     while(!scanf("%d", op))
        {
            printf("�������ݲ��Ϸ�!\n");
            while ((ch = getchar()) != EOF && ch != '\n');
        }
        while ((ch = getchar()) != EOF && ch != '\n');
}

#endif
