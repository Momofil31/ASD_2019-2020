#include <fstream>
#include <iostream>
using namespace std;

int N;
string d;
int res[1000];
int leftSD = -1;
int rightSD = -1;
int j = 0;

bool checkL(int i);
bool checkR(int i);

int main() {
    ifstream in("input.txt");
    in >> N;
    in >> d;

    // Search for SDs
    leftSD = N;
    rightSD = -1;
    for (int i = 1; i < N - 3; i += 2) {
        if (leftSD == N && d[i] == 's' && d[i + 1] == 'd') leftSD = i;
        if (d[i + 1] == 's' && d[i + 2] == 'd') rightSD = i + 1;
    }
    cout << leftSD << " " << rightSD << endl;

    // Check all number
    for (int i = 0; i < N; i += 2)
        if (checkL(i) && checkR(i)) res[j++] = i;

    ofstream out("output.txt");
    out << j << endl;
    for (int i = 0; i < j; i++) out << res[i] << " ";
    return 0;
}

bool checkL(int i) {
    return ((i == 0) || (d[i - 1] == 's') || (leftSD <= i - 3));
}

bool checkR(int i) {
    return ((i == N - 1) || (d[i + 1] == 'd') || (rightSD >= i + 2));
}
