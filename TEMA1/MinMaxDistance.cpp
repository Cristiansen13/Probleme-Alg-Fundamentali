#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 2e5 + 5;
vector<int> minDist(MAX_N, MAX_N);
vector<int> marked(MAX_N, 0);
vector<vector<int>> adj(MAX_N);

void bfs(int start) {
    queue<int> q;
    q.push(start);
    minDist[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : adj[current]) {
            if (minDist[neighbor] > minDist[current] + 1) {
                minDist[neighbor] = minDist[current] + 1;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        for (int i = 0; i <= n; ++i) {
            adj[i].clear();
            minDist[i] = MAX_N;
            marked[i] = 0;
        }

        for (int i = 0; i < k; ++i) {
            int idx;
            cin >> idx;
            marked[idx] = 1;
        }

        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Find a marked node
        int startNode = 1;
        for (int i = 1; i <= n; ++i) {
            if (marked[i]) {
                startNode = i;
                break;
            }
        }

        bfs(startNode);

        int minDistance = MAX_N;
        for (int i = 1; i <= n; ++i) {
            if (marked[i]) {
                minDistance = min(minDistance, minDist[i]);
            }
        }

        cout << minDistance << endl;
    }

    return 0;
}
