#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

// Function to generate all elements of the group (Zm x Zn, +)
vector<pair<int, int>> generateGroup(int m, int n) {
    vector<pair<int, int>> group;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            group.push_back({i, j});
        }
    }
    return group;
}

// Function to check if a subset is a subgroup of the group (Zm x Zn, +)
bool isSubgroup(const vector<pair<int, int>>& group, const set<pair<int, int>>& subset, int m, int n) {
    if (subset.empty()) {
        return false;
    }
    for (const auto& x : subset) {
        for (const auto& y : subset) {
            pair<int, int> sum = {(x.first + y.first) % m, (x.second + y.second) % n};
            if (subset.find(sum) == subset.end()) {
                return false;
            }
        }
    }
    return true;
}

// Function to generate all subsets of a set
void generateSubsets(vector<pair<int, int>>& group, set<pair<int, int>>& subset, int index, int m, int n, vector<set<pair<int, int>>>& subgroups) {
    if (index == group.size()) {
        if (isSubgroup(group, subset, m, n)) {
            subgroups.push_back(subset);
        }
        return;
    }
    generateSubsets(group, subset, index + 1, m, n, subgroups);
    subset.insert(group[index]);
    generateSubsets(group, subset, index + 1, m, n, subgroups);
    subset.erase(group[index]);
}

int main() {
    ifstream inFile("n3.in");
    ofstream outFile("n3.out");
    int m, n;
    inFile >> m >> n;
    inFile.close();

    vector<pair<int, int>> group = generateGroup(m, n);
    set<pair<int, int>> subset;
    vector<set<pair<int, int>>> subgroups;
    generateSubsets(group, subset, 0, m, n, subgroups);


    outFile << "The number of subgroups of the abelian group (Z" << m << " x Z" << n << ", +) is " << subgroups.size() << endl;
    for (int i = 0; i < subgroups.size(); i++) {
        outFile << "H" << i + 1 << " = {";
        for (const auto& element : subgroups[i]) {
            outFile << "(" << element.first << ", " << element.second << ")";
        }
        outFile << "}\n";
    }
    outFile.close();

    return 0;
}
