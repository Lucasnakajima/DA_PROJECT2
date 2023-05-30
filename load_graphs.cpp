//
// Created by Utilizador on 5/12/2023.
//

#include "load_graphs.h"
#include "Graph.h"


Graph load_graphs::load_toy(string filename) {
    Graph graph(false);
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << filename << std::endl;
        return graph;
    }

    std::string header;
    std::getline(file, header);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        // Read the source node
        std::getline(ss, token, ',');
        int source = std::stoi(token);

        // Read the destination node
        std::getline(ss, token, ',');
        int destination = std::stoi(token);

        // Read the distance
        std::getline(ss, token, ',');
        double distance = std::stod(token);
        Edge e;
        e.ori = source;
        e.dest = destination;
        e.weight = distance;

        if(graph.nodes.empty()){

            list<Edge> li;
            li.push_back(e);
            Node no;
            no.visited = false;
            no.distance = 0;
            no.adj = li;
            graph.nodes.push_back(no);
        }
        else if(graph.nodes.size()<source+1){

            list<Edge> li;
            li.push_back(e);
            Node no;
            no.visited = false;
            no.distance = 0;
            no.adj = li;
            graph.nodes.push_back(no);
        }
        else{
            graph.nodes[source].adj.push_back(e);
        }
        e.dest=source;
        e.ori = destination;
        if(graph.nodes.size()<destination+1){
            graph.nodes.resize(destination+1);
        }
        graph.nodes[destination].adj.push_back(e);

    }

    file.close();
    return graph;
}

Graph load_graphs::load_real(string graph) {
    Graph Graph(true);
    string filename_edge = graph + "/edges.csv";
    string filename_node = graph + "/nodes.csv";
    std::ifstream file(filename_node);
    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << filename_node << std::endl;
        return Graph;
    }

    std::string header;
    std::getline(file, header);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        // Read the source node
        std::getline(ss, token, ',');
        int id = std::stoi(token);

        // Read the destination node
        std::getline(ss, token, ',');
        double longitude = std::stod(token);

        // Read the distance
        std::getline(ss, token, ',');
        double latitude= std::stod(token);
        Node node;
        node.visited = false;
        node.distance = 0;
        node.latitude = latitude;
        node.longitude = longitude;
        Graph.nodes.push_back(node);

    }
    file.close();

    std::ifstream file_e(filename_edge);
    if (!file_e.is_open()) {
        std::cout << "Failed to open the file: " << filename_node << std::endl;
        return Graph;
    }
    std::getline(file_e, header);

    while (std::getline(file_e, line)) {
        std::stringstream ss(line);
        std::string token;

        // Read the source node
        std::getline(ss, token, ',');
        int origem = std::stoi(token);

        // Read the destination node
        std::getline(ss, token, ',');
        int dest = std::stoi(token);

        // Read the distance
        std::getline(ss, token, ',');
        double distance= std::stod(token);
        Edge forward, backwards;
        forward.ori = origem;
        forward.dest = dest;
        forward.weight = distance;

        backwards.ori=dest;
        backwards.dest=origem;
        backwards.weight=distance;

        Graph.nodes[origem].adj.push_back(forward);
        Graph.nodes[dest].adj.push_back(backwards);

    }
    file_e.close();

    return Graph;
}

Graph load_graphs::load_medium(int num) {
    Graph graph(false);
    string filename = "edges_"+ to_string(num) +".csv";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << filename << std::endl;
        return graph;
    }
    graph.nodes.resize(num);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        // Read the source node
        std::getline(ss, token, ',');
        int source = std::stoi(token);

        // Read the destination node
        std::getline(ss, token, ',');
        int destination = std::stoi(token);

        // Read the distance
        std::getline(ss, token, ',');
        double distance = std::stod(token);
        Edge e;
        e.ori = source;
        e.dest = destination;
        e.weight = distance;
        graph.nodes[source].adj.push_back(e);
        e.dest=source;
        e.ori = destination;
        graph.nodes[destination].adj.push_back(e);

    }

    file.close();
    return graph;
}