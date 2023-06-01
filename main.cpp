#include <iostream>
#include "Graph.h"
#include "load_graphs.h"

int main() {
    Graph graph_toy(false);
    load_graphs l;
    graph_toy = l.load_toy("shipping.csv");
    /*Graph graph_real(true);
      int c;
    graph_real = l.load_real("graph3");*/
    Graph graph_medium(true);
    graph_medium = l.load_medium(500);
    vector<int> a = graph_toy.Backtracking();
    auto start = std::chrono::high_resolution_clock::now();
    vector<int> d = graph_medium.NearstNeighbor();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto dura = duration.count();
    vector<int> b = graph_toy.NearstNeighbor();
    double c = graph_toy.ratioBetweentwopaths(a,b);
    return 0;
}
