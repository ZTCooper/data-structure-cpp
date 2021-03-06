#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFINITY INT_MAX//最大值
#define MAX_VERTEX_NUM 20//最大顶点个数
typedef int Status;
typedef int VRType;
typedef int InfoType;
typedef enum{DG,DN,UDG,UDN}GraphKind;

typedef struct ArcCell{
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef char VertexType;
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;//邻接矩阵
	int vexnum,arcnum;//顶点数，弧数
	GraphKind kind;
}MGraph;

int LocateVex(MGraph G,char v){
	int i;
	for(i=0;i<G.vexnum;++i)
		if(G.vexs[i]==v) return i;
		return -1;
}

Status CreateDG(MGraph &G){
		int i,j,k,w;
	VertexType v1,v2;
	printf("输入顶点数G.vexnum:");scanf("%d",&G.vexnum);
	printf("输入边数G.arcnum:");scanf("%d",&G.arcnum);
	getchar();
	for(i=0;i<G.vexnum;i++){
		printf("输入顶点G.vexs[%d]:",i);
		scanf("%c",&G.vexs[i]);
		getchar();
	}
	for(i=0;i<G.vexnum;++i)//初始化邻接矩阵
		for(j=0;j<G.vexnum;++j){
			G.arcs[i][j].adj=0;
			G.arcs[i][j].info=NULL;
			}
		for(k=0;k<G.arcnum;++k){
			printf("输入第%d条边的两个端点:\n",k+1);
			scanf("%c%c",&v1,&v2);
			getchar();
			i=LocateVex(G,v1);	j=LocateVex(G,v2);
			G.arcs[i][j].adj=1;
		}
		return OK;
}//构造有向图 

Status CreateDN(MGraph &G){
	int i,j,k,w;
	VertexType v1,v2;
	printf("输入顶点数G.vexnum:");scanf("%d",&G.vexnum);
	printf("输入边数G.arcnum:");scanf("%d",&G.arcnum);
	getchar();
	for(i=0;i<G.vexnum;i++){
		printf("输入顶点G.vexs[%d]:",i);
		scanf("%c",&G.vexs[i]);
		getchar();
	}
	for(i=0;i<G.vexnum;++i)//初始化邻接矩阵
		for(j=0;j<G.vexnum;++j){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;
		}
		for(k=0;k<G.arcnum;++k){
			printf("输入第%d条边vi、vj和权值w(int):\n",k+1);
			scanf("%c%c%d",&v1,&v2,&w);
			getchar();
			i=LocateVex(G,v1);	j=LocateVex(G,v2);
			G.arcs[i][j].adj=w;//弧<v1,v2>的权值
		}
		return OK;
}//构造有向网 

Status CreateUDG(MGraph &G){
	int i,j,k,w;
	VertexType v1,v2;
	printf("输入顶点数G.vexnum:");scanf("%d",&G.vexnum);
	printf("输入边数G.arcnum:");scanf("%d",&G.arcnum);
	getchar();
	for(i=0;i<G.vexnum;i++){
		printf("输入顶点G.vexs[%d]:",i);
		scanf("%c",&G.vexs[i]);
		getchar();
	}
	for(i=0;i<G.vexnum;++i)//初始化邻接矩阵
		for(j=0;j<G.vexnum;++j){
			G.arcs[i][j].adj=0;
			G.arcs[i][j].info=NULL;
			}
		for(k=0;k<G.arcnum;++k){
			printf("输入第%d条边的两个端点:\n",k+1);
			scanf("%c%c",&v1,&v2);
			getchar();
			i=LocateVex(G,v1);	j=LocateVex(G,v2);
			G.arcs[i][j].adj=1;
			G.arcs[j][i].adj=G.arcs[i][j].adj;
		}
		return OK;
}//构造无向图 

Status CreateUDN(MGraph &G){
	int i,j,k,w;
	VertexType v1,v2;
	printf("输入顶点数G.vexnum:");scanf("%d",&G.vexnum);
	printf("输入边数G.arcnum:");scanf("%d",&G.arcnum);
	getchar();
	for(i=0;i<G.vexnum;i++){
		printf("输入顶点G.vexs[%d]:",i);
		scanf("%c",&G.vexs[i]);
		getchar();
	}
	for(i=0;i<G.vexnum;++i)//初始化邻接矩阵
		for(j=0;j<G.vexnum;++j){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;
		}
		for(k=0;k<G.arcnum;++k){
			printf("输入第%d条边vi、vj和权值w(int):\n",k+1);
			scanf("%c%c%d",&v1,&v2,&w);
			getchar();
			i=LocateVex(G,v1);	j=LocateVex(G,v2);
			G.arcs[i][j].adj=w;//弧<v1,v2>的权值
			G.arcs[j][i].adj=G.arcs[i][j].adj;
		}
		return OK;
}//构造无向网


Status CreateGraph(MGraph &G){
	printf("请输入图的种类：0表示DG，1表示DN，2表示UDG，3表示UDN\n");
	scanf("%d",&G.kind);
	switch(G.kind){
	case DG:return CreateDG(G);
	case DN:return CreateDN(G);
	case UDG:return CreateUDG(G);
	case UDN:return CreateUDN(G);
	default:return ERROR;
	}
}

void list(MGraph G){
	int i,j;
	printf("输出邻接矩阵：\n");
	for(i=0;i<G.vexnum;++i){
		printf("%c----",G.vexs[i]);
		for(j=0;j<G.vexnum;++j)
			if(G.arcs[i][j].adj==INFINITY)
				printf("%4s","∞");
			else
				printf("%4d",G.arcs[i][j].adj);
			printf("\n");
	}
}

int main(){
	MGraph G;
	CreateGraph(G);
	list(G);
}
