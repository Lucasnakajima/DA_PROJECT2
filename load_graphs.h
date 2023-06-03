//
// Created by Utilizador on 5/12/2023.
//

#ifndef PROJETO2_LOAD_GRAPHS_H
#define PROJETO2_LOAD_GRAPHS_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Graph.h"

using namespace std;

class load_graphs {
public:
    /**
     * @brief Loads station and connection data from a CSV file into a graph object.
     * @param filename The name of the CSV file to load
     * @return Graph The loaded graph object
     */
    Graph load_toy(string filename);

    /**
     * @brief Loads real-world station and connection data from CSV files into a graph object.
     * @param graph The name of the graph directory containing the CSV files
     * @return Graph The loaded graph object
     */
    Graph load_real(string graph);


    /**
     * @brief Loads medium-sized graph data from a CSV file into a graph object.
     * @param num The number of nodes in the graph
     * @return Graph The loaded graph object
     */
    Graph load_medium(int num);
};


#endif //PROJETO2_LOAD_GRAPHS_H
