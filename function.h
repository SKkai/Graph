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


/*��������InitiaGraph
 *������ͼ��ַ
 *����ֵ��int
 *���ܣ���ʼ��ͼ
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
 *��������CreatNode
 *������ͼ��ַ��������
 *����ֵ��Defination
 *���ܣ�����ͼ�Ķ��㼯
 */
Defination CreatNode()
{

    Defination *DF = (Defination *)malloc(sizeof(Defination));
    defination df=NULL;
    //VNode *t;
    int key,n=0;
    printf("����ͼ�Ķ��㼯,��EOF��������\nkey:");
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
 *��������CreatVR
 *������������������ά����
 *����ֵ:void
 *���ܣ�����ͼ�Ĺ�ϵ��
 */
void  CreatVR(int i,int a[][2])
{
    int j;
    printf("����ÿ���������key���յ�key��");
    for(j=0;j<i;j++)
        scanf("%d %d",&a[j][0],&a[j][1]);
    printf("\n");
}

/*
 *��������CreatGraph
 *������ͼG�����㼯����ϵ��
 *����ֵ��void
 *���ܣ����ݶ��崴��ͼ
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
 *��������LocateVex
 *������ͼָ�룬����ؼ���
 *����ֵ��status
 *���ܣ����ݹؼ����ҽ��λ��
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

/*��������DestroyGraph
 *������ͼG��ַ
 *����ֵ��status
 *���ܣ��ݻ�ͼ
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
 *��������GetVex
 *������ͼ��ַ���ؼ���key
 *����ֵ��index
 *���ܣ����ݹؼ����Ҷ�����Ϣ
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
 *��������PutVex
 *������ͼ��ַ���ؼ���key������ֵvalue
 *����ֵ��status
 *���ܣ����ؼ���Ϊkey�Ķ��㸳ֵvalue
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
 *��������FirstAdjvex
 *������ͼ��ַ������ؼ���key
 *����ֵ��status
 *���ܣ��Ҷ���ĵ�һ���ڽӶ���
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
 *��������NextAdjvex
 *������ͼ��ַ������ؼ��֣��ڽӽڵ�ؼ���
 *����ֵ��status
 *���ܣ������ڽӵ����һ�ڵ�
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
        printf("�ö������ڽӽڵ�!\n");
        return INFEASIBLE;}
    else
        return OVERFLOW;
}

/*
 *��������InsertAdjvex
 *������ͼ��ַ������ָ��
 *����ֵ��status
 *���ܣ���ͼ�������¶���
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
 *��������DeletVex
 *������ͼ��ַ������keyֵ
 *����ֵ��void
 *���ܣ�ɾ������
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
 *��������InsertArc
 *������ͼ��ַ��������ؼ���
 *����ֵ��status
 *���ܣ����ӻ�
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
 *��������DeleteArc
 *������ͼ��ַ��ɾ�����Ļ�ͷ��β�ؼ���
 *����ֵ��status
 *���ܣ�ɾ����
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
 *��������DFSTraverse
 *������ͼ��ַ,visited����
 *����ֵ��void
 *���ܣ�������ȱ���ͼ
 */
void DFSTraverse(Graph G,int visited[])
{
    int v;
    for(v=0;v<G->vexnum; v++)    //��ʼ��������δ����״̬
        visited[v]=0;
    for(v=0;v<G->vexnum; v++)
        if (!visited[v])         //��һ��δ���ʵĶ��㿪ʼ
	        DFS(G, v, visit,visited);
}

void DFS(Graph G,int v,status (*visit)(Graph G,int i),int visited[])
{
    int w;
    visited[v]=1;
    visit(G,v);
    int a=G->vertices[v].key;
    for(w=FirstAdjvex(G,a)-1;w>=0; w=NextAdjvex(G,a,w+1)-1)
        if (!visited[w])     //��������δ���ʵ��ڽӶ���
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
 *��������BFSTraverse
 *������ͼ��ַ,visited���飬visit����ָ��
 *����ֵ��void
 *���ܣ����������������ͼ
 */
void BFSTraverse(Graph G,int visited[],status (*visit)(Graph G,int i))
{
    int w,u,v;
    LinkQueue Q;
    for(v=0; v<G->vexnum; v++)
        visited[v]=0;
    InitQueue(&Q);
    for(v=0;v<G->vexnum; v++)  //������λ���������ѡ�񶥵�
        if (!visited[v])
        {     //����δ���ʹ��Ķ��㿪ʼ����
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


 /*��������Savegraph
 *������ͼ,�ļ�ָ��,�ļ���
 *����ֵ��status
 *���ܣ�����ͼ
 */
status Savegraph(ALGraph G,FILE *fp,char *filename)
{
    if((fp=fopen(filename,"wb"))==NULL)
	{
        printf("�ļ���ʧ��\n ");
        return ERROR;
	}
	int vexnum, arcnum;
	vexnum = G.vexnum;
	arcnum = G.arcnum;
	fwrite(&vexnum,sizeof(int),1,fp);          //д�붥����
	fwrite(&arcnum,sizeof(int),1,fp);          //д�뻡��
	int i, data,j,x[G.vexnum];
	for(i=0;i<G.vexnum;i++)                    //��˳��д�붥��������Ϣ
	{
		data = G.vertices[i].key;
		int lenth=strlen(G.vertices[i].index);
		fwrite(&lenth,sizeof(int),1,fp);
		for(j=0;j<lenth;j++)
            fwrite(&G.vertices[i].index[j],sizeof(char),1,fp);
	    fwrite(&data,sizeof(int),1,fp);
	}
	ArcNode *p;
	for(i = 0; i < G.vexnum; i++)              //��˳��д�뻡����Ϣ
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
 *��������Loadgraph
 *������ͼ��ַ,�ļ�ָ��,�ļ���
 *����ֵ��status
 *���ܣ���ȡͼ
 */
status Loadgraph(ALGraph *G,FILE *fp,char *filename)
{
    if((fp = fopen(filename,"rb")) == NULL)
	{
        printf("�ļ���ʧ��\n ");
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
