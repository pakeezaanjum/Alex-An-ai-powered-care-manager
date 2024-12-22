#include <iostream>
#include <list>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int random(int max) {
    return rand() % (max + 1); 
}

double distance(double x1, double y1, double x2, double y2) {
    double d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    cout << "Distance between these points is " << d << endl;
    return d;
}

double rotations(double d) {
    int rotations = d / 0.1;
    cout << "Total tyre rotations needed are " << rotations << " cm" << endl;
    return rotations;
}

pair<int, int> findcd(int limit) {
    int x = random(limit);
    int y = random(limit);
    return make_pair(x, y);
}

class graph {
public:
    int s;
    list<pair<int, int>>* l;
    
    graph(int a) {
        s = a;
        l = new list<pair<int, int>>[a];
    }

    void addedge(int a, int b, int w) {
        l[a].push_back({b, w});
        l[b].push_back({a, w});
    }

    void display() {
        for (int i = 0; i < s; ++i) {
            cout << "Adjacency list of vertex " << i << ": ";
            for (auto neighbor : l[i]) {
                cout << " -> " << neighbor.first << "(" << neighbor.second << ")";
            }
            cout << endl;
        }
    }
};

graph generateRandomGraph(int n) {
    graph g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int weight = random(10);  // Random weight between 0 and 10
            g.addedge(i, j, weight);
        }
    }
    return g;
}

void printDijkstraTable(const vector<int>& dist, const vector<int>& parent, int node_count) {
    cout << "Dijkstra table after processing node:\n";
    for (int i = 0; i < node_count; i++) {
        cout << i << " " << dist[i] << " " << parent[i] << "\n";
    }
    cout << "---------------------\n";
}

void findShortestPath(graph &g, int source) {
    vector<int> dist(g.s, INT_MAX); // Distance table initialized to infinity
    vector<int> parent(g.s, -1);    // Parent array to track the shortest path
    vector<bool> visited(g.s, false); // Visited nodes tracker

    dist[source] = 0; // Distance to source is 0
    list<int> unvisited; // Unvisited nodes list

    for (int i = 0; i < g.s; ++i) {
        unvisited.push_back(i); // Add all nodes to unvisited
    }

    while (!unvisited.empty()) {
        // Find the unvisited node with the smallest distance
        int u = -1;
        int min_distance = INT_MAX;
        for (int v : unvisited) {
            if (dist[v] < min_distance) {
                min_distance = dist[v];
                u = v;
            }
        }

        // Remove the node from unvisited
        unvisited.remove(u);
        visited[u] = true;

        // Update the distances of the neighboring nodes
        for (auto neighbor : g.l[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }

        // Print the Dijkstra table after processing the current node
        printDijkstraTable(dist, parent, g.s);
    }

    // Print the final shortest paths from the source
    cout << "Shortest paths from node " << source << ":\n";
    for (int i = 0; i < g.s; i++) {
        cout << "Node " << i << " distance: " << dist[i] << ", Path: ";
        int v = i;
        while (parent[v] != -1) {
            cout << v << " <- ";
            v = parent[v];
        }
        cout << source << endl;
    }
}

int main() {
    srand(time(0));

    // Alex finds the destination coordinates using IR sensors
    cout << "Here Alex will find coordinates of the destination by using IR sensors installed in its machine body, to proceed the code I have generated random coordinates." << endl;

    // Find random coordinates for the destination
    pair<int, int> coordinates = findcd(100);
    cout << "Coordinates are (" << coordinates.first << "," << coordinates.second << ")" << endl;

    // Calculate distance between (0, 0) and the random destination
    double d = distance(0, 0, coordinates.first, coordinates.second);

    // Calculate the tyre rotations needed based on the distance
    rotations(d);

    // Create a graph with 6 nodes
    graph g(6);
    g.addedge(0, 1, 2);
    g.addedge(0, 3, 8);
    g.addedge(1, 3, 5);
    g.addedge(1, 4, 6);
    g.addedge(2, 4, 9);
    g.addedge(2, 5, 3);
    g.addedge(3, 4, 3);
    g.addedge(4, 5, 1);

    // Display graph adjacency list
    g.display();

    // Find the shortest path starting from node 0
    findShortestPath(g, 0);

    return 0;
}
