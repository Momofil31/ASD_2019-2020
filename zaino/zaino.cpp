#include <bits/stdc++.h>

using namespace std;

int C, N;
vector<int> weight;
vector<int> value;

int knapsack();
int knapsackRec(vector<vector<int>> &DP, int i, int c);

void printMatrix(vector<vector<int>> const &matrix) {
    for (std::vector<int> row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << '\n';
    }
}

int main() {
    ifstream in("input.txt");

    in >> C >> N;

    weight.resize(N);
    value.resize(N);

    for (int i = 0; i < N; i++) {
        in >> weight[i] >> value[i];
    }
    in.close();

    int sol = knapsack();

    ofstream out("output.txt");
    out << sol;
    out.close();
    return 0;
}

int knapsack() {
    vector<vector<int>> DP(N + 1, vector<int>(C + 1, -1));
    // printMatrix(DP);
    return knapsackRec(DP, N, C);
}

int knapsackRec(vector<vector<int>> &DP, int i, int c) {
    if (c < 0)
        return INT_MIN;
    else if (i == 0 || c == 0)
        return 0;

    else {
        if (DP[i][c] < 0) {
            int nottaken = knapsackRec(DP, i - 1, c);
            int taken = knapsackRec(DP, i - 1, c - weight[i - 1]) + value[i - 1];
            DP[i][c] = max(taken, nottaken);
        }
        return DP[i][c];
    }
}
