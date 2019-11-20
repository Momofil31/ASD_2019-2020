#include <fstream>
#include <iostream>
#include <vector>

#include <stack>
using namespace std;

vector<vector<int> > graph;
int N, M;

int min(int a, int b) { return (a < b) ? a : b; }

void findComponent(int u, int disc[], int low[], stack<int>& stk,
                   bool stkItem[]) {
    static int time = 0;
    disc[u] = low[u] = ++time;  // inilially discovery time and low value is 1
    stk.push(u);
    stkItem[u] = true;  // flag as u in the stack

    for (int v = 0; v < N; v++) {
        if (graph[u][v]) {
            if (disc[v] == -1) {  // when v is not visited
                findComponent(v, disc, low, stk, stkItem);
                low[u] = min(low[u], low[v]);
            } else if (stkItem[v])  // when v is in the stack, update low for u
                low[u] = min(low[u], disc[v]);
        }
    }

    int poppedItem = 0;
    if (low[u] == disc[u]) {
        while (stk.top() != u) {
            poppedItem = stk.top();
            cout << poppedItem << " ";
            stkItem[poppedItem] = false;  // mark as item is popped
            stk.pop();
        }
        poppedItem = stk.top();
        cout << poppedItem << endl;
        stkItem[poppedItem] = false;
        stk.pop();
    }
}

void strongConComponent() {
    int disc[N], low[N];
    bool stkItem[N];
    stack<int> stk;

    for (int i = 0; i < N; i++) {  // initialize all elements
        disc[i] = low[i] = -1;
        stkItem[i] = false;
    }

    for (int i = 0; i < N; i++)  // initialize all elements
        if (disc[i] == -1) findComponent(i, disc, low, stk, stkItem);
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int from, to;
            in >> from >> to;
            graph[from][to] = 1;
        }
    }

    strongConComponent();
}