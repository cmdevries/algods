#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Find the maximum X where X = A xor B AND L <= A <= B <= R
int main() {
    int L = 0, R = 0, MAX = 0;
    cin >> L >> R;
    for (int A = L; A <= R; A++) {
        for (int B = A; B <= R; B++) {
            int XOR = A ^ B;
            if (XOR > MAX) {
                MAX = XOR;
            }
        }
    }
    cout << MAX << endl;
    return 0;
}
