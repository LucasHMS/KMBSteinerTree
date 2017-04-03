#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <set>

#include <iostream>
#include <fstream>
#include <string>

#include <climits>
#include <cstdlib>
#include <ctime>

#define INF INT_MAX

using namespace std;

typedef pair<int, int> iPair;
/* struct to store the shortest path from a vertex v to all other vertices
    of the graph and the cost of each path*/
typedef struct{
    int* path_weights;
    int* prev;
}dijkstra_return;

// Class of a an undirected graph with adjacency list
class Graph{
private:
    int V;    // No. of Vetices
    int T;    // No. of Terminals
    list<iPair>* adj;

public:
    Graph(int V, int T);

    ~Graph();

    void addEdge(int u, int v, int w);

    list<iPair> getEdges(int v);

    int get_n_vertices();

    int get_n_terminals();

    void printGraph();

    int isConnected();

    void DFS(int v, int* visited);

    void DFS_util(int u, int* visited);

    Graph* getMetricClousure();

    dijkstra_return* dijkstra_one_to_all(int org);

    Graph* primMST();

    void print_steiner();

    static dijkstra_return** returns;
    
    static int* terminals;
};

/* Global Funcs. */
void read_file(Graph** grafo, char* arquivo);
void findPath(int* parents, int org);
void delete_globals();

#endif
