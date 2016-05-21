#ifndef __disjoint_set_h_cdv__
#define __disjoint_set_h_cdv__

#include <vector>

using std::vector;

// A disjoint set for dense graphs with path compression and union by rank
class disjoint_set_t {
public:
    // graph has n nodes with IDs 0 to n - 1
    explicit disjoint_set_t(const int n) : parent_(n, 0), rank_(n, 0), count_(n, 1) { 
        // make all sets disjoint; i.e. 1 node of self at root and counts are 1
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
        if (repi == repj) {
            // already merged
            return;
        }

        // merge to root with shortest depth; i.e. union by rank
        if (rank_[repi] > rank_[repj]) {
            parent_[repj] = repi;
            count_[repi] += count_[repj];
            count_[repj] = 0;
        } else {
            parent_[repi] = repj;
            count_[repj] += count_[repi];
            count_[repi] = 0;
        }

        // if there is a tie in rank; arbitrarily increase rank of one tree
        if (rank_[repi] == rank_[repj]) {
            rank_[repj]++; 
        }
    }
    
    int count(const int i) const { return count_[i]; }
    
private:
    // rooted trees; parent[i] is the parent of node i 
    // sets have a representative node; i.e. the root of tree 
    vector<int> parent_; 
    vector<int> count_; // node count for parent
    
    // rank[i] >= longest path to leaf from node i 
    vector<int> rank_;
};

#endif
