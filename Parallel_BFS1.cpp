#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Tree {
public:
    int V; // number of vertices
    vector<vector<int>> adj; // adjacency list

    Tree(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // because tree is undirected
    }

    void parallelBFS(int start) {
        vector<bool> visited(V, false); // keep track of visited nodes
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal: ";

        while (!q.empty()) {
            int size = q.size(); // number of nodes at current level
            vector<int> nextLevel; // nodes to visit in next level

            // parallel loop for current level
            #pragma omp parallel for
            for (int i = 0; i < size; i++) {
                int node;

                // Critical section to safely pop from queue
                #pragma omp critical
                {
                    if (!q.empty()) {
                        node = q.front();
                        q.pop();
                        cout << node << " ";
                    }
                }

                // Visit all neighbors of current node
                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                nextLevel.push_back(neighbor);
                            }
                        }
                    }
                }
            }

            // Push all nodes of next level into queue
            for (int n : nextLevel) {
                q.push(n);
            }
        }

        cout << endl;
    }
};

int main() {
    Tree t(5);
    t.addEdge(0, 1);
    t.addEdge(0, 2);
    t.addEdge(1, 3);
    t.addEdge(1, 4);

    cout << "Parallel BFS starting from node 0:\n";
    t.parallelBFS(0);

    return 0;
}
