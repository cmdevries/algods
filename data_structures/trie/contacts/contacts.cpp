#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <memory>
#include <iterator>
using namespace std;

// A prefix tree for string of lower case characters.
class trie_t {
public:
    trie_t() : words(0), prefixes(0), children(ALPHABET_SIZE) { }
    
    void add(string::const_iterator begin, string::const_iterator end) {
        if (begin == end) {
            words++;
        } else {
            prefixes++;
            auto& child = find(*begin);
            if (child == nullptr) {
                child.reset(new trie_t());
            }
            child->add(++begin, end);
        }
    }

    void add(const string& word) { add(word.begin(), word.end()); }
    
    size_t find_partial(string::const_iterator begin, string::const_iterator end) {
        if (begin == end) { // match
            return prefixes + words;
        }
        auto& child = find(*begin);
        if (child == nullptr) { // no match
            return 0;
        } else {
            return child->find_partial(++begin, end);
        }
    }

    size_t find_partial(const string& prefix) { return find_partial(prefix.begin(), prefix.end()); }
    
private:
    unique_ptr<trie_t>& find(char c) { return children['z' - c]; }
    static constexpr auto ALPHABET_SIZE = 26;   
    size_t words;
    size_t prefixes;
    vector<unique_ptr<trie_t>> children;
};


int main() {
    trie_t trie;
    int N = 0;
    cin >> N;
    string line;
    getline(cin, line); // read rest of line
    for (int i = 0; i < N; i++) {
        getline(cin, line);
        istringstream iss(line);
        vector<string> tokens{istream_iterator<string>{iss},
            istream_iterator<string>{}};
        string& operation = tokens[0];
        string& word = tokens[1];
        if (operation == "add") {
            trie.add(word);
        } else {
            cout << trie.find_partial(word) << endl;
        }
    }
    return 0;
}
