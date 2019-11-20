#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
struct nodo {
    vector<int> vic;
    bool visited;
};

vector<nodo> grafo;

int visita(int node) {
    int count = 1;
    if (!grafo[node].visited) {
        grafo[node].visited = true;
        for (auto v : grafo[node].vic) {
            count += visita(v);
        }
    } else {
        return 0;
    }
    return count;
}

int main() {
    int N, M, S;

    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M >> S;

    grafo.resize(N);

    for (int j = 0; j < M; j++) {
        int from, to;
        in >> from >> to;
        grafo[from].vic.push_back(to);
        grafo[from].visited = false;
    }

    for (int i = 0; i < N; i++) {
        cout << "Nodo " << i << " ha " << grafo[i].vic.size() << " vicini"
             << endl;
        for (int v : grafo[i].vic) {
            cout << "  " << v << endl;
        }
    }
    int res = visita(S);
    out << res << endl;
    return 0;
}
