#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../disjoint_set.h"
using namespace std;

int main() {
    int N = 0, Q = 0;
    cin >> N >> Q;
    disjoint_set_t set(N);
    for (int q = 0; q < Q; q++) {
        string operation;
        cin >> operation;
        if (operation == "Q") {
            int query = 0;
            cin >> query;
            int rep_query = set.find(query);
            cout << set.count(rep_query) << endl;
        } else {
            int i = 0, j = 0;
            cin >> i >> j;
            set.merge(i, j);
        }
    }
    return 0;
}
