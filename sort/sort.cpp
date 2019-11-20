#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void Merge(int a[], int left, int center, int right) {
    int aux[right + 1];
    int i, j;
    for (i = center + 1; i > left; i--) aux[i - 1] = a[i - 1];
    for (j = center; j < right; j++) aux[right + center - j] = a[j + 1];
    for (int k = left; k <= right; k++)
        if (aux[j] < aux[i])
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
}
void Mergesort(int a[], int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        Mergesort(a, left, center);
        Mergesort(a, center + 1, right);
        Merge(a, left, center, right);
    }
}
int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N;

    in >> N;

    vector<int> array;
    int array2[N];
    int temp;
    for (int i = 0; i < N; i++) {
        in >> temp;
        array.push_back(temp);
        array2[i] = temp;
    }
    for (int i = 0; i < N; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    // sort(array.begin(), array.end());
    Mergesort(array2, 0, N - 1);

    for (int i = 0; i < N; i++) {
        out << array2[i] << " ";
    }
    out << endl;
    in.close();
    out.close();

    return 0;
}