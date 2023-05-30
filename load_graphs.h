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
    Graph load_toy(string filename);
    Graph load_real(string graph);
    Graph load_medium(int num);
};


#endif //PROJETO2_LOAD_GRAPHS_H
