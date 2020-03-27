/* Dynamic Programming implementation
of Maximum Sum Increasing Subsequence
(MSIS) problem */
#include <bits/stdc++.h>
using namespace std;

const int DIM = 10000;
int N;
int val[DIM];

/* maxSumIS() returns the maximum
sum of increasing subsequence
in arr[] of size n */
int maxSumIS(int arr[], int n) {
    int i, j, max = 0;
    int msis[n];

    /* Initialize msis values
    for all indexes */
    for (i = 0; i < n; i++)
        msis[i] = arr[i];

    /* Compute maximum sum values
    in bottom up manner */
    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (arr[i] >= arr[j] && msis[i] < msis[j] + arr[i])
                msis[i] = msis[j] + arr[i];

    /* Pick maximum of
    all msis values */
    for (i = 0; i < n; i++)
        if (max < msis[i])
            max = msis[i];

    return max;
}

// RICORSIVA
// Function to find maximum sum of increasing subsequence
int MSIS(int arr[], int i, int n, int prev, int sum) {
    // Base case: nothing is remaining
    if (i == n)
        return sum;

    // case 1: exclude the current element and process the
    // remaining elements
    int excl = MSIS(arr, i + 1, n, prev, sum);

    // case 2: include the current element if it is greater
    // than previous element
    int incl = sum;
    if (arr[i] > prev)
        incl = MSIS(arr, i + 1, n, arr[i], sum + arr[i]);

    // return maximum of above two choices
    return max(incl, excl);
}

// Driver Code
int main() {
    ifstream in("input.txt");
    in >> N;

    for (int i = 0; i < N; i++) {
        in >> val[i];
    }

    in.close();
    ofstream out("output.txt");
    out << maxSumIS(val, N) << endl;
    // out << MSIS(val, 0, N, INT_MIN, 0) << endl;
}

// This is code is contributed by rathbhupendra
