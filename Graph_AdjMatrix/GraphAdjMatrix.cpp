#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include "Queue.h"
#include "Arraylist.h"

#define WHITE 1
#define GREY 2
#define BLACK 3
#define BFS 4
#define DFS 5
#define NULL_VALUE (-999999)
#define INFINITY 999999
int time=0;
using namespace std;
//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
    int *color ,*parent ,*dist, *discoveryTime, *finishTime;
    //define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

 public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
    void dfs();

    void printStat(int type);

    void dfs_visitM(int vertex);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    directed = dir ; //set direction of the graph
    color =0; //define other variables to be initialized
    parent=0;
    dist=0;
    discoveryTime=0;
    finishTime=0;
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    color = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];
    discoveryTime=new int[nVertices];
    finishTime=new int[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    if(directed)matrix[u][v]=0;
    else {
        matrix[u][v] = 0;
        matrix[v][u] =0;
    }
    }

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) {
        cout<<"INVALID INDEX\n";
        return false;
    }
    if(directed) return matrix[u][v]==1;
    else return matrix[u][v]==1 && matrix[v][u]==1 ;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices ) return NULL_VALUE;

    bool isLoop=matrix[u][u]==1;
    int degree=0;
    for(int i=0;i<nVertices;degree += matrix[u][i],i++);
    if(!directed)
    {
        if(isLoop)return degree+1;
        else return degree;
    }
    else
    {
        for(int i=0;i<nVertices;i++)
        {
            if(i==u)continue;
            if(matrix[i][u])degree++;
        }
        if(isLoop)return degree+1;
        else return degree;
    }
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    int U[nVertices]={0},V[nVertices]={0};
    for(int i=0;i<nVertices;i++)if(matrix[u][i]==1)U[i]=1;

    for(int i=0;i<nVertices;i++)if(matrix[v][i]==1)V[i]=1;

    int i=0;
    for(i=0;i<nVertices;i++)if(U[i] & V[i])return true;

    if(i==nVertices)return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int visited=q.dequeue();
        color[visited]=BLACK;
        //cout<<visited<<"->";
        for(int i=0;i<nVertices;i++)
        {
            int neighbourOfV;
            if(matrix[visited][i]!=0) {
                neighbourOfV = i;
                //int neighbourOfV=[visited].getItem(i);
                if (color[neighbourOfV] == WHITE) {
                    q.enqueue(neighbourOfV);
                    color[neighbourOfV] = GREY;
                    dist[neighbourOfV] = dist[visited] + 1;
                    parent[neighbourOfV] = visited;
                }
            }
        }

    }
   // cout<<"|\n";
}

void Graph::dfs()
{
    //write this function
    time = 0;
    for(int i = 0; i<nVertices ; i++){
        color[i] = WHITE;
        parent[i]=-1;
    }
    for(int i = 0; i<nVertices ; i++){
        if(color[i] == WHITE){
            dfs_visitM(i);
        }
    }
    cout<<"|\n";
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || u>=nVertices || v>=nVertices) {
        cout<<"Invalid Index\n";
        return 0; //vertex out of range
    }
    bfs(u);
    return dist[v];

}
void Graph::dfs_visitM(int vertex){
    if(color[vertex] == BLACK){
        return;
    }

    time++;
    discoveryTime[vertex] = time;
    cout<<"Visit :"<<vertex<<"\n";
    color[vertex] = GREY;
    for( int i = 0 ; i<nVertices ; i++){
        if(matrix[vertex][i] && color[i]==WHITE){
                parent[i]=vertex;
                dfs_visitM(i);
        }
    }
    color[vertex] = BLACK;
    time++;
    cout<<"Leave :"<<vertex<<endl;
    finishTime[vertex] = time;
    return;
}
void Graph::printStat(int type)
{
    if(type==BFS) {
        cout<<"BFS Stats\n";
        for (int i = 0; i < nVertices; i++) {
            cout << "NODE:" << i<<endl;
            cout << " ->Color :" << color[i] << " Parent :" << parent[i] << " Distance :" << dist[i] << endl;
        }
    }
    else if(type==DFS)
    {
        cout<<"DFS Stats\n";

        for (int i = 0; i < nVertices; i++) {
            cout << "NODE:" << i<<endl;
            cout << " ->Color :" << color[i] << " Parent :" << parent[i] << " DiscoveryTime :" << discoveryTime[i]
                 <<" FinishTime :"<<finishTime[i]<< endl;
        }
    }
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(matrix)delete [] matrix;
    if(color)delete [] color;
    if(parent)delete [] parent;
    if(dist)delete [] dist;
    if(discoveryTime)delete [] discoveryTime;
    if(finishTime)delete [] finishTime;
}
//******main function to test your code*************************
int main(void)
{
    int n;
    //Graph g;
    //printf("Enter number of vertices: ");
    //scanf("%d", &n);
    //g.setnVertices(n);
    Graph g(0);
    g.setnVertices(8);

    g.addEdge(0,1);
    g.addEdge(1,3);
    g.addEdge(3,2);
    g.addEdge(3,5);
    g.addEdge(1,5);

    g.addEdge(4,5);
    g.addEdge(6,5);
    g.addEdge(5,7);
    g.addEdge(7,1);


    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. RemoveEdge(u , v). 3.isEdge(u , v) 4.getDegree(u) 5. Print Graph \n"
                       "6. CheckCommonAdjacent(int u,int v) 7.getDist() 8.BFS 9.DFS 10. Exit.\n");

        int ch;
        cin>>ch;
        cout<<"Your Choice :"<<ch<<endl;
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int s=0,e=0;
            scanf("%d%d",&s,&e);
            g.removeEdge(s,e);
            g.printGraph();
        }
        else if(ch==3)
        {
            int u=0,v=0;
             cin>>u>>v;
            if(g.isEdge(u,v))cout<<"Edge Exists\n";
            else cout<<"Edge Not Found !\n";

        }
        else if(ch==4)
        {
            int u=0;
            cin>>u;
            cout<<"Degree of :"<<u<<" is:"<<g.getDegree(u)<<endl;
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u=0,v=0;
            cin>>u>>v;
            if(g.hasCommonAdjacent(u,v))cout<<"Common Vertex Exists\n";
            else cout<<"Doesnot Exist\n";
        }
        else if(ch==7)
        {
            int u=0,v=0;
             cin>>u>>v;
             cout<<"Distance From:"<<u<<"to"<<v<<"="<<g.getDist(u,v)<<endl;

        }
        else if(ch==8)
        {
            int u=0;
            cin>>u;
            g.bfs(u);
            g.printStat(BFS);
        }
        else if(ch==9)
        {
            g.dfs();
            g.printStat(DFS);
        }
        else if(ch==10)
        {
            break;
        }
    }

}
