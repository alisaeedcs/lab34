// comsc-210 | ali saeed | lab34
// ide used: vs code
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <climits>  // For using INT_MAX
using namespace std;

const int SIZE = 9;  // 9 airports in the network

struct Edge {
    int src, dest, weight;  // source, destination, and flight duration (in minutes)
};

typedef pair<int, int> Pair;  // Creating an alias for a pair of integers (weight, node)

class Graph {
public:
    vector<vector<Pair>> adjList;  // Adjacency list to represent the graph

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        // Populate adjacency list
        for (auto &edge : edges) {
            adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
            adjList[edge.dest].push_back(make_pair(edge.src, edge.weight));  // For undirected graph
        }
    }

    void printGraph() {
        cout << "Flight Route Network Topology:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Airport " << i << " connects to: " << endl;
            for (auto &v : adjList[i]) {
                cout << "\tAirport " << v.first << " (Duration: " << v.second << " mins) \n";
            }
            cout << endl;
        }
    }

    void dfs(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> temp;
        temp.push(start);
        cout << "\nFlight Route Trace (DFS) from Airport " << start << ":\n";
        cout << "========================================\n";

        int count = 1;
        while (!temp.empty()) {
            int i = temp.top();
            temp.pop();

            if (!visited[i]) {
                cout << "Step " << count++ << ": Visiting Airport " << i << endl;
                visited[i] = true;
                for (auto &neighbor : adjList[i]) {
                    if (!visited[neighbor.first]) {
                        cout << "  → Potential flight route to Airport " << neighbor.first 
                             << " (Duration: " << neighbor.second << " mins)\n";
                        temp.push(neighbor.first);
                    }
                }
            }
        }
        cout << "========================================\n";
    }

    void bfs(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        cout << "\nLayer-by-Layer Flight Route Inspection (BFS) from Airport " << start << ":\n";
        cout << "========================================\n";

        int count = 1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << "Layer " << count++ << ": Checking Airport " << v << endl;

            for (auto &neighbor : adjList[v]) {
                if (!visited[neighbor.first]) {
                    cout << "  → Next reachable destination: Airport " << neighbor.first 
                         << " (Duration: " << neighbor.second << " mins)\n";
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << "========================================\n";
    }

    // Dijkstra's algorithm for finding the shortest path from start
    void dijkstra(int start) {
        vector<int> dist(SIZE, INT_MAX);  // Distance array, initialized to infinity
        dist[start] = 0;
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;  // Min-heap priority queue
        pq.push(make_pair(0, start));  // Push the start node with distance 0

        while (!pq.empty()) {
            int u = pq.top().second;  // Get the node with the smallest distance
            pq.pop();

            // Traverse through all the neighbors of the current node u
            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // If a shorter path is found, update the distance and push to the queue
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        // Output the shortest path for each node from the start node
        cout << "\nShortest path from node " << start << ":\n";
        for (int i = 0; i < SIZE; i++) {
            cout << start << " -> " << i << " : ";
            if (dist[i] == INT_MAX) {
                cout << "No path\n";
            } else {
                cout << dist[i] << " mins\n";
            }
        }
    }

    // Prim's algorithm to find the Minimum Spanning Tree (MST)
    void primMST() {
        vector<int> key(SIZE, INT_MAX);  // To store the minimum weight edge for each vertex
        vector<int> parent(SIZE, -1);  // To store the parent node for each vertex in the MST
        vector<bool> inMST(SIZE, false);  // To check if a node is included in the MST

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;  // Min-heap priority queue

        key[0] = 0;  // Start with node 0
        pq.push(make_pair(0, 0));  // Push the start node with key 0

        while (!pq.empty()) {
            int u = pq.top().second;  // Get the node with the smallest key
            pq.pop();

            inMST[u] = true;  // Mark this node as included in the MST

            // Traverse through all the neighbors of the current node u
            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // If the neighbor is not in the MST and the weight is smaller than the current key
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push(make_pair(key[v], v));  // Push the updated key and vertex
                }
            }
        }

        // Output the edges in the MST
        cout << "\nMinimum Spanning Tree edges:\n";
        for (int i = 1; i < SIZE; i++) {
            cout << "Edge from " << parent[i] << " to " << i << " with capacity: " << key[i] << " mins\n";
        }
    }
};

int main() {
    // Define edges for the flight route network
    vector<Edge> edges = {
        {0, 1, 120}, {0, 2, 180}, {1, 3, 150}, {2, 4, 200}, {3, 5, 180}, {4, 6, 220},
        {5, 7, 140}, {6, 8, 160}, {7, 5, 180}, {8, 6, 200}
    };

    // Create the graph
    Graph graph(edges);

    int choice;
    do {
        // Display menu
        cout << "Water Distribution Network Menu:\n";
        cout << "[1] Display water distribution network\n";
        cout << "[2] Check contaminant spread (BFS)\n";
        cout << "[3] Plan inspection route  (DFS)\n";
        cout << "[4] Calculate shortest paths\n";
        cout << "[5] Find Minimum Spanning Tree\n";
        cout << "[0] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Process user's choice
        switch (choice) {
            case 1:
                graph.printGraph();
                break;
            case 2:
                graph.bfs(0);
                break;
            case 3:
                graph.dfs(0);
                break;
            case 4:
                graph.dijkstra(0);
                break;
            case 5:
                graph.primMST();
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
