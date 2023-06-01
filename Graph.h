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
#include <chrono>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

struct Edge {
    int ori;
    int dest;   // Destination node
    double weight; // An integer weight
};
struct EdgeComparator {
    bool operator()(const Edge& edge1, const Edge& edge2) {
        return edge1.weight > edge2.weight;  // Compare edges based on weight in ascending order
    }
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
    void dfs_connected(int v, std::vector<bool>& visited, std::vector<int>& component);
    // Breadth-First Search: example implementation
    void bfs(int v);
    int maxbfs(int v);
    // ----- Functions to implement in this class -----
    int distance(int a, int b);
    int diameter();

    std::vector<std::vector<int>> findConnectedComponents();

    const Node& getNode(int index) const ;
    double Haversine(const Node& node1, const Node& node2);

    int getNumNodes() const;

    std::vector<Edge> minimumSpanningTree();

    std::vector<int> TSPApproximation();
    std::vector<Edge> duplicateEdges(const std::vector<Edge>& edges);
    std::vector<int> removeDuplicateNodes(const std::vector<int>& eulerianTour);
    std::vector<int> findEulerianTour(const std::vector<Edge>& edges);

    std::vector<Edge> minimumSpanningTreeForComponent(int startNode, std::vector<bool>& visited);
    std::vector<int> findEulerianTourForComponent(const std::vector<int>& component, std::multimap<int, Edge>& edgeMap);

    void BacktrackingUtil(int current, int count, double cost, double& minCost, std::vector<int>& path);
    std::vector<int> Backtracking();
    std::vector<int> NearestNeighbor();
    double ratioBetweentwopaths(vector<int>opt, vector<int>test);
};


#endif //PROJETO2_GRAPH_H
