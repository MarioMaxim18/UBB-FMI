#include <iostream>
#include <fstream>

using namespace std;
//(Am incercat cu relative path dar Clion-ul nu vedea fisierele asa ca m-am folosit de absolute path)
ifstream fin("/Users/mario/Desktop/Project1/n1.in");
ofstream fout("/Users/mario/Desktop/Project1/n1.out");

const int MAX_SIZE = 101;

int A[MAX_SIZE][MAX_SIZE], n, d;

//Function where we print the result
void afis() {
    n++;
    fout << "The number of associative operations is: " << n << "\n";
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < d; ++j) {
            fout << (char)('a' + (A[i][j])) << " ";
        }
        fout << "\n";
    }
    fout << "\n";
}

//Function that verifies Associativity
bool verif() {
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < d; ++j) {
            for (int k = 0; k < d; ++k) {
                if (A[A[i][j]][k] != A[i][A[j][k]]) {
                    return false;
                }
            }
        }
    }
    return true;
}

//Function that verifies if we have reached all the possible operation table
bool done() {
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < d; ++j) {
            if (A[i][j] < d - 1) {
                return false;
            }
        }
    }
    return true;
}

//Function that computes and solve the problem.
void back() {
    while (!done()) {
        int i = 0, j = 0;
        if (verif()) {
            afis();
        }
        A[i][j]++;
        while (A[i][j] == d) {
            A[i][j] = 0;
            if (j < d - 1) {
                j++;
            }
            else {
                ++i;
                j = 0;
            }
            A[i][j]++;
        }
    }
}

int main() {
    fin >> d;
    back();
    ++n;
    fout << "Associative Table Operation: " << n << "\n";
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < d; ++j) {
            fout << (char)('a' + d -1) << " ";
        }
        fout << "\n";
    }
    return 0;
}