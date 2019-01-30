#include "Graph.h"
#include "function.h"

int main()
{
    Defination df;
    int N,U,T;
    printf("请输入您本次操作所要管理图的数目：");
    scanf("%d",&N);
    printf("\n");
    printf("请输入你想要操作图的位序：\n");
    ALGraph G[N];
    FILE *fp;
    char index[10],value[10],filename[20];
    char *dex=index;
    int  op = 1,a[21][2],visited[20];
    ElemType d,s,key,key1,flag;
    char ch;
    while((scanf("%d",&T)!=EOF)&&1<=T&&T<=N){
            U=T-1;
            flag=0;
            Graph g=&G[U];
    while(op)
    {
        system("cls");	printf("\n\n");
        printf("                         Menu for Graph                         \n");
        printf("----------------------------------------------------------------\n");
        printf("    	  1.  InitiaGraph            2.  CreateCraph(&G,V,VR)   \n");
        printf("    	  3.  DestroyCraph(&G)       4.  Locate(G,u)            \n");
        printf("          5.  GetVex(G,v)            6.  PutVex(&G,v,value)     \n");
        printf("          7.  FirstAdjVex(G,v)       8.  NextAdjVex(G,v,w)      \n");
        printf("    	  9.  InsertVex(&G,v)        10. DeleteVex(&G,v)        \n");
        printf("    	  11. InsertArc(&G,v,w)      12. DeleteArc(&G,v,w)       \n");
        printf("    	  13. DFSTraverse(G,visit()) 14. BFSTraverse(G,visit()) \n");
        printf("    	  15. load                   16. save                   \n");
        printf("          0.  EXIT\n");
        printf("----------------------------------------------------------------\n");
        printf("    输入执行项[0~16]:");
        while(!scanf("%d", &op))
        {
            printf("输入数据不合法!\n");
            while ((ch = getchar()) != EOF && ch != '\n');
        }
        while ((ch = getchar()) != EOF && ch != '\n');
        switch(op){
        case 1:
            InitiaGraph(&G[U]);
            memset(G,0,sizeof( ALGraph));
            flag=1;
            printf("初始化成功！");
            system("pause");
            break;
        case 2:
            df=CreatNode();
            G[U].vexnum=df.n;
            printf("创建了%d个顶点，输入要创建的弧的数目：",df.n);
            scanf("%d",&d);
            G[U].arcnum=d;
            CreatVR(d,a);
            CreatGraph(&g,df.df,a);
            printf("创建成功！\n");
            flag=1;
            system("pause");
            break;
        case 3:
            if(flag)
            {
                s=DestroyGraph(&G[U]);
                if(s)
                    printf("销毁成功！");
                flag=0;
            }
            else
                printf("图不存在或者已经被销毁！");
            system("pause");
            break;
        case 4:
            if(flag)
            {
                printf("输入要查找顶点的关键字key：");
                input(&key);
                s=LocateVex(&G[U],key);
                if(s)
                    printf("该顶点位置为：%d\n", s);
                else
                    printf("该顶点不存在！\n");
            }
            else
                printf("错误操作！图不存在或为空！\n");
            system("pause");
            break;
        case 5:
            if(flag)
            {
                printf("输入要查找顶点关键字key:");
                input(&key);
                dex=GetVex(&G[U],key);
                if(dex)
                    printf("该顶点index为：%s",dex);
                else
                    printf("该顶点不存在！\n");
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 6:
            if(flag)
            {
                printf("输入要赋值顶点的关键字key：");
                input(&key);
                printf("输入要赋予的值value：");
                scanf("%s",value);
                s=PutVex(&G[U],key,value);
                if(s)
                    printf("赋值成功!");
                else
                    printf("赋值失败！");
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 7:
            if(flag)
            {
                printf("输入要查找顶点关键字key：");
                input(&key);
                s=FirstAdjvex(&G[U],key);
                if(s>0)
                    printf("该顶点第一个邻接顶点index：%s\tkey:%d \n",G[U].vertices[s-1].index,G[U].vertices[s-1].key);
                else if(s==ERROR)
                    printf("该顶点无邻接节点");
                else
                    printf("操作失败！");
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 8:
            if(flag)
            {
                printf("输入顶点key：");
                input(&key);
                printf("输入顶点key1：");
                input(&key1);
                s=NextAdjvex(&G[U],key, key1);
                if(s>0)
                {
                    printf("所查顶点下一邻接顶点index：%s\tkey:%d\n",G[U].vertices[s-1].index,G[U].vertices[s-1].key);
                }
                else if(s==ERROR)
                    printf("该顶点无邻接节点\n");
                else
                    printf("操作失败！");

            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 9:
            if(flag)
            {
                VNode *p=(VNode*)malloc(sizeof(VNode));
                printf("输入新插入节点key：");
                input(&(p->key));
                printf("index：");
                scanf("%s",p->index);
                s=InsertAdjvex(&G[U],p);
                if(s)
                {
                    printf("插入成功！");
                }
                else
                    printf("操作失败！");
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 10:
            if(flag)
            {
                printf("输入要删除节点key：");
                input(&key);
                s=DeleteVex(&G[U],key);
                if(s)
                    printf("该节点已删除！\n");
                else
                    printf("操作失败！");
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 11:
            if(flag)
            {
                printf("输入要增加弧的弧头key：");
                input(&key);
                printf("输入要增加的弧尾key：");
                input(&key1);
                s=InsertArc(&G[U],key,key1);
                if(s)
                    printf("增添弧成功！");
                else
                    printf("操作失败！");
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 12:
            if(flag)
            {
                printf("输入要删除弧的弧头key：");
                input(&key);
                printf("输入要删除弧的弧尾key：");
                input(&key1);
                s=DeleteArc(&G[U],key,key1);
                if(s)
                    printf("删除成功！");
                else
                    printf("操作失败！");
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 13:
            if(flag)
            {
                if(G[U].vexnum==0)
                    printf("空图！");
                else{
                for(s=0;s<20;s++)
                    visited[s]=1;
                DFSTraverse(&G[U],visited);
                printf("\n\n");}
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 14:
            if(flag)
            {
                if(G[U].vexnum==0)
                    printf("空图！");
                else{
                for(s=0;s<20;s++)
                    visited[s]=1;
                BFSTraverse(&G[U],visited,visit);
                printf("\n\n");}
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 16:
            if(flag)
            {
                printf("输入文件名: ");
                scanf("%s",filename);
                if(Savegraph(G[U],fp,filename)==OK)
                    printf("文件写入成功！ \n");
                else
                    printf("文件写入失败！ \n");
            }
            else
                printf("图不存在！\n");
            system("pause");
            break;
        case 15:
            if(flag)
            {
                printf("输入文件名: ");
                scanf("%s",filename);
                if(Loadgraph(&G[U],fp,filename)==OK)
                    printf("文件读取成功！ \n");
                else
                    printf("文件读取失败！ \n");
            }
            else
                printf("操作失败！\n");
            system("pause");
            break;
        case 0:
            break;
        default:
            printf("非法输入\n");
             break;
        }
    }
    printf("请选择下一个需要操作的顺序表的序号:\n");
	op=1;
	continue;
    }
    printf("欢迎下次再使用本系统！\n");
}
