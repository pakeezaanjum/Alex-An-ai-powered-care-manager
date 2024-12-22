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
            cout << "Full" << endl;
        } else {
            array[a] = x;
            a++;
        }
    }
    
    void pop(int a) {
        int i = 0;
        int d = 0;    
        int t;    
        while (array[d] != a && d < last) {
            d++;
        }
        t = d - 1;
        while (t < last - 1) {
            t++;
            d++;
            array[t] = array[d];
        }
        last--;
    }

    void display() {
        for (int i = 0; i < last + 1; i++) {
            cout << array[i] << " ";
        }
    }

    bool empty() {
        if (last == -1) cout << "Empty sponge" << endl;
        return last == -1;
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

int checkstatus(int ve, sponge uv, sponge v) {
    int check = 0;
    int t = 0;
    while (t != uv.last && uv.array[t] != ve) {
        t++;
    }
    if (uv.array[t] == ve) {
        check++;
    }
    t = 0;
    while (t != v.last && v.array[t] != ve) {
        t++;
    }
    if (v.array[t] != ve) {
        check++;
    }
    return check;
}

void findShortestPath(graph &g, int source) {
    sponge unvisited(g.s);
    sponge visited(g.s);
    int r = g.s;
    int c = 3;
    vector<vector<int>> array;
    array.resize(r, vector<int>(c));

    for (int i = 0; i < g.s; i++) {
        array[i][0] = i;
        array[i][1] = INT_MAX;
        array[i][2] = -1;
    }

    array[source][1] = 0;

    while (!unvisited.empty()) {
        int u = -1;
        int min_distance = INT_MAX;

        for (int i = 0; i < unvisited.last; i++) {
            int node = unvisited.array[i];
            if (array[node][1] < min_distance && !checkstatus(node, visited, unvisited)) {
                min_distance = array[node][1];
                u = node;
            }
        }

        unvisited.pop(u);

        for (auto neighbor : g.l[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (array[u][1] + weight < array[v][1]) {
                array[v][1] = array[u][1] + weight;
                array[v][2] = u;
            }
        }
    }

    // Print shortest paths from the source
    cout << "Shortest paths from node " << source << ":\n";
    for (int i = 0; i < g.s; i++) {
        cout << "Node " << i << " distance: " << array[i][1] << ", Path: ";
        int v = i;
        while (array[v][2] != -1) {
            cout << v << " <- ";
            v = array[v][2];
        }
        cout << source << endl;
    }
}

void dikefunction(graph &d, graph &g) {
    sponge unvisited(6);
    sponge visited(6);

    for (int i = 0; i < g.s; ++i) {
        unvisited.push(i);
    }
    cout << "Unvisited array: ";
    unvisited.display();
    cout << endl;
    cout << "Visited array: ";
    visited.display();
    cout << endl;

    int r = g.s;
    int c = 3;
    vector<vector<int>> array;  
    array.resize(r, vector<int>(c));

    for (int i = 0; i < g.s; i++) {
        array[i][0] = i;
        array[i][1] = INT_MAX;
        array[i][2] = -1;
    }

    array[0][1] = 0;

    while (!unvisited.empty()) {
        int u = -1;
        int min_distance = INT_MAX;

        for (int i = 0; i < unvisited.last; i++) {
            int node = unvisited.array[i];
            if (array[node][1] < min_distance) {
                min_distance = array[node][1];
                u = node;
            }
        }

        unvisited.pop(u);

        for (auto neighbor : g.l[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (array[u][1] + weight < array[v][1]) {
                array[v][1] = array[u][1] + weight;
                array[v][2] = u;
            }
        }

        cout << "Dijkstra table after processing node " << u << ":\n";
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
        cout << "---------------------\n";
    }

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
    cout << "Here Alex will find coordinates of the destination by using IR sensors installed in its machine body, to proceed the code I have generated random coordinates" << endl;
    pair<int, int> coordinates = findcd(100);
    cout << "Coordinates are (" << coordinates.first << "," << coordinates.second << ")" << endl;
    int d = distance(0, 0, coordinates.first, coordinates.second);
    cout << "Now assuming radius of tyre is 0.1" << endl;
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

    graph g1 = generateRandomGraph(6);
    g1.display();
    findShortestPath(g1, 0);  // Start from node 0

    return 0;
}
