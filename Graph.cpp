//
// Created by Utilizador on 5/12/2023.
//

#include "Graph.h"

Graph::Graph(int num, bool dir) : hasDir(dir){
}

Graph::Graph(bool dir) : hasDir(dir){
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<0 || dest<0) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

void Graph::addEdgewithoutNodes(int src, int dest, int weight) {
    if(nodes.empty()){

    }
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    // show node order
    // cout << v << " ";
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Breadth-First Search: example implementation
void Graph::bfs(int v) {
    for (int i = 0; i < nodes.size(); i++){ nodes[i].visited = false; nodes[i].distance = -1;}
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        // show node order
        //cout << u << " ";
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance+1;
            }
        }
    }
}

int Graph::maxbfs(int v) {
    int max = 0;
    for (int i = 0; i < nodes.size(); i++){ nodes[i].visited = false; nodes[i].distance = -1;}
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        // show node order
        //cout << u << " ";
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance+1;
                if(nodes[w].distance == -1){
                    return -1;
                }
                else if(nodes[w].distance > max) max = nodes[w].distance;
            }
        }
    }
    return max;
}


int Graph::distance(int a, int b) {
    bfs(a);
    return nodes[b].distance;
}

int Graph::diameter() {
    int max = 0;
    for(int i = 0; i<nodes.size(); i++){
        if(!nodes[i].visited && i>1) return -1;
        int res = maxbfs(i);
        if(res == -1) return -1;
        else if(res> max) max = res;
    }
    return max;
}

std::vector<int> Graph::Backtracking() {
    int numNodes = getNumNodes();

    for (int i = 0; i < nodes.size(); i++){ nodes[i].visited = false; nodes[i].distance = -1;}
    nodes[0].visited = true;

    std::vector<int> path(numNodes);

    double minCost = std::numeric_limits<double>::max();
    BacktrackingUtil(0, 0, 0, minCost, path);

    return path;
}

void Graph::BacktrackingUtil(int current, int count, double cost, double& minCost, std::vector<int>& path) {
    nodes[current].visited = true;
    path[count] = current;

    if (count == getNumNodes() - 1) {
        // Check if there is an edge back to the starting node
        if (nodes[current].adj.front().dest == 0) {
            double totalCost = cost + nodes[current].adj.front().weight;
            if (totalCost < minCost) {
                minCost = totalCost;
            }
        }
        return;
    }

    for (const Edge& edge : nodes[current].adj) {
        if (!nodes[edge.dest].visited && edge.dest!=0) {
            BacktrackingUtil(edge.dest, count + 1, cost + edge.weight, minCost, path);
        }
    }

    nodes[current].visited = false;
}
