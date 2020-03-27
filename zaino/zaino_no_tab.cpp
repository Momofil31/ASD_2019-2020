#include <bits/stdc++.h>

using namespace std;

int C, N;
int weight[1000];
int value[1000];

int main() {
    ifstream in("input.txt");

    in >> C >> N;

    for (int i = 0; i < N; i++) {
        in >> weight[i] >> value[i];
    }
    in.close();

    int DP[2][C + 1];

    for (int i = 0; i <= N; i++) {
        for (int c = 0; c <= C; c++) {
            if (i == 0 || c == 0)
                DP[i % 2][c] = 0;
            else if (weight[i - 1] <= c)
                DP[i % 2][c] = max(DP[(i - 1) % 2][c - weight[i - 1]] + value[i - 1], DP[(i - 1) % 2][c]);
            else
                DP[i % 2][c] = DP[(i - 1) % 2][c];
            // cerr << DP[i % 2][c] << '\t';
        }
        // cerr << endl;
    }

    ofstream out("output.txt");
    out << DP[N % 2][C];
    out.close();
    return 0;
}