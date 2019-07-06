#include<cstdio>
#include<cstdlib>
#include <iostream>
#include "Queue.h"
#include "Arraylist.h"
#define BFS 4
#define DFS 5
#define WHITE 1
#define GREY 2
#define BLACK 3
int time=0;
using namespace std;

class Graph
{
	int nVertices, nEdges ;
	bool directed ;
    int *color , *parent , *dist ,*discoveryTime, *finishTime;

    ArrayList  * adjList =0;
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
    void dfs(); //will run dfs in the graph
    void printStat(int type);

    void dfs_visit(int vertex);
};


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
Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    directed = dir ; //set direction of the graph
    color =0; //define other variables to be initialized
    parent=0;
    dist=0;
    discoveryTime=0;
    finishTime=0;

    //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0)
    {

        delete[] adjList ;
        delete[] parent;
        delete[] color;
        delete[] dist;
        delete[] discoveryTime;
        delete[] finishTime;
    } //delete previous list
	adjList = new ArrayList[nVertices] ;
    color = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];
    discoveryTime = new int[nVertices];
    finishTime = new int[nVertices];


}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges-- ;
    adjList[u].removeItem(v) ;
    if(!directed) adjList[v].removeItem(u) ;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || u>=nVertices || v>=nVertices) return 0; //vertex out of range

    if(!directed)return adjList[u].searchItem(v) != NULL_VALUE || adjList[v].searchItem(u) != NULL_VALUE;
    else { return adjList[u].searchItem(v)!=NULL_VALUE; }
}
int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices ) return 0; //vertex out of range
    int degree=adjList[u].getLength();
    bool isLoop=adjList[u].searchItem(u)!=NULL_VALUE;
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
         if(adjList[i].searchItem(u)!=NULL_VALUE)degree++;
        }
        if(isLoop)return degree+1;
        else return degree;
    }
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    int tU=0,tV=0,i=0;
    for (i = 0; i <nVertices ; i++) {
        if(adjList[u].searchItem(i)!=NULL_VALUE)tU=1;
        if(adjList[v].searchItem(i)!=NULL_VALUE)tV=1;

        if(tU & tV) return true;
    }
    if(i==nVertices) return false;

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
        int len=adjList[visited].getLength();
        for(int i=0;i<len;i++)
        {
            int neighbourOfV=adjList[visited].getItem(i);
            if(color[neighbourOfV]==WHITE )
            {
                q.enqueue(neighbourOfV);
                color[neighbourOfV]=GREY;
                dist[neighbourOfV]=dist[visited]+1;
                parent[neighbourOfV]=visited;
            }
        }

    }
    //cout<<"|\n";
}
void Graph::dfs_visit(int vertex){
    if(color[vertex] == BLACK){ return; }
    time++;
    discoveryTime[vertex] = time;
    color[vertex] = GREY;
    cout<<"Visit :"<<vertex<<"\n";

    int len=adjList[vertex].getLength();
    for( int i = 0 ; i<len ; i++){
        int u = adjList[vertex].getItem(i);

        if(color[u]== WHITE){
            parent[u]=vertex;
            dfs_visit(u);
        }
    }
    color[vertex] = BLACK;
    cout<<"Leave :"<<vertex<<endl;
    time++;
    finishTime[vertex] = time;
    return;
}

void Graph::dfs()
{
    //write this function

    time = 0;
    for(int i = 0; i<nVertices ; i++)
    {
        color[i] = WHITE;
        parent[i]=-1;
    }
    for(int i = 0; i<nVertices ; i++){
        if(color[i] == WHITE){
            dfs_visit(i);
    }
    }
    cout<<"\n";
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

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
     if(adjList)delete [] adjList;
     if(color)delete [] color;
     if(parent)delete [] parent;
     if(dist)delete [] dist;
     if(discoveryTime)delete [] discoveryTime;
     if(finishTime)delete [] finishTime;
}


//**********************Graph class ends here******************************


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
   // g.addEdge(1,5);

    g.addEdge(4,5);
    g.addEdge(6,5);
    g.addEdge(5,7);
    //g.addEdge(7,1);



    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. RemoveEdge(u , v). 3.isEdge(u , v) 4.getDegree(u) 5. Print Graph \n"
                       "6. CheckCommonAdjacent(int u,int v) 7.getDist(int u,int v) 8.BFS(int src) 9.DFS() 10. Exit.\n");

        int ch;
        cin>>ch;
        cout<<"Your Choice :"<<ch<<endl;
        if(ch==1)
        {
            int u, v;
            cin>>u>>v;
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int s=0,e=0;
            cin>>s>>e;
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
            //g.printStat(BFS);

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
