#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct element {
    int value;
    size_t index;
            
    bool operator<(const element& other) const {
        return value < other.value;
    }
};

size_t lower_bound(const vector<element>& flavors, const int search) {
    if (flavors.empty()) {
        return -1;
    }
    
    size_t begin = 0;
    size_t end = flavors.size();
    while (begin + 1 != end) {
        // (begin + end) / 2 can cause overflow
        size_t middle = begin + (end - begin) / 2;
        if (search < flavors[middle].value) {
            // search left half
            end = middle;
        } else {
            // search right half
            begin = middle;
        }
    }
    
    return begin;
}

int main() {
    int T = 0;
    cin >> T;
    for (int t = 0; t < T; t++) {
        // Have M dollars
        // There are N ice cream flavors
        // Find two that sum M
        // Output 1 based indexes in sorted order
        // There is only 1 solution
        // Two ice cream flavors can cost the same
        int M = 0, N = 0;
        cin >> M >> N;
        vector<element> flavors(N, {0, 0});
        for (int n = 0; n < N; n++) {
            flavors[n].index = n;
            cin >> flavors[n].value;
        }
        sort(flavors.begin(), flavors.end());
        for (auto flavor : flavors) {
            int need = M - flavor.value;
            size_t lbound = lower_bound(flavors, need);
            if (lbound != -1) {
                auto& other_flavor = flavors[lbound];
                if (other_flavor.value == need && flavor.index != other_flavor.index) {
                    if (flavor.index < other_flavor.index) {
                        cout << flavor.index + 1 << ' ' <<  other_flavor.index + 1 << endl;
                    } else {
                        cout << other_flavor.index + 1 << ' ' <<  flavor.index + 1 << endl;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}
