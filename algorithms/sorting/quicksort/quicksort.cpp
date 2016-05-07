#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

size_t partition(vector<int>& array, size_t low, size_t high) {
    int pivot = array[high];
    size_t i = low; // place for swapping
    for (size_t j = low; j < high; j++) {
        if (array[j] < pivot) {
            // swap with greater
            int tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
            i++;
        }
    }
    int tmp = array[i];
    array[i] = array[high];
    array[high] = tmp;
    for (auto e : array) {
        cout << e << ' ';
    }
    cout << endl;
    return i;
}

void quicksort(vector<int>& array, size_t low, size_t high) {
    if (low - high > 1) {
        size_t p = partition(array, low, high);
        quicksort(array, low, p - 1);
        quicksort(array, p + 1, high);
    }    
}

int main() {
    int n = 0;
    cin >> n;
    vector<int> array(n, 0);
    for (int i = 0; i < n; i++) {
        int e;
        cin >> e;
        array[i] = e;
    }
    quicksort(array, 0, array.size() - 1);
    return 0;
}
