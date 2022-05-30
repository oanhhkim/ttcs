#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>

#define MAXN 99 // maximum number of nodes in graph
#define INF 2147483646
using namespace std;

// represents the capacities of the edges
int capacity[MAXN][MAXN];
// shows how much flow has passed through an edge
int flowPassed[MAXN][MAXN];
// represents the graph and it may contain negative edges
vector <int> graph[MAXN];
// show the path builed by BFS in grarph
int parList[MAXN];
// shows the maximum flow to a node in the path built by the BFS
int currentPathC[MAXN];
// show  a node which is visited  or not
bool visited[MAXN];


// Find path builed by BFS and path flow in residual network
int bfs(int sNode, int eNode){
	
	memset(parList, -2, sizeof(parList));
	memset(visited, false, sizeof(visited));
	memset(currentPathC, 0, sizeof(currentPathC));
	queue<int> q; //declar queue
	q.push(sNode);
	visited[sNode]  = true; // sNode is visited
	parList[sNode] = -1; // initialize parlist's source node
	currentPathC[sNode] = INF;//initialize currentpath's source node
   
	while(!q.empty()){
		int currNode = q.front();
		q.pop();
		for(int i = 0; i<graph[currNode].size(); i++){
			int to  = graph[currNode][i];
			if(visited[to] == false){
				if(capacity[currNode][to] - flowPassed[currNode][to] > 0){
					visited[to] = true;
					parList[to] = currNode;
					currentPathC[to] =  min(currentPathC[currNode],
										capacity[currNode][to] - flowPassed[currNode][to]);
					if(to == eNode){
						return currentPathC[eNode];
					}
					q.push(to);
				}
			}
		}	
		
   }
   return 0;
}

// Edmonds-Karp 
int edmondsKarp(int sNode, int eNode){
	int maxFlow = 0; // There is no flow initially
	while(true){
		int pathFlow = bfs(sNode, eNode);
		if(pathFlow == 0){
			break;//not exists path flow build by BFS in residual network
		}
		
		// Add path flow to overall flow
		maxFlow += pathFlow;
		// update residual capacities of the edges and reverse edges along the path
		int currNode = eNode;
		while(currNode != sNode)
		{	
			int prevNode = parList[currNode];
				flowPassed[prevNode][currNode] += pathFlow;
				flowPassed[currNode][prevNode] -= pathFlow;
				currNode = prevNode;
		}
	
		
		
	}
	return maxFlow;
}

int main(){
	int nNode, nEdge;
	cin>>nNode>>nEdge; //Enter the number of nodes and edges
	
	int begin, last;
	cin>>begin>>last; //Enter the  beginNode and lastNode
	
	for(int e = 0; e< nEdge; e++){
		int from,to,cap;
		cin>>from>>to>>cap; 		//Enter the start and end vertex along with capacity for each edge
		capacity[from][to] = cap;
		graph[from].push_back(to);
		graph[to].push_back(from);
		
	}
	int maxFlow = edmondsKarp(begin, last);
	cout<<maxFlow<<endl;		//Max Flow 
	
}
