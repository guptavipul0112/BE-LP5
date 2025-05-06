#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

class Tree {
public:
    int nodes;
    vector<vector<int>> adj;

    Tree(int n) {
        nodes = n;
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected tree
    }

    void DFS(int node, int parent) {
        // Print current node
        #pragma omp critical
        cout << node; //<< " (Thread: " << omp_get_thread_num() << ")" << endl;

        // Visit all children (ignoring the parent to avoid going back)
        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); ++i) {
            int child = adj[node][i];
            if (child != parent) {
                DFS(child, node);
            }
        }
    }
};

int main() {
    // Tree with 6 nodes
    Tree t(6);

    // Add edges (undirected tree)
    t.addEdge(0, 1);
    t.addEdge(0, 2);
    t.addEdge(1, 3);
    t.addEdge(1, 4);
    t.addEdge(2, 5);

    cout << "Parallel DFS Traversal:" << endl;

    // Start DFS from root node 0
    t.DFS(0, -1);

    return 0;
}
