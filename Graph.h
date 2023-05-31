//
// Created by Utilizador on 5/12/2023.
//

#ifndef PROJETO2_GRAPH_H
#define PROJETO2_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>
#include <limits>

using namespace std;

struct Edge {
    int ori;
    int dest;   // Destination node
    double weight; // An integer weight
};

struct Node {
    list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    bool visited;// As the node been visited on a search?
    double distance;
    double longitude;
    double latitude;
};

class Graph {
    bool hasDir;        // false: undirected; true: directed

public:
    vector<Node> nodes;

    // Constructor: nr nodes and direction (default: undirected)
    Graph(int num, bool dir = false);

    Graph(bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);

    void addEdgewithoutNodes(int src, int dest, int weight = 1);
    // Depth-First Search: example implementation
    void dfs(int v);
    // Breadth-First Search: example implementation
    void bfs(int v);
    int maxbfs(int v);
    // ----- Functions to implement in this class -----
    int distance(int a, int b);
    int diameter();

    const Node& getNode(int index) const {
        return nodes[index];
    }

    int getNumNodes() const {
        return nodes.size();
    }

    void BacktrackingUtil(int current, int count, double cost, double& minCost, std::vector<int>& path);
    std::vector<int> Backtracking();
};


#endif //PROJETO2_GRAPH_H
