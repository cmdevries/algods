#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iostream>
#include <vector>
using namespace std;

// begin is the first index
// end is one past the end
size_t find_closest(const vector<int>& arr, const int search,
        const size_t begin, size_t end) {
    // return sentinel value for empty arrays    
    if (arr.empty()) {
        return -1;
    }
    
    // base case found lower bound
    size_t length = end - begin;
    if (length == 1) {
        int best = numeric_limits<int>::max();
        size_t best_index = 0;
        if (end != arr.size()) {
            // it could be closer to the next past the end of the subarray
            end++; 
        }    
        for (size_t i = begin; i < end; i++) {
            int diff = abs(search - arr[i]);
            if (diff < best) {
                best_index = i;
                best = diff;
            }
        }
        return best_index;
    }

    // split array in half and recurse 
    size_t middle = (begin + end) / 2;
    if (arr[middle] == search) {
        // exact match difference is 0
        return middle;
    } else if (search < arr[middle]) {
        // recurse left
        return find_closest(arr, search, begin, middle);
    } else {
        // recurse right
        return find_closest(arr, search, middle, end);
    }
}

// find closest to search in absolute difference by binary search on sorted array
// pre: array is sorted in ascending order
// post: return == index of value with the smallest difference
size_t find_closest(const vector<int>& arr, const int search) {
    return find_closest(arr, search, 0, arr.size());
}

size_t find_closest_linear_scan(const vector<int>& arr, const int search) {
    size_t best_index = 0;
    int best_diff = numeric_limits<int>::max();
    for (size_t i = 0; i < arr.size(); i++) {
        int diff = abs(search - arr[i]);
        if (diff < best_diff) {
            best_diff = diff;
            best_index = i;
        }    
    }
    return best_index;
}

int main() {
    constexpr int MAXSIZE = 1024*1024;
    constexpr int TRIALS = 10000;
    vector<int> sorted;
    sorted.reserve(MAXSIZE);
    srand(time(NULL));
    for (int i = 0; i < TRIALS; i++) {
        sorted.clear();
        int size = 1 + (rand() % MAXSIZE);
        for (int j = 0; j < size; j++) {
            sorted.push_back(rand());
        }
        sort(sorted.begin(), sorted.end());
        int search = rand();
        size_t index = find_closest(sorted, search); 
        size_t index_true = find_closest_linear_scan(sorted, search);
        if (index != index_true && sorted[index] != sorted[index_true]) {
            cout << endl << endl << "FAILED" << endl;
            cout << "size = " << sorted.size() << endl;
            cout << "search = " << search << endl;
            cout << "binary search: index = " << index << " value = " << sorted[index] << " diff = " << abs(search - sorted[index]) << endl;
            cout << "linear scan: index = " << index_true << " value = " << sorted[index_true] << " diff = " << abs(search - sorted[index_true]) << endl;
        }            
        cout << '.' << flush;
    }
    cout << endl;
}
