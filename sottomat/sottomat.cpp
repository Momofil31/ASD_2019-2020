#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;
int ROW;
int COL;

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int kadane(int arr[], int N) {
    int maxSoFar = 0;
    int maxHere = 0;
    for (int i = 0; i < N; i++) {
        maxHere = max(maxHere + arr[i], 0);
        maxSoFar = max(maxSoFar, maxHere);
    }
    return maxSoFar;
}

int main() {
    // leggo R e C in input
    ifstream in("input.txt");
    in >> ROW;
    in >> COL;

    // cout << "La matrice ha " << ROW << " righe e " << COL << " colonne."
    //    << endl;

    // dichiaro e leggo la matrice
    int mat[ROW][COL];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            in >> mat[i][j];
            // cout << mat[i][j] << " ";
        }
        // cout << endl;
    }
    // cout << endl;

    int maxSum = 0;
    int sum = 0;
    int temp[ROW];
    int left, right;

    // Set the left column
    for (left = 0; left < COL; left++) {
        // Initialize all elements of temp as 0
        for (int i = 0; i < ROW; i++) {
            temp[i] = 0;
        }

        // Set the right column for the left
        // column set by outer loop
        for (right = left; right < COL; ++right) {
            // Calculate sum between current left
            // and right for every row 'i'
            for (int i = 0; i < ROW; ++i) {
                temp[i] = temp[i] + mat[i][right];
                // cout << temp[i] << " ";
            }
            // cout << endl;
            // Find the maximum sum subarray in temp[].
            // The kadane() function also sets values
            // of start and finish. So 'sum' is sum of
            // rectangle between (start, left) and
            // (finish, right) which is the maximum sum
            // with boundary columns strictly as left
            // and right.
            sum = kadane(temp, ROW);
            // cout << "sinistra: " << left << " destra: " << right << " ";
            // cout << "la somma massimale della riga corrente è: " << sum <<
            // endl;

            // Compare sum with maximum sum so far.
            // If sum is more, then update maxSum and
            // other output values
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
    }
    cout << "La somma massimale è: " << maxSum << endl;

    ofstream out("output.txt");
    out << maxSum;
    return 0;
}
