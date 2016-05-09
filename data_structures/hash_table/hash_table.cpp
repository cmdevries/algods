#include <algorithm>
#include <cctype>
#include <functional>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Hash table with chaining where collisions are stored in a vector rather than
// a linked list.
template<typename KEY, typename VALUE, typename HASH = hash<KEY>>
class hash_table {
public:
    hash_table() : size_(0), buckets_(DEFAULT_SIZE) { }
    
    hash_table(size_t buckets) : size_(0), buckets_(buckets) { }

    VALUE& operator[](const KEY& key) {
        // increase the number of buckets if needed
        if (load_factor() > DEFAULT_MAX_LOAD_FACTOR) {
            grow();
        }
        
        // find existing 
        auto& bucket = items(key);
        auto cmp = [&key](const pair<KEY, VALUE>& kv) { return key == kv.first; };    
        auto it = find_if(bucket.begin(), bucket.end(), cmp);

        // not found so insert
        if (it == bucket.end()) { 
            bucket.emplace_back(pair<KEY, VALUE>{key, VALUE()});
            bucket.shrink_to_fit();
            size_++;
            return bucket.back().second;
        }
        
        // return existing
        return it->second;
    }
    
    void print() const {
        for (size_t i = 0; i < buckets_.size(); i++) {
            cout << i << ": ";
            for (const auto& kv : buckets_[i]) {
                cout << kv.first << " = " << kv.second << ", ";
            }
            cout << endl;
        }
    }

    // quick hack to not implement iterators
    vector<pair<KEY, VALUE>> items() const { 
        vector<pair<KEY, VALUE>> values;
        for (auto& bucket : buckets_) {
            for (auto& kv : bucket) {
                values.push_back(kv); 
            }
        }
        return values;
    }
    
    size_t size() const { return size_; }

    size_t buckets() const { return buckets_.size(); }

    float load_factor() const { return size() / static_cast<float>(buckets()); }

private:
    vector<pair<KEY, VALUE>>& items(const KEY& key) {
        return buckets_[hash_(key) % buckets()];
    }

    void grow() {
        hash_table larger(buckets_.size() * DEFAULT_GROWTH_FACTOR);
        for (auto& bucket : buckets_) {
            for (auto& kv : bucket) {
                larger[kv.first] = kv.second;
            }
        }
        swap(larger);
    }

    void swap(hash_table& other) {
        buckets_.swap(other.buckets_);
        size_t tmp = size_;
        size_ = other.size_;
        other.size_ = tmp;
    }

    static constexpr auto DEFAULT_MAX_LOAD_FACTOR = 1;
    static constexpr auto DEFAULT_GROWTH_FACTOR = 2;
    static constexpr auto DEFAULT_SIZE = 16;
    HASH hash_;
    size_t size_; 
    vector<vector<pair<KEY, VALUE>>> buckets_;
};

// Read all the words in a full text dictionary.
vector<string> read_words() {
    vector<string> words;
    ifstream ifs("hash_table.in");
    string word;
    string clean_word;
    while (ifs >> word) {
        clean_word.clear();
        for (char c : word) {
            if (isalpha(c)) { clean_word += tolower(c); }
        }
        if (!clean_word.empty()) {
            words.push_back(clean_word);
        }
    }
    return words;
}

// Generate expected output using known good hash table.
void generate_test_data() {
    unordered_map<string, int> word_count;
    for (auto& word : read_words()) {
        word_count[word]++;
    }
 
    vector<pair<string, int>> items;
    for (auto& kv : word_count) {
        items.push_back(kv);
    }
    sort(items.begin(), items.end(), [](const pair<string, int>& l,
                                        const pair<string, int>& r) {
        return l.second > r.second;
    });
    for (auto& item : items) {
        cout << item.first << ", " << item.second << endl;
    }
}

// Generate output using this hash table.
void test() {
    hash_table<string, int> word_count;
    for (auto& word : read_words()) {
        word_count[word]++;
    }
    
    vector<pair<string, int>> items;
    for (auto& kv : word_count.items()) {
        items.push_back(kv);
    }
    sort(items.begin(), items.end(), [](const pair<string, int>& l,
                                        const pair<string, int>& r) {
        return l.second > r.second;
    });
    for (auto& item : items) {
        cout << item.first << ", " << item.second << endl;
    }
}

int main() {
    //generate_test_data();
    test();
    return EXIT_SUCCESS;
}
