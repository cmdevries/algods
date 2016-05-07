#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <queue>
using namespace std;

struct graph_t {
    void add(int x, int y, int r) {
        add(x, {y, r});
        add(y, {x, r});
    }
    
    void add(int from, const pair<int, int>& to) {
        auto it = edges.find(from);
        if (it == edges.end()) {
            it = edges.insert({from, {}}).first;
        }
        it->second.push_back(to);
    }
    
    // from -> [(to, weight),...]
    unordered_map<int, vector<pair<int, int>>> edges;
    int nodes;
};

vector<int> dijkstra(graph_t& graph, int source) {
    // initialization of shortest distances priority queue and unvisted vertices
    constexpr int MAX = numeric_limits<int>::max();
    vector<int> distances(graph.nodes + 1, MAX); // nodes are 1 indexed so add dummy node for 0
    distances[source] = 0;
    struct node_t {
        int node;
        int dist;
        bool operator<(const node_t& other) const {
            return dist > other.dist;
        }
    };
    priority_queue<node_t> queue;
    unordered_set<int> unvisited;
    for (int v = 1; v < distances.size(); v++) {
        unvisited.insert(v);
        queue.push({v, distances[v]});
    }
    
    // find shortest paths
    while (!queue.empty()) {
        // process node with the current minimum distance
        auto& node = queue.top();
        int curr = node.node;
        int currdist = node.dist;
        queue.pop();
        if (currdist == MAX || unvisited.find(curr) == unvisited.end()) {
            continue;
        }
        unvisited.erase(curr);
        
        // for all nodes adjacent to the current minimum, that are unvisited
        for (auto& pair : graph.edges[curr]) {
            int next = pair.first;
            int nextdist = pair.second;
            if (unvisited.find(next) != unvisited.end()) {
                int alt = currdist + nextdist; // distance of this alternate route
                if (alt < distances[next]) {
                    distances[next] = alt;
                    queue.push({next, alt});
                }
            }
        }
    }
    
    // mark unreachable nodes as -1
    for (auto& dist : distances) {
        if (dist == MAX) {
            dist = -1;
        }
    }
    return distances;
}

int main() {
    int T = 0; // test cases
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N = 0; // nodes in graph
        int M = 0; // edges in graph
        cin >> N >> M;
        graph_t graph;
        graph.nodes = N;
        for (int e = 0; e < M; e++) {
            int x = 0, y = 0, r = 0; // edge between nodes x and y of length r
            cin >> x >> y >> r;
            graph.add(x, y, r);
        }
        int S = 0; // starting position
        cin >> S;
        auto distances = dijkstra(graph, S);
        for (int i = 1; i < distances.size(); i++) {
            if (i != S) {
                cout << distances[i] << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}
