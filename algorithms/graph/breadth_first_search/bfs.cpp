#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

struct node_t {
    int distance = -1;
    vector<node_t*> adjacent;
};

void bfs(node_t* root) {
    root->distance = 0;
    queue<node_t*> queue;
    queue.push(root);
    while (!queue.empty()) {
        node_t* current = queue.front();
        queue.pop();
        for (node_t* next : current->adjacent) {
            if (next->distance == -1) {
                next->distance = current->distance + 6;
                queue.push(next);
            }
        }        
    }
}

int main() {
    int T = 0; // test cases
    cin >> T;
    for (int i = 0; i < T; i++) {
        unordered_multimap<int, int> edges;
        int N = 0; // nodes in graph
        int M = 0; // edges in graph
        cin >> N >> M;
        vector<node_t> nodes(N);        
        for (int e = 0; e < M; e++) {
            int x = 0, y = 0; // edge between nodes x and y
            cin >> x >> y;
            nodes[x - 1].adjacent.push_back(&nodes[y - 1]);
            nodes[y - 1].adjacent.push_back(&nodes[x - 1]);
        }
        int S = 0; // starting position
        cin >> S;
        bfs(&nodes[S - 1]);
        for (int i = 0; i < nodes.size(); i++) {
            if (i != S - 1) {
                cout << nodes[i].distance << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}
