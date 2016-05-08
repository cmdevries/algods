#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cinttypes>
using namespace std;

uint64_t ways_to_make_change(const int cents, const vector<int>& coins) {
    vector<uint64_t> table(cents + 1, 0);
    // base case: cents = 0
    table[0] = 1; 
    // select each coin
    for (int i = 0; i < coins.size(); i++) {
        // update values greater than or equal to the value of the coin
        for (int j = coins[i]; j <= cents; j++) {
            table[j] += table[j - coins[i]];
        }
    }
    return table.back();
}

int main() {
    int N = 0; // N cents
    int M = 0; // M coins
    cin >> N >> M;
    vector<int> coins;
    for (int i = 0; i < M; i++) {
        int coin = 0;
        cin >> coin;
        coins.push_back(coin);
    }
    cout << ways_to_make_change(N, coins);
    return 0;
}
