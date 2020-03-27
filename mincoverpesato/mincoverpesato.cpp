#include <bits/stdc++.h>

using namespace std;

struct nodo {
    vector<int> children;
};

int N;
vector<nodo> albero;
vector<int> weight;
vector<int> vc;

int getMinVertexCover(int v) {
    if (albero[v].children.size() == 0)
        return 0;

    if (vc[v] != -1)
        return vc[v];

    int sizeIncluded = weight[v];
    for (int &child : albero[v].children)
        sizeIncluded += getMinVertexCover(child);
    
    //cout << "Size included node "<< v << " = " << sizeIncluded << endl;

    int sizeExcluded = 0;
    for (int &child : albero[v].children) {
        sizeExcluded += weight[child];;
        for (int &grandChild : albero[child].children)
            sizeExcluded += getMinVertexCover(grandChild);
    }

    //cout << "Size excluded node "<< v << " = " << sizeExcluded << endl;

    vc[v] = min(sizeIncluded, sizeExcluded);
    return vc[v];
}

// Driver program to test above functions
int main() {
    ifstream in("input.txt");
    in >> N;

    vc.resize(N, -1);
    albero.resize(N);
    weight.resize(N);

    for (int i = 0; i < N; i++) {
        in >> weight[i];
    }

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