using namespace std;
#include <set>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <map>

int const GRAPH_SIZE = 8;
class Graph
{
	int nodes;
	int edges[GRAPH_SIZE][GRAPH_SIZE] = { 0 };
	void printPath(int parent[], int j);
	void printDistances(int distances[], int start);
public:
	Graph(int node);
	void addEdge(char node1, char node2, int weight);
	void printNodes();
	void distancesToAllNodes(char startNode);
	void distanceToEveryNode(char start);
	void distanceBetweenTwoNodes(char start, char end);
	char getLetter(int i);
	char getInt(char i);

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
	edges[node2Index][node1Index] = weight;

}

void Graph::printNodes()
{
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			if (j == i)
				cout << "# ";
			else
				cout << edges[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::distancesToAllNodes(char startNode)
{
	int nodeIndex = (startNode - 'A');

	for (int j = 0; j < nodes; j++) {
		if (edges[nodeIndex][j] != 0) {
			char ch = getLetter(j);
			cout << "Distance from " << startNode << " to " << ch << ": " << edges[nodeIndex][j] << " " << endl;
		}
	}
}

void Graph::printPath(int parent[], int j)
{
	// Base Case : If j is source
	if (parent[j] == -1) {
		return;
	}
	printPath(parent, parent[j]);
	char jToChar = getLetter(j);
	cout << jToChar;
}

//http://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/

void Graph::printDistances(int distances[], int start)
{
	cout << "Vertex \tDistance\n";
	for (int i = 0; i < 8; i++) {
		if (i != start) {
			char iToLetter = getLetter(i);
			cout << "   " << iToLetter << " \t   " << distances[i] << "\n";
		}
	}
}

int minDistance(int distances[], bool sptSet[])
{
	int min = INT_MAX, min_index;

	for (int i = 0; i < 8; i++) {
		if (sptSet[i] == false && distances[i] <= min) {
			min = distances[i];
			min_index = i;
		}
	}
	return min_index;
}

// Prints shortest paths from src to all other 
void Graph::distanceToEveryNode(char start)
{
	int nodeInt = start - 'A';
	cout << "Shortest path from " << start << " to all nodes\n";
	int distances[GRAPH_SIZE];
	bool processed[GRAPH_SIZE];

	for (int i = 0; i < GRAPH_SIZE; i++)
		distances[i] = INT_MAX, processed[i] = false;

	distances[nodeInt] = 0;

	for (int i = 0; i < GRAPH_SIZE - 1; i++)
	{
		int minDist = minDistance(distances, processed);
		processed[minDist] = true;

		for (int j = 0; j < GRAPH_SIZE; j++) {
			
			if (!processed[j] && edges[minDist][j] && distances[minDist] != INT_MAX
				&& distances[minDist] + edges[minDist][j] < distances[j]) {
				distances[j] = distances[minDist] + edges[minDist][j];
			}
		}
	}
	printDistances(distances, start);
}

void Graph::distanceBetweenTwoNodes(char start, char end)
{
	int startNode = getInt(start);
	int endNode = getInt(end);

	int distances[8];
	bool processed[8];

	for (int i = 0; i < 8; i++)
		distances[i] = INT_MAX, processed[i] = false;

	distances[startNode] = 0;

	for (int i = 0; i < 8 - 1; i++)
	{
		int minDist = minDistance(distances, processed);
		processed[minDist] = true;

		for (int j = 0; j < 8; j++) {
			if (!processed[j] && edges[minDist][j] && distances[minDist] != INT_MAX
				&& distances[minDist] + edges[minDist][j] < distances[j]) {
				distances[j] = distances[minDist] + edges[minDist][j];
			}
		}
	}

	cout << "Distance from " << start << " -> " << end << " is " << distances[endNode] << "\n";
}

char Graph::getLetter(int i)
{
	return ('A' + i);
}

char Graph::getInt(char i)
{
	return (i - 'A');
}


int main()
{
	Graph g(GRAPH_SIZE);

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

	g.distanceToEveryNode('B');

	g.distanceBetweenTwoNodes('A', 'G');

	int wait = 0;
	cin >> wait;
	return 0;
}