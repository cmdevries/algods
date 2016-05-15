#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

// left half is array[begin:middle - 1]
// right half is array[middle:end - 1]
void merge(vector<int>& array, size_t begin, size_t middle, size_t end, vector<int>& work) {
    for (size_t i = begin, j = middle, k = begin; k < end; k++) {
        // take lowest value from left or right
        if (i < middle && (j >= end || array[i] <= array[j])) {
            work[k] = array[i++];
        } else {
            work[k] = array[j++];
        }
    }
}

// begin <= array index < end -> array indexes go from begin to end - 1
void split_merge(vector<int>& array, size_t begin, size_t end, vector<int>& work) {
    // base case array size = 1 is sorted
    if (begin + 1 >= end) { 
        return;
    }

    // split array in half
    size_t middle = (end + begin) / 2; 

    // split and merge left
    split_merge(array, begin, middle, work);

    // split and merge right
    split_merge(array, middle, end, work);
    
    // merge the two halves
    merge(array, begin, middle, end, work);
    
    // copy merged work back to array
    for (size_t i = begin; i < end; i++) {
        array[i] = work[i];
    }
}

void merge_sort(vector<int>& array) {
    vector<int> work(array.size(), 0); // working array
    split_merge(array, 0, array.size(), work);
}

int main() {
    srand(time(NULL));
    //srand(1);
    constexpr auto TRIALS = 1024;
    constexpr auto MAX_SIZE = 1024 * 1024;
    size_t failed = 0;
    size_t passed = 0;
    for (int i = 0; i < TRIALS; i++) {
        auto size = 1 + (rand() % MAX_SIZE);
        cout << "size = " << size << ", " << flush;
        vector<int> trial(size, 0);
        for (auto& t : trial) {
            t = rand();
        }
        merge_sort(trial);
        vector<int> sorted = trial;
        sort(sorted.begin(), sorted.end());
        bool bad = false;
        for (int j = 0; j < size; j++) {
            if (sorted[j] != trial[j]) {
                bad = true;
                break;
            }
        }
        if (bad) {
            failed++;
        } else {
            passed++;
        }    
    }
    cout << endl << endl;
    cout << "failed = " << failed << endl;
    cout << "passed = " << passed << endl;
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
