#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef complex<double> point;

int n;
vector<vector<int>> g;
int res = 0;
bool DFS(int u, int p) {
    bool black = false;
    for (int i = 0; i < g[u].size(); ++i)
        if (g[u][i] != p) {
            bool cur = DFS(g[u][i], u);
            if (cur)
                black = true;
        }
    if (black)
        ++res;
    return !black;
}
int main() {
    ifstream in("input.txt");
    in >> n;
    g.resize(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        in >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    DFS(0, -1);
    ofstream out("output.txt");
    out << res << endl;
    return 0;
}