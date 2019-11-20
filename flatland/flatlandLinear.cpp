#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

int N;

void executeAlg(string input) {
    cout << input << endl;
    ifstream in(input);
    in >> N;
    cout << N << endl;

    char data[N];
    set<int> result;

    in >> data;

    cout << data << endl;
    // X<<<>>>*...
    // ...*<<<>>>X
    // N-(n-1) = N-N+1
    int posFirstSxDx = N;
    int posLastSxDx = -1;
    for (int i = 1; i < N - 3; i += 2) {
        if (posFirstSxDx == N && data[i] == 's' && data[i + 1] == 'd')
            posFirstSxDx = i;

        if (data[i + 1] == 's' && data[i + 2] == 'd') posLastSxDx = i + 1;
    }

    cout << posFirstSxDx << " " << posLastSxDx << endl;
    bool elimDx = false;
    bool elimSx = false;
    for (int i = 0; i < N; i += 2) {
        if (i == 0 || data[i - 1] == 's' || (posFirstSxDx <= i - 3))
            elimSx = true;

        if (i == N - 1 || data[i + 1] == 'd' || (posLastSxDx >= i + 2))
            elimDx = true;

        if (elimSx && elimDx) result.insert(i);

        elimSx = false;
        elimDx = false;
    }

    fstream out("output.txt", ios::out);

    // out << "Output" << numOutput << " " << result.size() << endl;
    out << result.size() << endl;
    for (auto const& el : result) {
        out << el << " ";
    }
    out << endl;

    in.close();
    out.close();
}

int main() {
    executeAlg("input.txt");
    return 0;
}
/*
int main() {
    string inputFile;
    ofstream myout("output1.txt");

    for (int i = 0; i < 17; i++) {
        inputFile = "input";
        inputFile += to_string(i);
        inputFile += ".txt";

        auto start = chrono::high_resolution_clock::now();
        executeAlg(inputFile, i);
        auto stop = chrono::high_resolution_clock::now();
        auto duration =
            chrono::duration_cast<chrono::microseconds>(stop - start);
        myout << "Input file " << i << ": " << duration.count() / 1000 << "ms"
              << endl;
    }
    return 0;
}*/