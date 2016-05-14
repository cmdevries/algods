#include <cinttypes>
#include <iostream>
#include <limits>
using namespace std;

// Louise and Richard play a game. They have a counter set to N. Louise gets the
// first turn and the turns alternate thereafter. In the game, they perform the
// following operations.
//
// - If N is not a power of 2, reduce the counter by the largest power of 2 less
//   than N.
// - If N is a power of 2, reduce the counter by half of N.
// - The resultant value is the new N which is again used for subsequent
//   operations.
//
// The game ends when the counter reduces to 1, i.e., N == 1, and the last
// person to make a valid move wins.
//
// Given N, your task is to find the winner of the game.
string game(uint64_t N) {
    bool louises_turn = false;
    uint64_t pow2 = 9223372036854775808L; // 2^63
    while (N != 1) {
        louises_turn = !louises_turn;
        while (pow2 > N) {
            pow2 >>= 1;
        }
        if (N == pow2) {
            N >>= 1;
        } else {
            N -= pow2;
        }
    }
    return louises_turn ? "Louise" : "Richard";
}

int main() {
    int T = 0;
    cin >> T;
    for (int i = 0; i < T; i++) {
        uint64_t N = 0;
        cin >> N;
        cout << game(N) << endl;
    }
    return 0;
}
