#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>
#include <unordered_set>
#include <utility>
using namespace std;

// TODO: smuggle color in least significant bit of pointers because pointers
// are always even on most platforms

// TODO: implement rebalancing

template <typename T>
class rb_tree_t {
public:
    rb_tree_t() : root(nullptr), count(0) {}
    void insert(const T& t) { insert(root, t); }
    bool exists(const T& t) { return find(nullptr, root, t).found; }
    void remove(const T& t) { remove(root, t); }
    size_t max_height() { return max_height(root); } 
    size_t size() { return count; }
    size_t size_traversal() { return size_traversal(root); }

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
        node_t* insert; // insertion point or point where already inserted
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

    search_t find(node_t* node, const T& t) {
        node_t* parent = node ? node->parent : nullptr;
        return find(parent, node, t);
    }

    // Rotations are untested 
    void rotate_left(node_t* node) {
        if (!node) {
            return;
        }

        // establish right link
        node_t* old_right = node->right;
        if (old_right) {
            node->right = old_right->left;
            if (old_right->left) {
                old_right->left->parent = node;
            }
        }

        // establish new parent for old right 
        if (old_right) {
            old_right->parent = node->parent;
        }
        if (node->parent) {
            if (node == node->parent->left) {
                node->parent->left = old_right;
            } else {
                node->parent->right = old_right;
            }
        } else {
            root = old_right;
        }

        // link node and old right 
        if (old_right) {
            old_right->left = node;
        }
        node->parent = old_right;
    }

    void rotate_right(node_t* node) {
        if (!node) {
            return;
        }

        node_t* old_left = node->left;
        
        // establish left link
        if (old_left) {
            node->left = old_left->right;
            if (old_left->right) {
                old_left->right->parent = node;
            }
        }

        // establish new parent for old left
        if (old_left) {
            old_left->parent = node->parent;
        }
        if (node->parent) {
            if (node == node->parent->right) {
                node->parent->right = old_left;
            } else {
                node->parent->left = old_left;
            }
        } else {
            root = old_left;
        }

        // link node and old left
        if (old_left) {
            old_left->right = node;
        }
        node->parent = old_left;
    }

    void insert_fixup(node_t* node) { } 

    void insert(node_t* node, const T& t) {
        auto search = find(node, t);
        if (!search.found) {
            node_t* parent = search.insert;
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
            count++;
        }
    }

    void remove_fixup(node_t* node) {
        if (node->color != BLACK) { // is this really needed?
            return;
        }    
    }

    void remove(node_t* match) {
        if (!match) {
            return;
        }
        node_t* parent = match->parent;

        if (match->left == nullptr
                && match->right == nullptr) { // no children, so delete
            if (parent) {    
                if (match == parent->left) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }    
            delete match;
        } else if (match->left == nullptr
                && match->right != nullptr) { // one child, link parent to right
            if (parent) {    
                if (match == parent->left) {
                    parent->left = match->right;
                } else {
                    parent->right = match->right;
                }
                match->right->parent = parent;
            } else {
                root = match->right;
                root->parent = nullptr;
            }
            delete match;
        } else if (match->left != nullptr
                && match->right == nullptr) { // one child, link parent to left 
            if (parent) {    
                if (match == parent->left) {
                    parent->left = match->left;
                } else {
                    parent->right = match->left;
                }
                match->left->parent = parent;
            } else {
                root = match->left;
                root->parent = nullptr;
            }
            delete match;
        } else { // two children
            // find smallest node larger than match
            node_t* successor = match->right;
            while (successor->left) {
                successor = successor->left;
            }
            
            // place successor value into match and remove successor from tree
            match->t = successor->t;
            remove(successor);
        }
    }

    void remove(node_t* node, const T& t) {
        auto search = find(node, t);
        if (!search.found) {
            return;
        }
        remove(search.insert);
        count--;
    }
    
    size_t max_height(node_t* node) {
        if (!node) {
            return 0;
        }    

        size_t local_max = max_height(node->left);
        local_max = max(max_height(node->right), local_max);
        local_max++;
        return local_max;
    }

    size_t size_traversal(node_t* node) {
        if (!node) {
            return 0;
        }

        size_t size = size_traversal(node->left) + size_traversal(node->right);
        size++; // for this node
        return size;
    }
   
    node_t* root;
    size_t count;
};

int main() {
    srand(time(NULL));
    unordered_set<int> data; // random order traversal
    set<int> a;
    rb_tree_t<int> b;
    const auto SIZE = 1 + (rand() % (1024 * 10));
    cout << "SIZE = " << SIZE << endl;
    for (int i = 0; i < SIZE; i++) {
        data.insert(rand());
    }
    auto check_size = [&b]() {
        if (b.size() != b.size_traversal()) {
            cout << "SIZE mismatch" << b.size() << " != (traversal) "
                 << b.size_traversal() << endl; 
        }
    };    
    for (auto t : data) {
        a.insert(t);
        b.insert(t);
        check_size();
    }
    for (auto t : data) {
        if (!b.exists(t)) {
            cout << "NOT FOUND" << endl;
        }
    }
    cout << "MAX HEIGHT = " << b.max_height() << endl;
    for (auto t : data) {
        b.remove(t);
        check_size();
        if (b.exists(t)) {
            cout << "FOUND WHEN ALREADY DELETED" << endl;
        }
    }
    return 0;
}
