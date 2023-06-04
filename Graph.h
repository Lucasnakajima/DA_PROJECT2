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

/**
 * @brief Structure representing a cluster of nodes.
 */
struct Cluster {
    vector<int> nodes; ///< Indices of nodes in the cluster
};

/**
 * @brief Structure representing an edge between nodes in the graph.
 */
struct Edge {
    int ori; ///< Origin node
    int dest;   ///< Destination node
    double weight;  ///< Weight of the edge
};

/**
 * @brief Comparator for comparing edges based on weight in ascending order.
 */
struct EdgeComparator {

    /**
     * @brief Comparison operator for edges.
     * @param edge1 The first edge.
     * @param edge2 The second edge.
     * @return True if edge1 has a greater weight than edge2, false otherwise.
     */
    bool operator()(const Edge& edge1, const Edge& edge2) {
        return edge1.weight > edge2.weight;  // Compare edges based on weight in ascending order
    }
};


/**
 * @brief Structure representing a node in the graph.
 */
struct Node {
    list<Edge> adj; ///< The list of outgoing edges (to adjacent nodes)
    bool visited; ///< Flag indicating if the node has been visited during a search
    double distance; ///< Distance from the source node
    double longitude; ///< Longitude coordinate of the node
    double latitude; ///< Latitude coordinate of the node
};

/**
 * @brief Class representing a graph.
 */
class Graph {
    bool hasDir;    ///< Flag indicating if the graph is directed (true) or undirected (false)

public:
    vector<Node> nodes; ///< Vector of nodes in the graph

    /**
     * @brief Performs hierarchical agglomerative clustering to partition the nodes into k clusters.
     * @param k The number of clusters.
     * @return vector<Cluster> The clusters obtained from the clustering.
     */
    vector<Cluster> clusterNodes(int k);

    /**
    * @brief Constructs a graph with a specified number of nodes and directionality.
    * @param num The number of nodes in the graph.
    * @param dir The directionality of the graph (default: undirected).
    */
    Graph(int num, bool dir = false);

    /**
     * @brief Constructs a graph with optional directionality.
     * @param dir The directionality of the graph (default: undirected).
     */
    Graph(bool dir = false);

    /**
     * @brief Adds an edge from source to destination with a certain weight
     *
     * If the graph is undirected, the edge is also added from destination to source
     *
     * @param src Source node
     * @param dest Destination node
     * @param weight Weight of the edge
     * Time Complexity: O(1)
     */
    void addEdge(int src, int dest, int weight);

    /**
     * @brief Adds an edge from source to destination with a certain weight
     *
     * This function doesn't check for existence of nodes in the graph
     *
     * @param src Source node
     * @param dest Destination node
     * @param weight Weight of the edge
     * Time Complexity: O(1)
     */
    void addEdgewithoutNodes(int src, int dest, int weight = 1);

    /**
     * @brief Performs depth-first search on the graph starting from node 'v'
     *
     * @param v Node to start the search from
     * Time Complexity: O(V+E)
     */
    void dfs(int v);

    /**
     * @brief Recursive function for Depth-first search to find all nodes in the same connected component as node 'v'
     *
     * @param v Node to start the search from
     * @param visited Vector to keep track of visited nodes
     * @param component Vector to keep track of nodes in the same connected component
     * Time Complexity: O(V+E)
     */
    void dfs_connected(int v, std::vector<bool>& visited, std::vector<int>& component);

    /**
     * @brief Performs breadth-first search on the graph starting from node 'v'
     *
     * Also, calculates the distance of all nodes from node 'v' in terms of the number of edges
     *
     * @param v Node to start the search from
     * Time Complexity: O(V+E)
     */
    void bfs(int v);

    /**
     * @brief Performs a modified breadth-first search from the given node, tracking the maximum distance achieved
     *
     * @param v The node to start the search from
     * @return int Maximum distance achieved during the search, or -1 if any node was unreachable
     * Time Complexity: O(V+E)
     */
    int maxbfs(int v);

    /**
     * @brief Computes the shortest distance between two nodes in the graph using Breadth-First Search (BFS)
     *
     * @param a The starting node
     * @param b The ending node
     * @return int The shortest distance between the nodes
     * Time Complexity: O(V+E)
     */
    int distance(int a, int b);

    /**
     * @brief Computes the diameter of the graph, which is the longest shortest-path distance among all pairs of nodes
     *
     * @return int The diameter of the graph, or -1 if the graph is not connected
     * Time Complexity: O(V*(V+E))
     */
    int diameter();

    /**
     * @brief Finds connected components in the graph
     *
     * @return vector<std::vector<int>> Vector of vectors, each containing nodes belonging to one connected component
     * Time Complexity: O(V+E)
     */
    std::vector<std::vector<int>> findConnectedComponents();


    /**
     * @brief Fetches a node object given its index
     *
     * @param index The index of the desired node
     * @return const Node& The requested node
     * Time Complexity: O(1)
     */
    const Node& getNode(int index) const ;

    /**
     * @brief Computes the Haversine distance between two nodes, which is the shortest distance over the earth's surface
     *
     * @param node1 The first node
     * @param node2 The second node
     * @return double The Haversine distance between the nodes
     * Time Complexity: O(1)
     */
    double Haversine(const Node& node1, const Node& node2);

    /**
     * @brief Fetches the number of nodes in the graph
     *
     * @return int The number of nodes in the graph
     * Time Complexity: O(1)
     */
    int getNumNodes() const;


    /**
     * @brief Finds the representative node of the set that the given node belongs to.
     * @param node The node to find the representative for.
     * @param parent The parent array representing the disjoint sets.
     * @return int The representative node of the set.
     */
    int findSet(int node, vector<int>& parent);

    /**
     * @brief Merges two disjoint sets into a single set.
     * @param set1 The representative node of the first set.
     * @param set2 The representative node of the second set.
     * @param parent The parent array representing the disjoint sets.
     */
    void unionSets(int set1, int set2, vector<int>& parent);

    /**
     * @brief Finds the minimum spanning tree of the graph using Prim's algorithm.
     * @return vector<Edge> The edges of the minimum spanning tree.
     */
    std::vector<Edge> minimumSpanningTree();

    /**
     * @brief Computes an approximate solution to the Traveling Salesman Problem (TSP).
     * @return vector<int> The nodes visited in the approximate Hamiltonian tour.
     * Time Complexity: O(n^2 log n), where n is the number of nodes in the graph.
     */
    std::vector<int> TSPApproximation();

    /**
     * @brief Duplicates the edges of the minimum spanning tree.
     * @param edges The edges of the minimum spanning tree.
     * @return vector<Edge> The duplicated edges.
     */
    std::vector<Edge> duplicateEdges(const std::vector<Edge>& edges);

    /**
     * @brief Removes duplicate nodes from the Eulerian tour to obtain a Hamiltonian tour.
     * @param eulerianTour The Eulerian tour containing duplicate nodes.
     * @return vector<int> The nodes visited in the Hamiltonian tour.
     */
    std::vector<int> removeDuplicateNodes(const std::vector<int>& eulerianTour);


    /**
     * @brief Finds an Eulerian tour in the multigraph formed by duplicating the edges of the minimum spanning tree.
     * @param edges The duplicated edges.
     * @return vector<int> The nodes visited in the Eulerian tour.
     */
    std::vector<int> findEulerianTour(const std::vector<Edge>& edges);

    /**
     * @brief Connects two paths by finding the minimum-weight edge that connects them.
     * @param path1 The first path.
     * @param path2 The second path.
     * @return vector<int> The connected path.
     */
    std::vector<int> connectPaths(std::vector<int>& path1, std::vector<int>& path2);

    /**
     * @brief Finds the approximate optimal path through the graph using the Nearest Neighbor algorithm.
     * @param cluster The cluster of nodes to consider.
     * @param returnToStart Whether to return to the start node or not.
     * @return vector<int> The approximate optimal path through the graph.
     * Time Complexity: O(k^2 * n^3), where k is the number of clusters and n is the average size of each cluster.
     */
    std::vector<int> NearestNeighbor(const vector<int>& cluster, bool returnToStart);

    /**
     * @brief Performs the Divide and Conquer algorithm to find the optimal path through the clustered graph.
     * @return vector<int> The optimal path through the clustered graph.
     */
    std::vector<int> DivideConquerClusteredNN();

    /**
     * @brief Finds the minimum spanning tree for a disconnected component of the graph.
     * @param startNode The starting node of the component.
     * @param visited The visited array to keep track of visited nodes.
     * @return vector<Edge> The edges of the minimum spanning tree for the component.
     */
    std::vector<Edge> minimumSpanningTreeForComponent(int startNode, std::vector<bool>& visited);

        /**
     * @brief Finds an Eulerian tour in the multigraph formed by duplicating the edges of the minimum spanning tree for a disconnected component.
     * @param component The component of nodes to find the Eulerian tour for.
     * @param edgeMap The multimap of edges for each node.
     * @return vector<int> The nodes visited in the Eulerian tour for the component.
     */
    std::vector<int> findEulerianTourForComponent(const std::vector<int>& component, std::multimap<int, Edge>& edgeMap);

    /**
     * @brief Utility function for backtracking to explore all possible paths through the graph.
     * @param current The current node being visited.
     * @param count The number of nodes visited so far.
     * @param cost The cost of the current path.
     * @param minCost The minimum cost found so far.
     * @param path The current path being explored.
     */
    void BacktrackingUtil(int current, int count, double cost, double& minCost, std::vector<int>& path);

    /**
     * @brief Performs backtracking to find the optimal path through the graph.
     * @return vector<int> The optimal path through the graph.
     * Time Complexity: O(n!)
     */
    std::vector<int> Backtracking();

    /**
     * @brief Computes the ratio of the distances of two paths in the graph
     *
     * This function assumes the first node in the vectors is the starting node, and that both paths are closed loops
     * (i.e., they start and end at the same node).
     *
     * @param opt The first path
     * @param test The second path
     * @return double The ratio of the total distance of the 'test' path to the 'opt' path, or -1 if the paths are not the same size or don't start at the same node
     * Time Complexity: O(n), where n is the number of nodes in the paths
     */
    double ratioBetweentwopaths(vector<int>opt, vector<int>test);

    double pathWeight(vector<int> opt);
};


#endif //PROJETO2_GRAPH_H
