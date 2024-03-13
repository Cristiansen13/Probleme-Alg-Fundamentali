#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 250;

ifstream in("bile.in");
ofstream out("bile.out");

int findSet(int i, vector<int>& parent) {
    if (parent[i] == i)
        return i;
    return parent[i] = findSet(parent[i], parent);
}

void unionSets(int i, int j, vector<int>& parent, vector<int>& componentSize) {
    int parentI = findSet(i, parent);
    int parentJ = findSet(j, parent);

    if (parentI != parentJ) {
        componentSize[parentJ] += componentSize[parentI];
        componentSize[parentI] = 0;
        parent[parentI] = parentJ;
    }
}

void readInput(int& n, vector<vector<int>>& graph) {
    in >> n;

    for (int i = 0; i < n * n; i++) {
        int x, y;
        in >> x >> y;
        graph[i] = {x, y};
    }
}

int main() {
    vector<int> parent(NMAX + NMAX * NMAX + NMAX);
    vector<vector<int>> graph(NMAX * NMAX, vector<int>(2));
    vector<int> result(NMAX * NMAX);
    vector<int> componentSize(NMAX + NMAX * NMAX + NMAX);

    int n, maxComponentSize = 0, position;
    readInput(n, graph);

    for (int i = 0; i < n; i++)
        parent[i] = parent[n - 1 + n * n + n - i] = -1;

    for (int i = n * n - 1; i > 0; i--) {
        result[i] = maxComponentSize;
        position = n - 1 + (graph[i][0] - 1) * n + graph[i][1];
        componentSize[position] = 1;
        parent[position] = position;

        if (parent[position - n] > 0)
            unionSets(position - n, position, parent, componentSize);
        if (parent[position + n] > 0)
            unionSets(position + n, position, parent, componentSize);
        if (parent[position + 1] > 0 && graph[i][1] < n)
            unionSets(position + 1, position, parent, componentSize);
        if (parent[position - 1] > 0 && graph[i][1] > 1)
            unionSets(position - 1, position, parent, componentSize);

        if (componentSize[position] > maxComponentSize)
            maxComponentSize = componentSize[position];
    }

    result[0] = n * n - 1;

    for (int i = 0; i < n * n; i++)
        out << result[i] << "\n";

    return 0;
}
