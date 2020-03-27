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

    int DP[N + 1][C + 1];

    // Build table K[][] in bottom up manner
    for (int i = 0; i <= N; i++) {
        for (int c = 0; c <= C; c++) {
            if (i == 0 || c == 0)
                DP[i][c] = 0;
            else if (weight[i - 1] <= c)
                DP[i][c] = max(value[i - 1] + DP[i - 1][c - weight[i - 1]], DP[i - 1][c]);
            else
                DP[i][c] = DP[i - 1][c];
            cout << DP[i][c] << '\t';
        }
        cout << endl;
    }

    ofstream out("output.txt");
    out << DP[N][C];
    out.close();
    return 0;
}