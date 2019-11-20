#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N;
    int contaScambi = 0;

    int prezzo = 0;

    in >> N;
    vector<int> elements = vector<int>(N);

    for (int i = 0; i < N; i++) {
        in >> elements[i];
        cout << elements[i] << " ";
    }
    cout << endl;

    for (int i = N - 1; i > 0; i--) {
        if (elements[i] < i + 1) {
            cout << "elements[" << i << "]: " << elements[i] << " < " << i + 1
                 << endl;
            for (int j = i - 1; j >= 0; j--) {
                if (elements[j] == i + 1) {
                    cout << "trovato elemento da scambiare: " << elements[j]
                         << endl;
                    std::iter_swap(elements.begin() + i, elements.begin() + j);
                    contaScambi++;
                    prezzo += elements[i] + elements[j];
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        cout << elements[i] << " ";
    }
    cout << endl;
    out << contaScambi << " " << prezzo << endl;

    in.close();
    out.close();
    return 0;
}