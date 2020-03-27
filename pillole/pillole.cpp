#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("input.txt");
    int N;
    in >> N;

    vector<vector<long long int>> DP(N + 1, vector<long long int>(N + 1));
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (i == 0 && j == 0) {
                DP[i][j] = 1;
            } else if (i > 0 && j == 0) {
                DP[i][j] = DP[i - 1][j + 1];
            } else if (i == 0 && j > 0) {
                DP[i][j] = DP[i][j - 1];
            } else if (i > 0 && j > 0) {
                DP[i][j] = DP[i][j - 1] + DP[i - 1][j + 1];
            }
            // cout << DP[i][j] << '\t';
        }
        // cout << endl;
    }
    ofstream out("output.txt");
    out << DP[N][0] << endl;
}