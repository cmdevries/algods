#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../disjoint_set.h"
using namespace std;

int main() {
    int N = 0;
    cin >> N;
    const int nodes = (2 * N) + 1;
    disjoint_set_t set(nodes);
    for (int n = 0; n < N; n++) {
        int i = 0, j = 0;
        cin >> i >> j;
        set.merge(i, j);
    }
    vector<int> counts(nodes, 0); // set -> count
    for (int i = 1; i < nodes; i++) {
        int repi = set.find(i);
        counts[repi]++;
    }
    int min = numeric_limits<int>::max();
    int max = numeric_limits<int>::min();    
    for (auto count : counts) {
        if (count > 1 && count < min) {
            min = count;
        }
        if (count > max) {
            max = count;
        }
    }
    cout << min << ' ' << max << endl;
    return 0;
}
