#include <iostream>
#include "Graph.h"
#include "load_graphs.h"

int main() {
    Graph graph_toy(false);
    load_graphs l;
    graph_toy = l.load_toy("stadiums.csv");
    /*Graph graph_real(true);
      int c;
    graph_real = l.load_real("graph3");*/
    Graph graph_medium(true);
    graph_medium = l.load_medium(25);

    vector<int> a = graph_toy.Backtracking();

    return 0;
}
