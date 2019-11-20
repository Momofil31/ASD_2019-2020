#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct element {
    int index;
    char value;
};
/*
 * Prende in input vettore con i dati e un set (per riferimento) dove salvare i
 * risultati
 */
void bruteForce(vector<element> data, set<int>& result) {
    /*
     * Se la dimensione del vettore è 1, inserisce l'elemento nel set perchè è
     * una soluzione
     */
    if (data.size() == 1) {
        result.insert(data.at(0).index);
    } else {
        // altrimenti scorre il vettore con i dati dal secondo elemento al
        // penultimo
        for (int i = 1; i < data.size() - 1; i++) {
            // istanzia un sottovettore
            vector<element> subvector;
            // switch se l'i-esimo elemento (siamo in un loop) è 'd' o 's'
            switch (data.at(i).value) {
                case 'd':
                    // nel sottovettore sono inseriti tutti gli elementi che non
                    // siano l'i-esimo o quello alla sua destra
                    subvector = vector<element>(data.begin(), data.begin() + i);
                    subvector.insert(subvector.end(), data.begin() + i + 2,
                                     data.end());

                    // viene chiamata ricorsivamente la bruteforce sul
                    // sottovettore
                    bruteForce(subvector, result);
                    break;
                case 's':
                    subvector =
                        vector<element>(data.begin(), data.begin() + i - 1);
                    subvector.insert(subvector.end(), data.begin() + i + 1,
                                     data.end());
                    bruteForce(subvector, result);
                    break;
            }
        }
    }
}
int main() {
    int N;
    vector<element> data;

    ifstream in("input.txt");
    in >> N;

    for (int i = 0; i < N; i++) {
        element temp;
        in >> temp.value;
        temp.index = i;
        data.push_back(temp);
    }

    set<int> result = set<int>();
    bruteForce(data, result);

    ofstream out("output.txt");
    out << result.size() << endl;
    for (int const& el : result) {
        out << " " << el;
    }

    in.close();
    out.close();
    return 0;
}
/*
void executeAlg(string input) {
    int N;
    vector<element> data;

    ifstream in("input.txt");
    in >> N;

    for (int i = 0; i < N; i++) {
        element temp;
        in >> temp.value;
        temp.index = i;
        data.push_back(temp);
    }

    set<int> result = set<int>();
    bruteForce(data, result);

    ofstream out("output.txt");
    out << result.size() << endl;
    for (int const& el : result) {
        out << " " << el;
    }

    in.close();
    out.close();
}

int main() {
    string inputFile;
    ofstream myout("output1.txt");

    for (int i = 0; i < 20; i++) {
        inputFile = "input";
        inputFile += to_string(i);
        inputFile += ".txt";
        cout << inputFile << endl;

        auto start = chrono::high_resolution_clock::now();
        executeAlg(inputFile);
        auto stop = chrono::high_resolution_clock::now();
        auto duration =
            chrono::duration_cast<chrono::microseconds>(stop - start);
        myout << "Input file " << i << ": " << duration.count()
              << "microseconds" << endl;
    }
    return 0;
}*/