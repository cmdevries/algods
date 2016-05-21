#ifndef __disjoint_set_h_cdv__
#define __disjoint_set_h_cdv__

#include <vector>

using std::vector;

// A disjoint set for dense graphs with path compression and union by rank
// i.e. the union find algorithm
class disjoint_set_t {
public:
    // graph has n nodes with IDs 0 to n - 1
    explicit disjoint_set_t(const int n) : parent_(n, 0), rank_(n, 0) { 
        // make all sets disjoint; i.e. 1 node of self at root
        // all ranks are zero because roots are leaves
        for (int i = 0; i < n; i++) {
            parent_[i] = i; 
        }
    }

    // returns the representative for the set
    int find(const int i) {
        if (i != parent_[i]) {
            // all leaves point to the root; i.e. path compression
            parent_[i] = find(parent_[i]);
        }
        return parent_[i];
    }
    
    void merge(const int i, const int j) {
        // find the representatives of sets
        int repi = find(i);
        int repj = find(j);

        // merge to root with shortest depth; i.e. union by rank
        if (rank_[repi] > rank_[repj]) {
            parent_[repj] = repi;
        } else {
            parent_[repi] = repj;
        }

        // if there is a tie in rank; arbitrarily increase rank of one tree
        if (rank_[repi] == rank_[repj]) {
            rank_[repj]++; 
        }
    }
private:
    // rooted trees; parent[i] is the parent of node i 
    // sets have a representative node; i.e. the root of tree 
    vector<int> parent_; 
    
    // rank[i] >= longest path to leaf from node i 
    vector<int> rank_;
};

#endif
