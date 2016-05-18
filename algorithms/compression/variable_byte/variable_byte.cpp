#include <cinttypes>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

vector<uint64_t> decode(const vector<uint8_t>& encoded) {
    vector<uint64_t> decoded;
    uint64_t d = 0;
    int n = 0;
    for (auto byte : encoded) {
        uint64_t next_byte = byte;
        if (0x80 & byte) { // last byte 
            d |= (next_byte & 0x7F) << 7 * n;
            decoded.push_back(d);
            d = 0;
            n = 0;
        } else {
            d |= next_byte << 7 * n++;
        }            
    }
    return decoded;
}

vector<uint8_t> encode(const vector<uint64_t>& data) {
    vector<uint8_t> encoded;
    for (uint64_t d : data) {
        while (d > 0x7F) {
            encoded.push_back(d & 0x7F);
            d >>= 7;
        }
        // set highest bit for last byte 
        encoded.push_back(0x80 | d);
    }
    return encoded;
}

vector<uint64_t> generate(size_t n) {
    srand(time(NULL));
    vector<uint64_t> data(n, 0);
    data[0] = 0;
    data[1] = 1;
    data[2] = 0x7F;
    data[3] = 0xFF;
    data[4] = 0x7F << 7 | 0x7F;
    data[5] = 0xFF0000FF00FF00FFULL;
    for (size_t i = 6; i < n / 2 ; i++) {
        data[i] = rand();
    }
    for (size_t i = n / 2; i < n; i++) {    
        data[i] = (uint64_t)rand() | ((uint64_t)rand() << 32);
    }
    return data;
}

int main() {
    auto data = generate(1024 * 1024 * 100);
    auto encoded = encode(data);
    auto decoded = decode(encoded);
    if (data.size() != decoded.size()) {
        cout << "size mismatch, data = " << data.size() << ", decoded = " << decoded.size() << endl;
        return 0;
    }
    size_t failures = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] != decoded[i]) {
            cout << "i = " << i << ", data[i] = " << data[i] << ", decoded[i] = " << decoded[i] << endl;
            failures++;
        }
    }
    cout << failures << " failures" << endl; 
    cout << "data size = " << data.size() * 8 << " bytes" << endl; 
    cout << "compressed size = " << encoded.size() << " bytes" << endl; 
    return 0;
}
