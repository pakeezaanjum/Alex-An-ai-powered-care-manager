#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    vector<vector<pair<int, int>>> l;

    Graph(int n) {
        l.resize(n);
    }

    void addEdge(int u, int v, int w) {
        l[u].emplace_back(v, w);
    }
};

int main() {
    int n = 5;
    Graph g(n);

    // Adding edges
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 20);
    g.addEdge(1, 2, 30);
    g.addEdge(2, 3, 40);
    g.addEdge(3, 4, 50);

    // 2D array to store edge information
    int array[n][3];

    // Traverse the graph using a classic for loop
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < g.l[i].size(); ++j) {
            cout << i;
            cout << " ----> ";  
            cout << g.l[i][j].first << "(" << g.l[i][j].second << ")";

            // Update the array
            array[g.l[i][j].first][1] = g.l[i][j].second;  // Store the edge weight
            array[g.l[i][j].first][2] = i;  // Store the original node (i)
        }
    }

    // Print the array to verify updates
    cout << "\nArray contents after update:\n";
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": ";
        cout << "Weight = " << array[i][1] << ", ";
        cout << "Original Node = " << array[i][2] << endl;
    }

    return 0;
}
