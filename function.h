#ifndef _H_FUNCTION_
#define _H_FUNCTION_
#include "Graph.h"

Defination CreatNode();
void  CreatVR(int i,int a[][2]);
status LocateVex(Graph G,int key);
void CreatGraph(Graph *G, defination df,int a[][2]);
status InitiaGraph(Graph G);
status DestroyGraph(Graph G);
status PutVex(Graph G, int key, char *value );
status FirstAdjvex(Graph G,int key);
status NextAdjvex(Graph G,int key1,int key2);
status InsertAdjvex(Graph G,VNode *p);
status DeleteVex(Graph G,int key);
status InsertArc(Graph G,int key1,int key2);
status DeleteArc(Graph G, int key1,int key2);
void DFSTraverse(Graph G,int visited[]);
void DFS(Graph G,int v,status (*visit)(Graph G,int i),int visited[]);
void BFSTraverse(Graph G,int visited[],status (*visit)(Graph G,int i));
status visit(Graph G,int i);
status InitQueue(LinkQueue *Q);
status EnQueue(LinkQueue *Q,int e);
status QueueEmpty(LinkQueue Q);
status DeQueue(LinkQueue *Q,int *e);
status Savegraph(ALGraph G,FILE *fp,char *filename);
status Loadgraph(ALGraph *G,FILE *fp,char *filename);


/*函数名：InitiaGraph
 *参数：图地址
 *返回值：int
 *功能：初始化图
 */
status InitiaGraph(Graph G)
{
    G=(Graph)malloc(sizeof(ALGraph));
    memset(G,0,sizeof( ALGraph));
    G->vexnum=0;
    G->arcnum=0;
    return OK;
}
/*
 *函数名：CreatNode
 *参数：图地址，定点数
 *返回值：Defination
 *功能：创建图的顶点集
 */
Defination CreatNode()
{

    Defination *DF = (Defination *)malloc(sizeof(Defination));
    defination df=NULL;
    //VNode *t;
    int key,n=0;
    printf("输入图的顶点集,用EOF结束输入\nkey:");
    while(scanf("%d",&key) != EOF)
    {
        n++;
        if(!(df = (defination)realloc(df, sizeof(VNode) * n)))
            perror("realloc");
        df[n-1] = (VNode *)malloc(sizeof(VNode));
        df[n-1]->key=key;
        printf("index:");
        fflush(stdout);
        scanf("%19s",&((df[n-1]->index)));
        df[n-1]->firstarc=NULL;
        printf("key:");
    }
    DF->df = df;
    DF->n = n;
    return *DF;
}

/*
 *函数名：CreatVR
 *参数：弧的条数，二维数组
 *返回值:void
 *功能：创建图的关系集
 */
void  CreatVR(int i,int a[][2])
{
    int j;
    printf("输入每条弧的起点key和终点key：");
    for(j=0;j<i;j++)
        scanf("%d %d",&a[j][0],&a[j][1]);
    printf("\n");
}

/*
 *函数名：CreatGraph
 *参数：图G，顶点集，关系集
 *返回值：void
 *功能：依据定义创建图
 */
void CreatGraph(Graph *G, defination df,int a[][2])
{
    int h,i,j;
    ArcNode *p,*q;
   // p=(ArcNode *)malloc(sizeof(ArcNode));
    for(h=0;h<(*G)->vexnum;(h)++)
    {
        ((*G)->vertices[h]).key=df[h]->key;
        strcpy(((*G)->vertices[h]).index,df[h]->index);
        ((*G)->vertices[h]).firstarc=NULL;
    }
    for(h=0;h<(*G)->arcnum;(h)++)
    {
        i=LocateVex(*G,a[h][0]);
        j=LocateVex(*G,a[h][1]);
        p=(ArcNode *)malloc(sizeof(ArcNode));
        p->next=NULL;
        p->adjvex=j;
        if((*G)->vertices[i-1].firstarc==NULL){
            (*G)->vertices[i-1].firstarc=(ArcNode *)malloc(sizeof(ArcNode));
            (*G)->vertices[i-1].firstarc->adjvex=p->adjvex;
            (*G)->vertices[i-1].firstarc->next=p->next;}
        else
            {
                q=(ArcNode *)malloc(sizeof(ArcNode));
                q=(*G)->vertices[i-1].firstarc;
                while(q->next)
                    q=q->next;
                q->next=p;
            }
    }
}
/*
 *函数名：LocateVex
 *参数：图指针，顶点关键字
 *返回值：status
 *功能：依据关键字找结点位置
 */
status LocateVex(Graph G,int key)
{
    int i;
    for(i=0;i<G->vexnum;i++)
    {
        if(G->vertices[i].key == key)
            return (i+1);
    }
    return ERROR;
}

/*函数名：DestroyGraph
 *参数：图G地址
 *返回值：status
 *功能：摧毁图
 */
status DestroyGraph(Graph G)
{
    int j,i=G->vexnum;
    ArcNode *p,*q;
    G->vexnum=G->arcnum=0;
    for(j=0;j<i;j++)
    {
        p=G->vertices[j].firstarc;
        while(p)
        {
            q=p->next;
            free(p);
            p=q;
        }
    }
    free(G);
    return OK;
}

/*
 *函数名：GetVex
 *参数：图地址，关键字key
 *返回值：index
 *功能：依据关键字找顶点信息
 */
char* GetVex(Graph G,int key)
{
    int i=(LocateVex(G,key));
    if(i)
        return G->vertices[i-1].index;
    else
        return NULL;

}

/*
 *函数名：PutVex
 *参数：图地址，关键字key，所赋值value
 *返回值：status
 *功能：给关键字为key的顶点赋值value
 */
status PutVex(Graph G, int key, char *value )
{
    int i=LocateVex(G,key);
    if(i)
    {
        memset(G->vertices[i-1].index,0,sizeof(char)*20);
        strcpy(G->vertices[i-1].index,value);
        return OK;
    }
    else
        return ERROR;
}

/*
 *函数名：FirstAdjvex
 *参数：图地址，顶点关键字key
 *返回值：status
 *功能：找顶点的第一个邻接顶点
 */
status FirstAdjvex(Graph G,int key)
{

    ArcNode *p=NULL;
    int i=LocateVex(G,key);
    if(i)
    {
        p=G->vertices[i-1].firstarc;
        if(p)
            return p->adjvex;
        else
            return ERROR;
    }
    else
        return OVERFLOW;
}

/*
 *函数名：NextAdjvex
 *参数：图地址，顶点关键字，邻接节点关键字
 *返回值：status
 *功能：返回邻接点的下一节点
 */
status NextAdjvex(Graph G,int key1,int key2)
{
    int i=LocateVex(G,key1);
    if(i>0)
        {
            ArcNode *p;
            //*p=(ArcNode *)malloc(sizeof(ArcNode));
            if(G->vertices[i-1].firstarc)
            {
                p=G->vertices[i-1].firstarc;
                while(p!=NULL)
                {
                    if(p->adjvex==key2)
                    {
                        if(p->next)
                            return p->next->adjvex;
                        else
                            return ERROR;
                    }
                    else
                        p=p->next;
                }
            }
            else
                return ERROR;
        }
    else if(i==ERROR){
        printf("该顶点无邻接节点!\n");
        return INFEASIBLE;}
    else
        return OVERFLOW;
}

/*
 *函数名：InsertAdjvex
 *参数：图地址，顶点指针
 *返回值：status
 *功能：在图中增添新顶点
 */
status InsertAdjvex(Graph G,VNode *p)
{
    if((G)->vexnum==20)
        return OVERFLOW;
    else
    {
        (G)->vertices[(G)->vexnum].key=p->key;
        strcpy((G)->vertices[(G)->vexnum].index,p->index);
        (G)->vertices[(G)->vexnum].firstarc=NULL;
        (G)->arcnum++;
        (G)->vexnum++;
        return OK;
    }
}

/*
 *函数名：DeletVex
 *参数：图地址，顶点key值
 *返回值：void
 *功能：删除顶点
 */
status DeleteVex(Graph G,int key)
{
    if(G->vexnum==0)
        return INFEASIBLE;
    else
    {
        int h,j,i=LocateVex(G,key);
        ArcNode *p,*q,*op;
        if(i)
        {
            p=G->vertices[i-1].firstarc;
            while(p)
            {
                q=p;
                p=p->next;
                free(q);
                G->arcnum--;
            }
            free(p);
            G->vexnum--;
            j=G->vexnum;
            for(i=i-1;i<j;i++)
            {
                  G->vertices[i]=G->vertices[i+1];
            }
            for(i=0;i<j;i++)
            {
                if(G->vertices[i].firstarc)
                {
                    p=G->vertices[i].firstarc;
                    h=0;
                    if(p){
                    while(p && (p->next))
                    {
                        if(!h && (G->vertices[i].firstarc->adjvex==key))
                        {
                            G->vertices[i].firstarc=p->next;
                            q=p;
                            p=p->next;
                            free(q);
                            h++;
                            G->arcnum--;
                        }
                        if(p->next)
                        {
                            if(p->next->adjvex!=key)
                            {
                                p=p->next;
                                h++;
                            }
                            else
                            {
                                q=p->next;
                                p->next=q->next;
                                p=p->next;
                                free(q);
                                G->arcnum--;
                            }
                        }
                    }}
                    if((G->vertices[i].firstarc->adjvex==key))
                    {
                        p=G->vertices[i-1].firstarc;
                        G->vertices[i-1].firstarc=NULL;
                        free(p);
                        G->arcnum--;
                    }
                }
            }
            for(i=0;i<G->vexnum;i++)
            {
                if(G->vertices[i].firstarc==NULL)
                    continue;
                else
                {
                    op=G->vertices[i].firstarc;
                    while(op!=NULL)
                    {
                        if((op->adjvex)>(LocateVex(G,key)))
                        {
                            op->adjvex=op->adjvex-1;
                        }
                        op=op->next;
                    }
                }
            }
            return OK;
        }
        else
            return ERROR;
    }
}

/*
 *函数名：InsertArc
 *参数：图地址，两定点关键字
 *返回值：status
 *功能：增加弧
 */
status InsertArc(Graph G,int key1,int key2)
{
    int i=LocateVex(G,key1);
    int j=LocateVex(G,key2);
    ArcNode *p,*q;
    if(i && j)
    {
        q=(ArcNode *)malloc(sizeof(ArcNode));
        q->adjvex=j;
        q->next=NULL;
        if(G->vertices[i-1].firstarc)
        {
            p=G->vertices[i-1].firstarc;
            if(p->adjvex==j)
                return OVERFLOW;
            else{
            while(p->next)
            {
                if(p=p->next->adjvex==j)
                    return OVERFLOW;
                else
                    p=p->next;
            }
            p->next=q;
            G->arcnum++;
            return OK;}
        }
        else
        {
            G->vertices[i-1].firstarc=q;
            G->arcnum++;
            return OK;
        }
    }
    else return ERROR;
}

/*
 *函数名：DeleteArc
 *参数：图地址，删除弧的弧头弧尾关键字
 *返回值：status
 *功能：删除弧
 */
status DeleteArc(Graph G, int key1,int key2)
{
    int i=LocateVex(G,key1);
    int j=LocateVex(G,key2);
    ArcNode *p,*q;
    if(i && j)
    {
        //q=(ArcNode *)malloc(sizeof(ArcNode));
        //q->adjvex=j;
        //q->next=NULL;
        p=G->vertices[i-1].firstarc;
        if(p){
        if(p->adjvex==j)
        {
            q=p->next;
            if(q)
            {
                G->vertices[i-1].firstarc=(q);
                free(p);
                G->arcnum--;
                return OK;
            }
            else
            {
                G->vertices[i-1].firstarc=NULL;
                free(p);
                G->arcnum--;
                return OK;
            }
        }
        else{
        while(p->next)
        {
            if(p->next->adjvex==j)
            {
                q=p->next;
                if(q->next)
                {
                    p->next=q->next;
                    free(q);
                    G->arcnum--;
                    return OK;
                }
                else
                {
                    p->next=NULL;
                    free(p->next);
                    G->arcnum--;
                    return OK;
                }
            }
            p=p->next;
        }
            return ERROR;
        }}
        else return ERROR;

    }
    else return ERROR;
}

/*
 *函数名：DFSTraverse
 *参数：图地址,visited数组
 *返回值：void
 *功能：深度优先遍历图
 */
void DFSTraverse(Graph G,int visited[])
{
    int v;
    for(v=0;v<G->vexnum; v++)    //初始化各顶点未访问状态
        visited[v]=0;
    for(v=0;v<G->vexnum; v++)
        if (!visited[v])         //从一个未访问的顶点开始
	        DFS(G, v, visit,visited);
}

void DFS(Graph G,int v,status (*visit)(Graph G,int i),int visited[])
{
    int w;
    visited[v]=1;
    visit(G,v);
    int a=G->vertices[v].key;
    for(w=FirstAdjvex(G,a)-1;w>=0; w=NextAdjvex(G,a,w+1)-1)
        if (!visited[w])     //处理所有未访问的邻接顶点
		    DFS(G, w,visit,visited);
}

status visit(Graph G,int i)
{
    if(i>=G->vexnum)
        return ERROR;
    else
    {
        printf("index:%s\tkey:%d\n",G->vertices[i].index,G->vertices[i].key);
        return OK;
    }
}

/*
 *函数名：BFSTraverse
 *参数：图地址,visited数组，visit函数指针
 *返回值：void
 *功能：广度优先搜索遍历图
 */
void BFSTraverse(Graph G,int visited[],status (*visit)(Graph G,int i))
{
    int w,u,v;
    LinkQueue Q;
    for(v=0; v<G->vexnum; v++)
        visited[v]=0;
    InitQueue(&Q);
    for(v=0;v<G->vexnum; v++)  //按顶点位置序号依次选择顶点
        if (!visited[v])
        {     //遇到未访问过的顶点开始遍历
            visited[v]=1;
            visit(G,v);
            EnQueue(&Q,v);
            while(!QueueEmpty(Q))
            {
	            DeQueue(&Q,&u);
	            int a=G->vertices[u].key;
                for(w=FirstAdjvex(G,a)-1;w>=0; w=NextAdjvex(G,a,(w+1))-1)
                //for(w=FirstAdjvex(G,u+1)-1;w>=0; w=NextAdjvex(G,u+1,w)-1)
                    if (!visited[w])
                    {
                        visited[w]=1; visit(G,w);EnQueue(&Q,w);
                    }
        }
    }

}

status InitQueue(LinkQueue *Q)
{
    (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(LinkQueue));
    if(!(*Q).front) exit(OVERFLOW);
    (*Q).front->next=NULL;
    return OK;
}

status EnQueue(LinkQueue *Q,int e)
{
    QueuePtr p=(QueuePtr)malloc(sizeof(LinkQueue));
    if(!p)
        exit(OVERFLOW);
    p->data=e;
    p->next=NULL;
    (*Q).rear->next=p;
    (*Q).rear=p;
    return OK;
}

status QueueEmpty(LinkQueue Q)
{
    if(Q.front==Q.rear) return 1;
    else return FALSE;
}

status DeQueue(LinkQueue *Q,int *e)
{
    QueuePtr p;
    if((*Q).front==(*Q).rear) return ERROR;
    p=(*Q).front->next;
    *e=p->data;
    (*Q).front->next=p->next;
    if((*Q).rear==p)
        (*Q).rear=(*Q).front;
    free(p);
    return OK;
}


 /*函数名：Savegraph
 *参数：图,文件指针,文件名
 *返回值：status
 *功能：保存图
 */
status Savegraph(ALGraph G,FILE *fp,char *filename)
{
    if((fp=fopen(filename,"wb"))==NULL)
	{
        printf("文件打开失败\n ");
        return ERROR;
	}
	int vexnum, arcnum;
	vexnum = G.vexnum;
	arcnum = G.arcnum;
	fwrite(&vexnum,sizeof(int),1,fp);          //写入顶点数
	fwrite(&arcnum,sizeof(int),1,fp);          //写入弧数
	int i, data,j,x[G.vexnum];
	for(i=0;i<G.vexnum;i++)                    //按顺序写入顶点的相关信息
	{
		data = G.vertices[i].key;
		int lenth=strlen(G.vertices[i].index);
		fwrite(&lenth,sizeof(int),1,fp);
		for(j=0;j<lenth;j++)
            fwrite(&G.vertices[i].index[j],sizeof(char),1,fp);
	    fwrite(&data,sizeof(int),1,fp);
	}
	ArcNode *p;
	for(i = 0; i < G.vexnum; i++)              //按顺序写入弧的信息
	{
	    if(G.vertices[i].firstarc == NULL)
            continue;
	    else
	    {
            p = G.vertices[i].firstarc;
            while(p!=NULL)
            {
                fwrite(&i,sizeof(int),1,fp);
                fwrite(&(p->adjvex),sizeof(int),1,fp);
                p=p->next;
            }
	    }
	}
    fclose(fp);
    return OK;
}

/*
 *函数名：Loadgraph
 *参数：图地址,文件指针,文件名
 *返回值：status
 *功能：读取图
 */
status Loadgraph(ALGraph *G,FILE *fp,char *filename)
{
    if((fp = fopen(filename,"rb")) == NULL)
	{
        printf("文件打开失败\n ");
        return ERROR;
	}
	fread(&(G->vexnum),sizeof(int),1,fp);
    fread(&(G->arcnum),sizeof(int),1,fp);
    int i=0,m,n,o,j,x[G->vexnum];
    ArcNode *p,*q;
    for(i = 0; i < G->vexnum; i++)
    {
        fread(&o,sizeof(int),1,fp);
        memset(G->vertices[i].index,0,20*sizeof(char));
        for(j=0;j<o;j++)
            fread(&(G->vertices[i].index[j]),sizeof(char),1,fp);
        fread(&(G->vertices[i].key),sizeof(int),1,fp);
	}
	for(i=0;i<G->vexnum;i++)
        G->vertices[i].firstarc = NULL;
    for(i=0;i<G->arcnum;i++)
	{
		fread(&m,sizeof(int),1,fp);
		fread(&n,sizeof(int),1,fp);
		p=(ArcNode*)malloc(sizeof(ArcNode));
	    p->adjvex=n;
	    p->next=NULL;
		if(G->vertices[m].firstarc==NULL)
            G->vertices[m].firstarc=p;
	    else{
	   	    q = G->vertices[m].firstarc;
	   	    if(q->next==NULL)
                q->next=p;
	   	    else{
                while(q->next!=NULL)
                    q=q->next;
                q->next=p;
			}
        }
	}
    fclose(fp);
    return OK;
}

#endif
