#include <fstream>
#include <iostream>

using namespace std;
int N;
// Array dichiarato con la dimensione massima
int arr[1000000];

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}
int main() {
    // lettura dati
    ifstream in("input.txt");
    in >> N;
    cout << "La dimensione dell'array è: " << N << endl;
    for (int i = 0; i < N; i++) {
        in >> arr[i];
        cout << arr[i] << " ";
    }
    cout << endl;

    // elaborazione dati
    int maxSoFar = 0;
    int maxHere = 0;
    for (int i = 0; i < N; i++) {
        maxHere = max(maxHere + arr[i], 0);
        maxSoFar = max(maxSoFar, maxHere);
    }
    cout << "La somma massima è: " << maxSoFar << endl;
    ofstream out("output.txt");
    out << maxSoFar;
    return 0;
}