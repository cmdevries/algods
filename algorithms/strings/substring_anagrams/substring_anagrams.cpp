#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int T = 0;
    cin >> T;
    string line;
    getline(cin, line);
    for (int t = 0; t < T; t++) {
        getline(cin, line);
        int count = 0;
        for (int len = 1; len < line.size(); len++) {
            for (int i = 0; i < line.size() - len; i++) {
                string a = line.substr(i, len);
                sort(a.begin(), a.end());
                for (int j = i + 1; j < line.size() - len + 1; j++) {
                    string b = line.substr(j, len);
                    sort(b.begin(), b.end());
                    if (a == b) {
                        count++;
                    }
                }
            }
        }
        cout << count << endl;
    }
    return 0;
}
