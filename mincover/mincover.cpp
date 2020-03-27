#include <bits/stdc++.h>

using namespace std;

struct nodo {
    vector<int> children;
    int weight;
};

int N;
vector<nodo> albero;
vector<int> vc;

int getMinVertexCover(int v) {
    if (albero[v].children.size() == 0)
        return 0;

    if (vc[v] != -1)
        return vc[v];

    int sizeIncluded = 1;
    for (int &child : albero[v].children)
        sizeIncluded += getMinVertexCover(child);

    int sizeExcluded = albero[v].children.size();
    for (int &child : albero[v].children) {
        for (int &grandChild : albero[child].children)
            sizeExcluded += getMinVertexCover(grandChild);
    }

    vc[v] = min(sizeIncluded, sizeExcluded);
    return vc[v];
}

// Driver program to test above functions
int main() {
    ifstream in("input.txt");
    in >> N;
    albero.resize(N);
    vc.resize(N, -1);

    for (int i = 0; i < N - 1; i++) {
        int from, to;
        in >> from >> to;
        albero[from].children.push_back(to);
    }

    // cout << "Size of the smallest vertex cover is " << getMinVertexCover(0) << endl;
    ofstream out("output.txt");
    out << getMinVertexCover(0);

    return 0;
}