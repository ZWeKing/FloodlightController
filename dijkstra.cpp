/*Dijkstra algrithm*/
#include <iostream>
#include<stack>
#include<stdlib.h>
#define M 100    //直连矩阵的行上限
#define N 100	//直连矩阵列上限
#define INT_MAX 10000	//定义无穷大
using namespace std;

typedef struct node
{
    int matrix[N][M];      //直连矩阵，变量值为链路权重
    int n;                 //有向图中的节点数目
    int e;                 //链路的数量
}MGraph;

void DijkstraPath(MGraph g,int *dist,int *path,int v0)   //v0 是源点，根节点
{
    int i,j,k;
    int c=0;
    bool *visited=(bool *)malloc(sizeof(bool)*g.n);
    for(i=0;i<g.n;i++)     //初始化每个节点的相关信息
    {
        if(g.matrix[v0][i]>0&&i!=v0)
        {
            dist[i]=g.matrix[v0][i];
            path[i]=v0;     //path 记录到节点i的前一个节点
        }
        else
        {
            dist[i]=INT_MAX;    //无直连链路时，定义权值为无穷大
            path[i]=-1;		//定义前一个节点为-1
        }
        visited[i]=false;
        if(c==0){
            path[v0]=v0;
            dist[v0]=0;
            c=1;
        }
    }
    visited[v0]=true;
    for(i=1;i<g.n;i++)     //计算到其他n-1个节点的路径和权值
    {
        int min=INT_MAX;
        int u;
        for(j=0;j<g.n;j++)    //寻找到某个节点的权值最小的节点，并将该节点标注为已知
        {
            if(visited[j]==false&&dist[j]<min)
            {
                min=dist[j];
                u=j;
            }
        }
        visited[u]=true;
        for(k=0;k<g.n;k++)   //更新dist和path数组
        {
            if(visited[k]==false&&g.matrix[u][k]>0&&min+g.matrix[u][k]<dist[k])
            {
                dist[k]=min+g.matrix[u][k];
                path[k]=u;
            }
        }
    }
    free(visited);
}

void showPath(int *path,int v,int v0)   //打印源节点到各个其他节点的路径
{
    stack<int> s;
    int u=v;
    while(v!=v0)
    {
        s.push(v);
        v=path[v];
    }
    s.push(v);
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
}

int main(int argc, char *argv[])
{
    int n,e;     //节点和链路数目
    cout<<"please set the number of nodes and links"<<endl;
    int c=0;
    while(cin>>n>>e&&e!=0)
    {
        int i,j;
        int s,t,w;      //s和t分别是有向图中的元节点和目的节点，w是这条链路的权重
        MGraph g;
        int v0;
        int *dist=(int *)malloc(sizeof(int)*n);
        int *path=(int *)malloc(sizeof(int)*n);
        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                g.matrix[i][j]=0;
        g.n=n;
        g.e=e;
	    cout<<"set the source node,the destination node,weight"<<endl;
        for(i=0;i<e;i++)
        {
            cin>>s>>t>>w;
            g.matrix[s][t]=w;
        }
	    cout<<"please input the source nodes:"<<endl;
        cin>>v0;        //获得源节点
        DijkstraPath(g,dist,path,v0);
        for(i=0;i<n;i++)
        {
            if(i!=v0)
            {
                showPath(path,i,v0);
                cout<<dist[i]<<endl;
            }
        }
        free(dist);
        free(path);
    }
    return 0;
}