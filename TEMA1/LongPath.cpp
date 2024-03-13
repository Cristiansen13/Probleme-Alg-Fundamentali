#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<bool> viz;
vector<int> directie;

void dfs(int v, int dir) {
    viz[v] = true;
    directie[v] = dir;

    for (int u : adj[v]) {
        if (!viz[u]) {
            dfs(u, !dir);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    viz.assign(n + 1, false);
    directie.assign(n + 1, 0);
    vector<pair<int, int>> muchii;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        muchii.push_back({u, v});
    }
    dfs(1, 0);
    bool posibil = true;
    for (int i = 0; i < m; ++i) {
        int u = muchii[i].first;
        int v = muchii[i].second;
        if (directie[u] == directie[v]) {
            posibil = false;
            break;
        }
    }
    if (posibil) {
        cout << "YES" << endl;
        for (int i = 0; i < m; ++i) {
            int u = muchii[i].first;
            cout << (directie[u] ? '1' : '0');
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
