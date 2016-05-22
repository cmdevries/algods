#include <iostream>
#include <set>
#include <utility>
using namespace std;

// TODO: smuggle color in least significant bit of pointers because pointers
// are always even on most platforms

// TODO: implement delete

// TODO: implement rebalancing in insert_fix

template <typename T>
class rb_tree_t {
public:
    rb_tree_t() : root(nullptr) {}
    void insert(const T& t) { insert(root, t); }
    bool find(const T& t) { return find(nullptr, root, t).found; }

private:
    enum color_t {RED, BLACK};

    struct node_t {
        T t;
        color_t color;
        node_t* left;
        node_t* right;
        node_t* parent;
    };
    
    struct search_t {
        node_t* parent; // insertion point
        bool found; // was value already found in tree?
    };

    search_t find(node_t* parent, node_t* node, const T& t) {
        if (node == nullptr) {
            return {parent, false};
        } else if (t == node->t) {
            return {node, true};
        } else if (t < node->t) {
            return find(node, node->left, t);
        } else {
            return find(node, node->right, t);
        }
    }
    
    void insert_fixup(node_t* node) { } 

    void insert(node_t* node, const T& t) {
        auto search = find(nullptr, node, t);
        if (!search.found) {
            node_t* parent = search.parent;
            node_t* newnode = new node_t;
            newnode->t = t;
            newnode->color = RED;
            newnode->left = nullptr;
            newnode->right = nullptr;
            newnode->parent = parent;
            if (parent) {
                if (t < parent->t) {
                    parent->left = newnode;
                } else {
                    parent->right = newnode;
                }
            } else { // tree was empty
                root = newnode;
            }
            insert_fixup(newnode);
        }
    }

    node_t* root;
};

int main() {
    set<int> a;
    rb_tree_t<int> b;
    auto data = {1, 10, 2, 8, 3, 7, 4, 6, 5};
    for (auto t : data) {
        a.insert(t);
        b.insert(t);
    }
    for (auto t : data) {
        if (!b.find(t)) {
            cout << "NOT FOUND" << endl;
        }
    }
    return 0;
}
