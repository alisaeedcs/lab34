// comsc-210 | ali saeed | lab34
// ide used: vs code
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
using namespace std;

const int SIZE = 9;  // 9 airports in the network

struct Edge {
    int src, dest, weight;  // source, destination, and flight duration (in minutes)
};

typedef pair<int, int> Pair;  // Creating an alias for a pair of integers

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
};

int main() {
    // Define edges for the flight route network
    vector<Edge> edges = {
        {0, 1, 120}, {0, 2, 180}, {1, 3, 150}, {2, 4, 200}, {3, 5, 180}, {4, 6, 220},
        {5, 7, 140}, {6, 8, 160}, {7, 5, 180}, {8, 6, 200}
    };

    // Create the graph
    Graph graph(edges);

    // Print the adjacency list representation of the network
    graph.printGraph();

    // DFS to simulate flight route trace
    graph.dfs(0);

    // BFS to simulate network service area analysis
    graph.bfs(0);

    return 0;
}
