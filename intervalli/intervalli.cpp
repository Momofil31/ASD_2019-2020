#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;
    int starts[N];
    int ends[N];
    for (int i = 0; i < N; i++) {
        in >> starts[i] >> ends[i];
    }
    sort(starts, starts + N);
    sort(ends, ends + N);

    int aux[N * 2];
    int i = 0, j = 0;
    while (i < N) {
        int c = starts[i];
        aux[j] = c;
        j++;
        while (i < N - 1 && c <= ends[i]) {
            c++;
            if (c == starts[i + 1]) i++;
        }
        aux[j] = ends[i];
        j++;
        i++;
    }

    int maxInterv = 0;
    int interv = 0;
    int x, y;
    if (j > 2) {
        for (int i = 1; i < j - 1; i += 2) {
            interv = aux[i + 1] - aux[i];
            if (interv > maxInterv) {
                x = aux[i];
                y = aux[i + 1];
                maxInterv = interv;
            }
        }
        out << x << " " << y << endl;
    } else {
        out << 0 << endl;
    }

    return 0;
}