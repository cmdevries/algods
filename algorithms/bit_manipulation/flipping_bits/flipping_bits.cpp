#include <cinttypes>
#include <iostream>
using namespace std;

// Given T unsigned 32 bit integers output the integer with all bits flipped
int main() {
    int T = 0;
    cin >> T;
    for (int i = 0; i < T; i++) {
        uint32_t integer = 0;
        cin >> integer;
        cout << ~integer << endl;
    }
    return 0;
}
