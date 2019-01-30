#include "Graph.h"
#include "function.h"

int main()
{
    Defination df;
    int N,U,T;
    printf("�����������β�����Ҫ����ͼ����Ŀ��");
    scanf("%d",&N);
    printf("\n");
    printf("����������Ҫ����ͼ��λ��\n");
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
        printf("    ����ִ����[0~16]:");
        while(!scanf("%d", &op))
        {
            printf("�������ݲ��Ϸ�!\n");
            while ((ch = getchar()) != EOF && ch != '\n');
        }
        while ((ch = getchar()) != EOF && ch != '\n');
        switch(op){
        case 1:
            InitiaGraph(&G[U]);
            memset(G,0,sizeof( ALGraph));
            flag=1;
            printf("��ʼ���ɹ���");
            system("pause");
            break;
        case 2:
            df=CreatNode();
            G[U].vexnum=df.n;
            printf("������%d�����㣬����Ҫ�����Ļ�����Ŀ��",df.n);
            scanf("%d",&d);
            G[U].arcnum=d;
            CreatVR(d,a);
            CreatGraph(&g,df.df,a);
            printf("�����ɹ���\n");
            flag=1;
            system("pause");
            break;
        case 3:
            if(flag)
            {
                s=DestroyGraph(&G[U]);
                if(s)
                    printf("���ٳɹ���");
                flag=0;
            }
            else
                printf("ͼ�����ڻ����Ѿ������٣�");
            system("pause");
            break;
        case 4:
            if(flag)
            {
                printf("����Ҫ���Ҷ���Ĺؼ���key��");
                input(&key);
                s=LocateVex(&G[U],key);
                if(s)
                    printf("�ö���λ��Ϊ��%d\n", s);
                else
                    printf("�ö��㲻���ڣ�\n");
            }
            else
                printf("���������ͼ�����ڻ�Ϊ�գ�\n");
            system("pause");
            break;
        case 5:
            if(flag)
            {
                printf("����Ҫ���Ҷ���ؼ���key:");
                input(&key);
                dex=GetVex(&G[U],key);
                if(dex)
                    printf("�ö���indexΪ��%s",dex);
                else
                    printf("�ö��㲻���ڣ�\n");
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 6:
            if(flag)
            {
                printf("����Ҫ��ֵ����Ĺؼ���key��");
                input(&key);
                printf("����Ҫ�����ֵvalue��");
                scanf("%s",value);
                s=PutVex(&G[U],key,value);
                if(s)
                    printf("��ֵ�ɹ�!");
                else
                    printf("��ֵʧ�ܣ�");
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 7:
            if(flag)
            {
                printf("����Ҫ���Ҷ���ؼ���key��");
                input(&key);
                s=FirstAdjvex(&G[U],key);
                if(s>0)
                    printf("�ö����һ���ڽӶ���index��%s\tkey:%d \n",G[U].vertices[s-1].index,G[U].vertices[s-1].key);
                else if(s==ERROR)
                    printf("�ö������ڽӽڵ�");
                else
                    printf("����ʧ�ܣ�");
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 8:
            if(flag)
            {
                printf("���붥��key��");
                input(&key);
                printf("���붥��key1��");
                input(&key1);
                s=NextAdjvex(&G[U],key, key1);
                if(s>0)
                {
                    printf("���鶥����һ�ڽӶ���index��%s\tkey:%d\n",G[U].vertices[s-1].index,G[U].vertices[s-1].key);
                }
                else if(s==ERROR)
                    printf("�ö������ڽӽڵ�\n");
                else
                    printf("����ʧ�ܣ�");

            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 9:
            if(flag)
            {
                VNode *p=(VNode*)malloc(sizeof(VNode));
                printf("�����²���ڵ�key��");
                input(&(p->key));
                printf("index��");
                scanf("%s",p->index);
                s=InsertAdjvex(&G[U],p);
                if(s)
                {
                    printf("����ɹ���");
                }
                else
                    printf("����ʧ�ܣ�");
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 10:
            if(flag)
            {
                printf("����Ҫɾ���ڵ�key��");
                input(&key);
                s=DeleteVex(&G[U],key);
                if(s)
                    printf("�ýڵ���ɾ����\n");
                else
                    printf("����ʧ�ܣ�");
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 11:
            if(flag)
            {
                printf("����Ҫ���ӻ��Ļ�ͷkey��");
                input(&key);
                printf("����Ҫ���ӵĻ�βkey��");
                input(&key1);
                s=InsertArc(&G[U],key,key1);
                if(s)
                    printf("�����ɹ���");
                else
                    printf("����ʧ�ܣ�");
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 12:
            if(flag)
            {
                printf("����Ҫɾ�����Ļ�ͷkey��");
                input(&key);
                printf("����Ҫɾ�����Ļ�βkey��");
                input(&key1);
                s=DeleteArc(&G[U],key,key1);
                if(s)
                    printf("ɾ���ɹ���");
                else
                    printf("����ʧ�ܣ�");
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 13:
            if(flag)
            {
                if(G[U].vexnum==0)
                    printf("��ͼ��");
                else{
                for(s=0;s<20;s++)
                    visited[s]=1;
                DFSTraverse(&G[U],visited);
                printf("\n\n");}
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 14:
            if(flag)
            {
                if(G[U].vexnum==0)
                    printf("��ͼ��");
                else{
                for(s=0;s<20;s++)
                    visited[s]=1;
                BFSTraverse(&G[U],visited,visit);
                printf("\n\n");}
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 16:
            if(flag)
            {
                printf("�����ļ���: ");
                scanf("%s",filename);
                if(Savegraph(G[U],fp,filename)==OK)
                    printf("�ļ�д��ɹ��� \n");
                else
                    printf("�ļ�д��ʧ�ܣ� \n");
            }
            else
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        case 15:
            if(flag)
            {
                printf("�����ļ���: ");
                scanf("%s",filename);
                if(Loadgraph(&G[U],fp,filename)==OK)
                    printf("�ļ���ȡ�ɹ��� \n");
                else
                    printf("�ļ���ȡʧ�ܣ� \n");
            }
            else
                printf("����ʧ�ܣ�\n");
            system("pause");
            break;
        case 0:
            break;
        default:
            printf("�Ƿ�����\n");
             break;
        }
    }
    printf("��ѡ����һ����Ҫ������˳�������:\n");
	op=1;
	continue;
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}
