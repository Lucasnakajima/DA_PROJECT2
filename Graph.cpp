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

std::vector<std::vector<int>> Graph::findConnectedComponents() {
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(nodes.size(), false);

    for (int i = 0; i < nodes.size(); ++i) {
        if (!visited[i]) {
            std::vector<int> component;
            dfs_connected(i, visited, component);
            components.push_back(component);
        }
    }

    return components;
}

void Graph::dfs_connected(int v, std::vector<bool>& visited, std::vector<int>& component) {
    visited[v] = true;
    component.push_back(v);

    for (const Edge& edge : nodes[v].adj) {
        int neighbor = edge.dest;
        if (!visited[neighbor]) {
            dfs_connected(neighbor, visited, component);
        }
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

const Node& Graph::getNode(int index) const {
    return nodes[index];
}

int Graph::getNumNodes() const {
    return nodes.size();
}

double Graph::Haversine(const Node& node1, const Node& node2){
    double lat1 = node1.latitude;
    double lon1 = node1.longitude;
    double lat2 = node2.latitude;
    double lon2 = node2.longitude;

    // Convert degrees to radians
    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;

    // Calculate the distance using the Haversine formula
    double dlon = lon2Rad - lon1Rad;
    double dlat = lat2Rad - lat1Rad;
    double a = pow(sin(dlat / 2), 2) + cos(lat1Rad) * cos(lat2Rad) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = c * 6371;  // Earth's radius in kilometers

    return distance;
}


double Graph::ratioBetweentwopaths(vector<int> opt, vector<int> test) {
    if(opt[0]!=test[0] && opt.size() != test.size()){
        return -1;
    }
    int start = opt[0];
    double distance_opt=0;
    double distance_test=0;
    bool is_h = true;
    int current = start;
    for(int i=1;i<opt.size();i++){
        is_h = true;
        for(auto e : nodes[current].adj){
            if(e.dest==opt[i]){
                distance_opt = distance_opt + e.weight;
                is_h = false;
                break;
            }
        }
        if(!is_h){
            current = opt[i];
        }
        else {
            distance_test = distance_test + Haversine(nodes[current], nodes[opt[i]]);
            current = opt[i];
        }
    }
    for(auto e : nodes[current].adj){
        if(e.dest==start){
            distance_opt = distance_opt + e.weight;
            break;
        }
    }

    current = start;
    is_h = true;
    for(int i=1;i<test.size();i++){
        is_h = true;
        for(auto e : nodes[current].adj){
            if(e.dest==opt[i]){
                distance_test = distance_test + e.weight;
                is_h = false;
                break;
            }
        }
        if(!is_h){
            current = test[i];
        }
        else {
            distance_test = distance_test + Haversine(nodes[current], nodes[test[i]]);
            current = test[i];
        }
    }
    for(auto e : nodes[current].adj){
        if(e.dest==start){
            distance_test = distance_test + e.weight;
            break;
        }
    }
    return distance_test/distance_opt;
}

//O(n!)
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


//O(k^2 * n^3), where k is the number of clusters and n is the average size of each cluster
std::vector<int> Graph::NearestNeighbor(const vector<int>& cluster, bool returnToStart) {
    int numNodes = cluster.size();
    std::vector<int> path(numNodes + (returnToStart ? 1 : 0));
    std::vector<bool> visited(getNumNodes(), false);
    int currentNode = cluster[0]; // Start from the first node in the cluster
    visited[currentNode] = true;
    path[0] = currentNode;

    for (int i = 1; i < numNodes; ++i) {
        int nearestNeighbor = -1;
        double minDistance = std::numeric_limits<double>::max();

        for (const auto& edge : nodes[currentNode].adj) {
            int neighbor = edge.dest;
            // We only consider neighbors that are in the cluster
            if (std::find(cluster.begin(), cluster.end(), neighbor) == cluster.end()) continue;

            double distance = edge.weight;
            if (!visited[neighbor] && distance < minDistance) {
                minDistance = distance;
                nearestNeighbor = neighbor;
            }
        }

        currentNode = nearestNeighbor;
        visited[currentNode] = true;
        path[i] = currentNode;
    }

    // Return to the start node if specified
    if (returnToStart) {
        path[numNodes] = cluster[0];
    }

    return path;
}

std::vector<int> Graph::DivideConquerClusteredNN() {
    int k = 5; // Number of clusters. You can experiment with different values.
    std::vector<Cluster> clusters = clusterNodes(k);

    std::vector<int> path;
    for (const auto& cluster : clusters) {
        // Generate a path for each cluster using NearestNeighbor
        std::vector<int> clusterPath = NearestNeighbor(cluster.nodes, false);
        if(path.empty()){
            path.insert(path.end(), clusterPath.begin(), clusterPath.end());
        }
        else{
            path = connectPaths(path, clusterPath);
        }
    }

    rotate(path.begin(), std::find(path.begin(), path.end(),0), path.end());

    return path;
}




std::vector<int> Graph::connectPaths(std::vector<int>& path1, std::vector<int>& path2) {
    double minDistance = std::numeric_limits<double>::max();
    int connectingNodePath1 = -1;
    int connectingNodePath2 = -1;

    // Iterate through all nodes in path1
    for (int i = 0; i < path1.size(); ++i) {
        int node1 = path1[i];

        // Iterate through all nodes in path2
        for (int j = 0; j < path2.size(); ++j) {
            int node2 = path2[j];

            // Iterate through all edges of node1
            for (const auto& edge : nodes[node1].adj) {
                if (edge.dest == node2 && edge.weight < minDistance) {
                    minDistance = edge.weight;
                    connectingNodePath1 = i;
                    connectingNodePath2 = j;
                }
            }
        }
    }

    // No connecting edge found
    if (connectingNodePath1 == -1 || connectingNodePath2 == -1) {
        throw std::logic_error("No connecting edge between clusters");
    }

    // Reorder path1 and path2 so that the connecting nodes are at the end of path1 and the start of path2
    std::rotate(path1.begin(), path1.begin() + connectingNodePath1+1, path1.end());
    std::rotate(path2.begin(), path2.begin() + connectingNodePath2, path2.end());

    // Connect path1 and path2
    path1.insert(path1.end(), path2.begin(), path2.end());

    return path1;
}

int Graph::findSet(int node, vector<int>& parent) {
    if (parent[node] == node)
        return node;
    return parent[node] = findSet(parent[node], parent);
}

// Function to merge two sets
void Graph::unionSets(int set1, int set2, vector<int>& parent) {
    parent[set1] = set2;
}


// hierarchical agglomerative clustering
vector<Cluster> Graph::clusterNodes(int k) {

    int n = nodes.size();
    vector<int> parent(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    // Create a priority queue of edges, sorted by increasing weight
    priority_queue<Edge, vector<Edge>, EdgeComparator> pq;
    for (int i = 0; i < n; i++) {
        for (const Edge& edge : nodes[i].adj) {
            pq.push(edge);
        }
    }

    // Merge sets until only k clusters remain
    int numClusters = n;
    while (numClusters > k) {
        Edge edge = pq.top();
        pq.pop();
        int set1 = findSet(edge.ori, parent);
        int set2 = findSet(edge.dest, parent);
        if (set1 != set2) {
            unionSets(set1, set2, parent);
            numClusters--;
        }
    }

    // Create clusters based on the final disjoint sets
    vector<Cluster> clusters(k);
    for (int i = 0; i < n; i++) {
        int set = findSet(i, parent);
        if(clusters.empty()){
            clusters[0].nodes.push_back(i);
        }
        else{
            for(int j=0; j<k; j++){
                if(clusters[j].nodes.empty()){
                    clusters[j].nodes.push_back(i);
                    break;
                }
                else if(findSet(clusters[j].nodes[0], parent) == set){
                    clusters[j].nodes.push_back(i);
                    break;
                }
            }
        }
    }

    return clusters;
}



//O(n^2 log n)
std::vector<int> Graph::TSPApproximation() {
    std::vector<Edge> mst = minimumSpanningTree();

    // Step 2: Duplicate the edges of the MST
    std::vector<Edge> duplicatedEdges = duplicateEdges(mst);

    // Step 3: Find an Eulerian tour in the multigraph
    std::vector<int> eulerianTour = findEulerianTour(duplicatedEdges);

    // Step 4: Remove duplicate nodes from the Eulerian tour to obtain a Hamiltonian tour
    std::vector<int> hamiltonianTour = removeDuplicateNodes(eulerianTour);

    auto it = std::find(hamiltonianTour.begin(), hamiltonianTour.end(), 0);
    std::rotate(hamiltonianTour.begin(), it, hamiltonianTour.end());

    return hamiltonianTour;
}

std::vector<Edge> Graph::minimumSpanningTree() {
    int numNodes = getNumNodes();

    std::vector<Edge> mstEdges;

    std::vector<bool> visited(numNodes, false);

    std::priority_queue<Edge, std::vector<Edge>, EdgeComparator> pq;

    for (const Edge& edge : nodes[0].adj) {
        pq.push(edge);
    }

    while (!pq.empty()) {
        Edge minEdge = pq.top();
        pq.pop();

        int ori = minEdge.ori;
        int dest = minEdge.dest;

        if (visited[dest]) {
            continue;
        }

        mstEdges.push_back(minEdge);

        visited[dest] = true;

        for (const Edge& edge : nodes[dest].adj) {
            pq.push(edge);
        }
    }

    for (int i = 1; i < numNodes; ++i) {
        if (!visited[i]) {
            std::vector<Edge> disconnectedMST = minimumSpanningTreeForComponent(i, visited);
            mstEdges.insert(mstEdges.end(), disconnectedMST.begin(), disconnectedMST.end());
        }
    }

    // Add missing edges using Haversine distance.
    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            if (!visited[j]) {
                Edge newEdge = {i, j, Haversine(nodes[i], nodes[j])};
                mstEdges.push_back(newEdge);
            }
        }
    }

    return mstEdges;
}

std::vector<Edge> Graph::minimumSpanningTreeForComponent(int startNode, std::vector<bool>& visited) {
    std::vector<Edge> mstEdges;

    // Create a priority queue to store the edges
    std::priority_queue<Edge, std::vector<Edge>, EdgeComparator> pq;

    // Add all the edges of the start node to the priority queue
    for (const Edge& edge : nodes[startNode].adj) {
        pq.push(edge);
    }

    while (!pq.empty()) {
        // Get the minimum-weight edge from the priority queue
        Edge minEdge = pq.top();
        pq.pop();

        int ori = minEdge.ori;
        int dest = minEdge.dest;

        // Check if the destination node has already been visited
        if (visited[dest]) {
            continue;
        }

        // Add the minimum-weight edge to the minimum spanning tree
        mstEdges.push_back(minEdge);

        // Mark the destination node as visited
        visited[dest] = true;

        // Add the edges of the destination node to the priority queue
        for (const Edge& edge : nodes[dest].adj) {
            pq.push(edge);
        }
    }

    return mstEdges;
}

std::vector<Edge> Graph::duplicateEdges(const std::vector<Edge>& edges) {
    std::vector<Edge> duplicatedEdges;

    for (const auto& edge : edges) {
        // Duplicate the edge
        Edge duplicatedEdge1 = {edge.ori, edge.dest, edge.weight};
        Edge duplicatedEdge2 = {edge.dest, edge.ori, edge.weight};

        // Add both duplicated edges to the list
        duplicatedEdges.push_back(duplicatedEdge1);
        duplicatedEdges.push_back(duplicatedEdge2);
    }

    return duplicatedEdges;
}

std::vector<int> Graph::findEulerianTour(const std::vector<Edge>& edges) {
    // Create a multimap to store the edges for each node
    std::multimap<int, Edge> edgeMap;

    // Store the edges in the multimap
    for (const Edge& edge : edges) {
        edgeMap.emplace(edge.ori, edge);
    }

    std::vector<int> eulerianTour;
    std::stack<int> tourStack;

    // Find the connected components
    std::vector<std::vector<int>> components = findConnectedComponents();

    // Start the tour from node 0
    int currentNode = 0;
    tourStack.push(currentNode);

    while (!tourStack.empty()) {
        // Check if the current node has any remaining edges
        if (edgeMap.find(currentNode) != edgeMap.end()) {
            // Get the next edge from the multimap
            auto edgeIt = edgeMap.find(currentNode);
            Edge currentEdge = edgeIt->second;

            // Remove the edge from the multimap
            edgeMap.erase(edgeIt);

            // Push the destination node onto the stack
            tourStack.push(currentEdge.dest);

            // Move to the destination node
            currentNode = currentEdge.dest;
        } else {
            // Add the current node to the Eulerian tour
            eulerianTour.push_back(currentNode);

            // Move to the previous node
            currentNode = tourStack.top();
            tourStack.pop();
        }
    }

    // Handle disconnected components
    for (const auto& component : components) {
        // Find an Eulerian tour for each disconnected component
        std::vector<int> componentTour = findEulerianTourForComponent(component, edgeMap);

        // Add the component tour to the overall Eulerian tour
        eulerianTour.insert(eulerianTour.end(), componentTour.begin(), componentTour.end());
    }

    return eulerianTour;
}

std::vector<int> Graph::findEulerianTourForComponent(const std::vector<int>& component, std::multimap<int, Edge>& edgeMap) {
    std::vector<int> eulerianTour;
    std::stack<int> tourStack;

    // Start the tour from the first node in the component
    int currentNode = component[0];
    tourStack.push(currentNode);

    while (!tourStack.empty()) {
        // Check if the current node has any remaining edges
        if (edgeMap.find(currentNode) != edgeMap.end()) {
            // Get the next edge from the multimap
            auto edgeIt = edgeMap.find(currentNode);
            Edge currentEdge = edgeIt->second;

            // Remove the edge from the multimap
            edgeMap.erase(edgeIt);

            // Push the destination node onto the stack
            tourStack.push(currentEdge.dest);

            // Move to the destination node
            currentNode = currentEdge.dest;
        } else {
            // Add the current node to the Eulerian tour
            eulerianTour.push_back(currentNode);

            // Move to the previous node
            currentNode = tourStack.top();
            tourStack.pop();
        }
    }

    return eulerianTour;
}

std::vector<int> Graph::removeDuplicateNodes(const std::vector<int>& eulerianTour) {
    std::vector<int> hamiltonianTour;

    // Remove duplicate nodes from the Eulerian tour to obtain a Hamiltonian tour
    std::vector<bool> visited(nodes.size(), false);
    for (int node : eulerianTour) {
        if (!visited[node]) {
            hamiltonianTour.push_back(node);
            visited[node] = true;
        }
    }



    return hamiltonianTour;
}





