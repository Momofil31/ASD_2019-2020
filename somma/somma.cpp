#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream in("input.txt");
    int a, b;
    in >> a >> b;
    ofstream out("output.txt");
    out << a + b;

    return 0;
}