using namespace std;
#include <set>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <map>


class Graph
{
	int nodes; 
	int edges[8][8] = {0};

public:
	Graph(int node); 
	void addEdge(char node1, char node2, int weight);
	void printNodes();
	void distancesToAllNodes(char startNode);
	void shortestPath(char src);

};

Graph::Graph(int nodes)
{
	this->nodes = nodes;
}

void Graph::addEdge(char node1, char node2, int weight)
{
	int node1Index = (node1 - 'A');
	int node2Index = (node2 - 'A');

	edges[node1Index][node2Index] = weight;

}

void Graph::printNodes()
{
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			if (j == i)
				cout << "# ";
			else
			cout << edges[i][j] << " " ;
			
		}
		cout << endl;
	}
}

void Graph::distancesToAllNodes(char startNode)
{
	int nodeIndex = (startNode - 'A');

	for (int j = 0; j < nodes; j++) {
		if (edges[nodeIndex][j] != 0) {
			char ch = ('A' + j);
			cout << "Distance from " << startNode << " to " << ch << ": " << edges[nodeIndex][j] << " " << endl;
		}
	}
}

void printPath(int parent[], int j)
{
	// Base Case : If j is source
	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);

	printf("%d ", j);
}

void printSolution(int dist[], int n, int parent[])
{
	int src = 0;
	printf("Vertex\t  Distance\tPath");
	for (int i = 1; i < 8; i++)
	{
		printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
		printPath(parent, i);
	}
}

int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < 8; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// Prints shortest paths from src to all other vertices
void Graph::shortestPath(char node)
{
	int src = (node - 'A');
	int dist[8];  // The output array. dist[i] will hold
				  // the shortest distance from src to i

				  // sptSet[i] will true if vertex i is included / in shortest
				  // path tree or shortest distance from src to i is finalized
	bool sptSet[8];

	// Parent array to store shortest path tree
	int parent[8];

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < 8; i++)
	{
		parent[0] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < 8 - 1; count++)
	{
		// Pick the minimum distance vertex from the set of
		// vertices not yet processed. u is always equal to src
		// in first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < 8; v++)

			// Update dist[v] only if is not in sptSet, there is
			// an edge from u to v, and total weight of path from
			// src to v through u is smaller than current value of
			// dist[v]
			if (!sptSet[v] && edges[u][v] &&
				dist[u] + edges[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + edges[u][v];
			}
	}
	printSolution(dist, 8, parent);
}



int main()
{
	Graph g(8);

	g.addEdge('A', 'E', 4);
	g.addEdge('A', 'D', 8);
	g.addEdge('A', 'B', 6);
	g.addEdge('B', 'E', 2);
	g.addEdge('B', 'C', 6);
	g.addEdge('B', 'H', 1);
	g.addEdge('B', 'F', 4);
	g.addEdge('C', 'G', 3);
	g.addEdge('D', 'G', 7);
	g.addEdge('F', 'G', 5);
	g.addEdge('F', 'H', 3);



	g.printNodes();

	g.shortestPath('A');


	int wait = 0;
	cin >> wait;
	return 0;
}