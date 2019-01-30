#ifndef _H_Graph_
#define _H_Graph_
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//返回类型列表
typedef int status;
typedef int ElemType;
#define TRUE 1
#define ERROR 0
#define FALSE 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20

typedef struct ArcNode { //表结点类型定义
    int adjvex;                          //顶点位置编号
    struct ArcNode *next;    //下一个表结点指针
    int *info;
} ArcNode;

typedef struct VNode{//头结点及其数组类型定义
    char index[20];
    int key;         //顶点信息
    ArcNode *firstarc;      //指向第一条弧
    }VNode,AdjList[MAX_VERTEX_NUM],**defination;

typedef  struct {  //邻接表的类型定义
        AdjList vertices;                //头结点数组
        int vexnum,arcnum;         //顶点数、弧数
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
            printf("输入数据不合法!\n");
            while ((ch = getchar()) != EOF && ch != '\n');
        }
        while ((ch = getchar()) != EOF && ch != '\n');
}

#endif
