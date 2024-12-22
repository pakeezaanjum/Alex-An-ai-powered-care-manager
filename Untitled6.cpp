//if you were not smart enough God would never had you put in this place
#include <iostream>
#include <list>
#include <utility> // For std::pair
using namespace std;

class Graph {
public:
    int vertices;                 // Number of vertices
    list<pair<int, int>> *adj;    // Array of lists where each list stores pairs (neighbor, weight)

    // Constructor
    Graph(int v) {
        vertices = v;
        adj = new list<pair<int, int>>[v];
    }

    // Function to add an edge with a weight
    void addEdge(int a, int b, int weight) {
        adj[a].push_back({b, weight}); // Add edge a->b with weight
        adj[b].push_back({a, weight}); // Add edge b->a with weight (for undirected graph)
    }

    // Function to display the graph
    void display() {
        for (int i = 0; i < vertices; ++i) {
            cout << "Adjacency list of vertex " << i << ": ";
            for (auto neighbor : adj[i]) { // Iterate through the adjacency list for vertex i
                cout << "(" << neighbor.first << ", weight: " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};
























int main() {
    Graph g(4); // Create a graph with 4 vertices

    // Add edges with weights
    g.addEdge(0, 1, 10); // Edge 0-1 with weight 10
    g.addEdge(0, 2, 20); // Edge 0-2 with weight 20
    g.addEdge(1, 2, 30); // Edge 1-2 with weight 30
    g.addEdge(2, 3, 40); // Edge 2-3 with weight 40

    // Display the graph
    g.display();

    return 0;
}


