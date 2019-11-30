#include <algorithm>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

struct node {
    vector<int> vic;
    bool visitato = false;
};

void tsdfs(vector<node>& grafo, int u, stack<int>& S) {
    grafo[u].visitato = true;
    for (auto vicino : grafo[u].vic) {
        if (!grafo[vicino].visitato) {
            tsdfs(grafo, vicino, S);
        }
    }

    S.push(u);
}

stack<int> topSort(vector<node>& grafo) {
    stack<int> S;

    for (int i = 0; i < grafo.size(); i++) {
        if (!grafo[i].visitato) {
            tsdfs(grafo, i, S);
        }
    }

    return S;
}

vector<node> transpose(vector<node> grafo) {
    vector<node> gt;
    gt.resize(grafo.size());

    for (int i = 0; i < grafo.size(); i++) {
        for (auto vicino : grafo[i].vic) {
            gt[vicino].vic.push_back(i);
        }
    }
    return gt;
}

void ccdfs(vector<node>& grafo, int counter, int u, vector<int>& id) {
    id[u] = counter;
    for (auto vicino : grafo[u].vic) {
        if (id[vicino] == 0) {
            ccdfs(grafo, counter, vicino, id);
        }
    }
}

vector<int> cc(vector<node> grafo, stack<int> S) {
    vector<int> id(grafo.size(), 0);
    int counter = 0;
    while (!S.empty()) {
        int u = S.top();
        S.pop();
        if (id[u] == 0) {
            counter++;
            ccdfs(grafo, counter, u, id);
        }
    }

    return id;
}

vector<int> scc(vector<node>& grafo) {
    stack<int> S = topSort(grafo);
    vector<node> gt = transpose(grafo);
    return cc(gt, S);
}

int main() {
    vector<node> grafo;
    int N, M, S, T;

    ifstream in("input/input19.txt");
    in >> N >> M >> S >> T;

    grafo.resize(N);
    // lettura grafo
    for (int i = 0; i < M; i++) {
        int from, to;
        in >> from >> to;
        grafo[from].vic.push_back(to);
    }

    // genera array componenti fortemente connesse
    vector<int> strongcc = scc(grafo);

    // salvo numero della componente di partenza e di fine
    // -1 perche l'array delle componenti fort. connesse le numera a partire da
    // 1 invece che da 0
    int componenteS = strongcc[S] - 1;
    int componenteT = strongcc[T] - 1;

    // massimo elemento nell'array delle componenti connesse
    // serve per avere la dimensione del grafo delle componenti
    int maxcc = *max_element(strongcc.begin(), strongcc.end());

    // genero il grafo delle componenti connesse
    vector<node> grafocc(maxcc);

    /* Scorro nodo per nodo il grafo (quello vero) e mi salvo il numero della
    componente a cui appartiene.
    Per ogni nodo scorro i vicini e per ogni vicino mi salvo il numero della
    sua componente se il vicino non appartiene alla stessa componente del
    nodo considerato, aggiungo un arco dalla componente del nodo alla
    componente del vicino nel grafo delle componenti. In caso di piu archi
    che vanno dalla stessa componente alla stessa componente aggiungo di
    nuovo. Questo non da problemi grazie all'implementazione della lista
    delle adiacenze. */
    for (int i = 0; i < grafo.size(); i++) {
        int ccNode = strongcc[i] - 1;
        for (auto vicino : grafo[i].vic) {
            int ccvic = strongcc[vicino] - 1;
            if (ccvic != ccNode) {
                grafocc[ccNode].vic.push_back(ccvic);
            }
        }
    }

    // stack contentente un ordinamento topologico del grafo delle componenti
    // fortemente connesse
    stack<int> topcc = topSort(grafocc);

    // vettore dei nodi ordinati del grafo delle componenti
    vector<int> topOrderCCArray(grafocc.size(), 0);

    vector<int> numPercorsi(topOrderCCArray.size());

    // svuoto lo stack nel vettore per rendere il tutto piu facile da scorrere

    while (!topcc.empty()) {
        topOrderCCArray.push_back(topcc.top());

        topcc.pop();
    }

    // scorro il vettore dei nodi ordinati e conto il numero di percorsi dal
    // nodo componenteS
    // Il numero di percorsi di un nodo v `e la somma del numero di
    // percorsi dei predecessori
    numPercorsi[componenteS] = 1;
    for (auto elem : topOrderCCArray) {
        for (auto vicino : grafocc[elem].vic) {
            numPercorsi[vicino] += numPercorsi[elem];
        }
    }

    ofstream out("output.txt");
    out << numPercorsi[componenteT];

    return 0;
}
