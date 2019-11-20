// CPP program to count number of shortest
// paths from a given source to every other
// vertex using BFS.
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;
int N, M, S, T;
// Traverses graph in BFS manner. It fills
// dist[] and paths[]
void BFS(vector<int> adj[], int src, int dist[], int paths[], int n) {
    bool visited[n];
    for (int i = 0; i < n; i++) visited[i] = false;
    dist[src] = 0;
    paths[src] = 1;

    queue<int> q;
    q.push(src);
    visited[src] = true;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        // For all neighbors of current vertex do:
        for (auto x : adj[curr]) {
            // if the current vertex is not yet
            // visited, then push it to the queue.
            if (visited[x] == false) {
                q.push(x);
                visited[x] = true;
            }

            // check if there is a better path.
            if (dist[x] > dist[curr] + 1) {
                dist[x] = dist[curr] + 1;
                paths[x] = paths[curr];
            }

            // additional shortest paths found
            else if (dist[x] == dist[curr] + 1)
                paths[x] += paths[curr];
        }
    }
}

// function to find number of different
// shortest paths form given vertex s.
// n is number of vertices.
void findShortestPaths(vector<int> adj[], int n, int s, int dest) {
    ofstream out("output.txt");
    int dist[n], paths[n];
    for (int i = 0; i < n; i++) dist[i] = INT_MAX;
    for (int i = 0; i < n; i++) paths[i] = 0;
    BFS(adj, s, dist, paths, n);
    out << dist[dest] << " " << paths[dest] << endl;
    /*     cout << "Numbers of shortest Paths are: ";
        for (int i = 0; i < n; i++) {
            cout << paths[i] << " ";
        }
        cout << endl;
        cout << "Distances are: ";
        for (int i = 0; i < n; i++) {
            cout << dist[i] << " ";
        }
        cout << endl; */
}

// A utility function to add an edge in a
// directed graph.
void addEdge(vector<int> adj[], int u, int v) { adj[u].push_back(v); }

// Driver code
int main() {
    ifstream in("input.txt");

    in >> N >> M >> S >> T;
    vector<int> adj[N];
    for (int j = 0; j < M; j++) {
        int from, to;
        in >> from >> to;
        addEdge(adj, from, to);
    }
    findShortestPaths(adj, N, S, T);
    return 0;
}
