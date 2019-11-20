#include <climits>
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
    vector<int> elements = vector<int>(N + 1);
    vector<bool> visitati;
    visitati.resize(N + 1, false);

    for (int i = 1; i <= N; i++) {
        in >> elements[i];
        cout << elements[i] << " ";
    }
    cout << endl;

    for (int i = 1; i <= N; i++) {
        if (!visitati[i]) {
            if (elements[i] != i) {
                int sommaCiclo = 0;
                int minimo = INT_MAX;
                int j = i;
                int scambiCiclo = 0;
                while (!visitati[elements[j]]) {
                    minimo = min(minimo, elements[j]);
                    sommaCiclo += elements[j];
                    visitati[elements[j]] = true;
                    j = elements[j];
                    scambiCiclo++;
                }
                // Calcolo prezzo senza prendere in prestito
                int tempPrezzo =
                    (scambiCiclo - 1) * minimo + sommaCiclo - minimo;
                if (minimo != 1) {
                    tempPrezzo =
                        min(tempPrezzo, 2 * (1 + minimo) + (scambiCiclo - 1) +
                                            sommaCiclo - minimo);
                }
                prezzo += tempPrezzo;
                contaScambi += scambiCiclo - 1;
            }
            visitati[i] = true;
        }
    }
    out << contaScambi << " " << prezzo << endl;

    in.close();
    out.close();

    return 0;
}