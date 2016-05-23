#include <cmath>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct element {
    int value;
    size_t index;
            
    bool operator<(const element& other) const {
        return value < other.value;
    }
};

template <typename T>
size_t lower_bound(const vector<T>& arr, const T& search) {
    if (arr.empty()) {
        return arr.size();
    }
    
    // binary search
    size_t begin = 0;
    size_t end = arr.size() - 1;
    while (begin < end) {
        // (begin + end) / 2 can cause overflow
        size_t middle = begin + (end - begin) / 2;
        if (arr[middle] < search) {
            // search right half
            begin = middle + 1;
        } else {
            // search left half
            end = middle;
        }
    }
    
    // all values are less than search
    if (arr[begin] < search) { 
        return arr.size();
    }
    return begin;
}

template <typename T>
size_t linear_scan_lower_bound(const vector<T>& arr, const T& search) {
    size_t i = 0;
    for ( ; i < arr.size(); i++) {
        if (!(arr[i] < search)) {
            return i;
        }    
    }
    return arr.size();
}

void test(vector<int>& arr, int search) {
    size_t linear = linear_scan_lower_bound(arr, search);
    size_t bsearch = lower_bound(arr, search);
    auto it = std::lower_bound(arr.begin(), arr.end(), search);
    size_t std = it - arr.begin();
    if (linear != bsearch || std != bsearch) {
        cout << "key = " << search << endl
             << "linear = " << linear << endl
             << "binary = " << bsearch << endl
             << "lower_bound = " << std << endl;
        if (arr.size() <= 100) {     
            for (auto a : arr) {
                cout << a << ' ';
            }
        }
        cout << endl << endl;
    }
}

void test_lower_bound() {
    // fixed test cases
    {
        vector<int> arr = {};
        for (int i = 0; i <= 7; i++) {
            test(arr, i);
        }
    }
    {
        vector<int> arr = {2};
        for (int i = 0; i <= 7; i++) {
            test(arr, i);
        }
    }
    {
        vector<int> arr = {2, 5};
        for (int i = 0; i <= 7; i++) {
            test(arr, i);
        }
    }
    {
        vector<int> arr = {5, 10, 15, 20, 25, 30};
        for (int i = 0; i <= 35; i++) {
            test(arr, i);
        }
    }

    // randomized test cases
    srand(time(NULL));
    {
        const auto max = 10000;
        vector<int> arr;
        arr.reserve(max);
        const auto tries = 1000 * 1000;
        for (int t = 0; t < tries; t++) {
            arr.clear();
            auto currmax = rand() % max;
            for (int i = 0; i < max; i++) {
                arr.push_back(rand() % max);
            }
            sort(arr.begin(), arr.end());
            test(arr, rand() % max);
        }    
    }
}

int main() {
    if (false) { test_lower_bound(); return 0; }
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
            size_t lbound = lower_bound(flavors, {need, 0});
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
