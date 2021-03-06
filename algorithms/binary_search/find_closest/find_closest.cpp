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
        const size_t begin, const size_t end) {
    // return sentinel value for empty arrays    
    if (arr.empty()) {
        return -1;
    }
    
    // base case found lower bound
    size_t length = end - begin;
    if (length == 1) {
        if (end == arr.size()) {
            return begin;
        } else {
            // it could be closer to the one above the lower bound 
            if (abs(search - arr[begin]) < abs(search - arr[end])) {
                return begin;
            } else {
                return end;
            }
        }    
    }

    // split array in half and recurse 
    // (begin + end) / 2 could overflow
    size_t middle = begin + (end - begin) / 2; 
    if (search < arr[middle]) {
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

void test(vector<int>& arr, const int search) {
    sort(arr.begin(), arr.end());
    size_t index = find_closest(arr, search); 
    size_t index_true = find_closest_linear_scan(arr, search);
    if (index != index_true && 
        abs(search - arr[index]) != abs(search - arr[index_true])) {
        cout << endl << endl << "FAILED" << endl;
        cout << "size = " << arr.size() << endl;
        cout << "search = " << search << endl;
        cout << "binary search: index = " << index << " value = " << arr[index] << " diff = " << abs(search - arr[index]) << endl;
        cout << "linear scan: index = " << index_true << " value = " << arr[index_true] << " diff = " << abs(search - arr[index_true]) << endl;
    }            
    cout << '.' << flush;
}

int main() {
    // manual test cases
    { // 0 size vector 
        vector<int> arr;
        if (find_closest(arr, 1) != -1) {
            cout << "ERROR: zero size array not returning -1" << endl;
        }
    }
    { // 1 size array
        vector<int> arr = {5};
        for (int i = 0; i <= 10; i++) {
            test(arr, i);
        }
    }
    { // 2 size array
        vector<int> arr = {2, 5};
        for (int i = 0; i <= 7; i++) {
            test(arr, i);
        }
    }
    { // many size array
        vector<int> arr = {5, 10, 15, 20, 25, 30};
        for (int i = 0; i <= 35; i++) {
            test(arr, i);
        }
    }

    // randomly generated
    constexpr int MAXSIZE = 1024*1024;
    constexpr int TRIALS = 10000;
    vector<int> arr;
    arr.reserve(MAXSIZE);
    srand(time(NULL));
    for (int i = 0; i < TRIALS; i++) {
        arr.clear();
        int size = 1 + (rand() % MAXSIZE);
        for (int j = 0; j < size; j++) {
            arr.push_back(rand());
        }
        int search = rand();
        test(arr, search);
    }
    cout << endl;
}
