#include<iostream>
#include<list>
#include<cmath>
#include<cfloat>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<utility>
#include<vector>
#define big 1000000
using namespace std;

int small(int a, int b) {
    return (a < b) ? a : b;
}

void seed() {
    srand(time(0));
}

int random(int max) {
    return rand() % (max + 1);
}

double distance(double x1, double y1, double x2, double y2) {
    double d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    cout << "distance between these points is " << d << endl;
    return d;
}

double rotations(double d) {
    int rotations = d / 0.1;
    cout << "total tyre rotations needed are " << rotations << " cm" << endl;
    return rotations;
}

pair<int, int> findcd(int limit) {
    int x = random(limit);
    int y = random(limit);
    return make_pair(x, y);
}

class sponge {
public:
    int s;
    int a;
    int* array;
    int last;
public:
    sponge(int b) {
        s = b;
        array = new int[s];
        last = s - 1;
        a = 0;
        for (int i = 0; i < s; i++) {
            array[i] = -1;
        }
    }

    void push(int x) {
        if (a == s) {
            cout << "full" << endl;
        } else {
            array[a] = x;
            a++;
        }
    }

    void pop(int x) {
        int t = 0;
        while (array[t] != x && t < last) {
            t++;
        }
        if (array[t] == x) {
            for (int i = t; i < last; i++) {
                array[i] = array[i + 1];
            }
            last--;
        }
    }

    void display() {
        for (int i = 0; i < last + 1; i++) {
            cout << array[i] << " ";
        }
    }

    bool empty() {
        return (last == -1);
    }
};

class graph {
public:
    int s;
    list<pair<int, int>>* l;
    graph(int a) {
        s = a;
        l = new list<pair<int, int>>[a];
    }

    void addedge(int a, int b, int w) {
        l[a].push_back({ b, w });
        l[b].push_back({ a, w });
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
    // Add random edges with random weights
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int weight = random(10);  // Random weight between 0 and 10
            g.addedge(i, j, weight);
        }
    }

    return g;
}

void findShortestPath(graph& g, int source) {
    sponge unvisited(g.s);
    sponge visited(g.s);
    int r = g.s;
    int c = 3;
    vector<vector<int>> array(r, vector<int>(c));

    // Initialize the table
    for (int i = 0; i < g.s; i++) {
        array[i][0] = i;
        array[i][1] = INT_MAX;
        array[i][2] = -1;
    }

    array[source][1] = 0;
    unvisited.push(source);

    while (!unvisited.empty()) {
        int u = -1;
        int min_distance = INT_MAX;

        // Select the node with the smallest distance from the unvisited nodes
        for (int i = 0; i < g.s; i++) {
            if (array[i][1] < min_distance && !checkstatus(i, visited, unvisited)) {
                min_distance = array[i][1];
                u = i;
            }
        }

        // Mark the node as visited and remove from unvisited list
        unvisited.pop(u);
        visited.push(u);

        // Update distances for neighbors of u
        for (auto neighbor : g.l[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (array[u][1] + weight < array[v][1]) {
                array[v][1] = array[u][1] + weight;
                array[v][2] = u;
            }
        }

        // Display the Dijkstra table after each step
        cout << "Dijkstra table after processing node " << u << ":\n";
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
        cout << "---------------------\n";
    }

    // Final Dijkstra table
    cout << "Dijkstra table (Final):\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

int checkstatus(int ve, sponge uv, sponge v) {
    int check = 0;
    int t = 0;
    while (t != uv.last && uv.array[t] != ve) {
        t++;
    }
    if (uv.array[t] == ve) { check++; }

    t = 0;
    while (t != v.last && v.array[t] != ve) {
        t++;
    }
    if (v.array[t] != ve) { check++; }

    return check;
}

void dikefunction(graph& d, graph& g) {
    sponge unvisited(6);
    sponge visited(6);

    // Push all nodes to the unvisited sponge
    for (int i = 0; i < g.s; ++i) {
        unvisited.push(i);
    }
    cout << "Unvisited array: ";
    unvisited.display();
    cout << endl;
    cout << "Visited array: ";
    visited.display();
    cout << endl;

    // Initialize Dijkstra table (distance table)
    int r = g.s;
    int c = 3;
    vector<vector<int>> array(r, vector<int>(c));

    // Initialize the table
    for (int i = 0; i < g.s; i++) {
        array[i][0] = i;
        array[i][1] = INT_MAX;
        array[i][2] = -1;
    }

    // Set distance to source (node 0) to 0
    array[0][1] = 0;

    while (!unvisited.empty()) {
        int u = -1;
        int min_distance = INT_MAX;

        // Select the node with the smallest distance from the unvisited nodes
        for (int i = 0; i < unvisited.last; i++) {
            int node = unvisited.array[i];
            if (array[node][1] < min_distance) {
                min_distance = array[node][1];
                u = node;
            }
        }

        // Remove node from unvisited
        unvisited.pop(u);

        // Update distances for neighbors of u
        for (auto neighbor : g.l[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (array[u][1] + weight < array[v][1]) {
                array[v][1] = array[u][1] + weight;
                array[v][2] = u;
            }
        }

        // Display the Dijkstra table at each step
        cout << "Dijkstra table after processing node " << u << ":\n";
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
        cout << "---------------------\n";
    }

    // Final Dijkstra table
    cout << "Dijkstra table (Final):\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    seed();

    cout << "Here alex will find coordinates of the destination by using IR sensors installed in its machine body, to proceed, the code has generated random coordinates" << endl;
    pair<int, int> coordinates = findcd(100);
    cout << "coordinates are (" << coordinates.first << "," << coordinates.second << ")" << endl;

    int d = distance(0, 0, coordinates.first, coordinates.second);
    cout << "now assuming radius of tyre is " << 0.1 << endl;
    rotations(d);

    graph g(6);
    g.addedge(0, 1, 2);
    g.addedge(0, 3, 8);
    g.addedge(1, 3, 5);
    g.addedge(1, 4, 6);
    g.addedge(2, 4, 9);
    g.addedge(2, 5, 3);
    g.addedge(3, 4, 3);
    g.addedge(4, 5, 1);
    g.display();

    graph dikegraph(6);
    dikefunction(dikegraph, g);

    srand(time(0));

    // Generate random graph with 6 nodes
    graph g1 = generateRandomGraph(6);

    // Display the generated graph
    g1.display();

    // Run Dijkstra's algorithm to find the shortest path
    findShortestPath(g1, 0);  // Start from node 0

    return 0;
}
