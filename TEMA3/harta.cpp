#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#define maxn 256

using namespace std;

int c[maxn][maxn], n, source, sink;

int bfs() {
    int Q[maxn], t[maxn], viz[maxn], p = 1, q = 1, u, i;
    memset(t, -1, sizeof(t));
    memset(viz, 0, sizeof(viz));
    Q[1] = source;
    viz[source] = 1;

    while (p <= q) {
        u = Q[p++];

        for (i = source; i <= sink; i++)
            if (c[u][i] && !viz[i]) {
                viz[i] = 1;
                t[i] = u;
                Q[++q] = i;
                if (i == source) {
                    break;
                }
            }
    }

    if (t[sink] == -1) {
        return 0;
    }

    for (i = sink; i; i = t[i]) {
        c[t[i]][i] -= 1;
        c[i][t[i]] += 1;
    }

    return 1;
}

void max_flow() {
    while (bfs());

    int i, j, nr = 0;
    for (i = 1; i <= n; i++)
        for (j = n + 1; j <= n << 1; j++)
            if (!c[i][j] && i != j - n)
                nr++;
    ofstream fout("harta.out");
    fout << nr << "\n";

    for (i = 1; i <= n; i++)
        for (j = n + 1; j <= n << 1; j++)
            if (!c[i][j] && i != j - n)
                fout << i << " " << j - n << "\n";

    fout.close();
}

int main() {
    ifstream fin("harta.in");
    fin >> n;
    int p, q;
    sink = 2 * n + 1;
    source = 0;

    for (int i = 1; i <= n; i++) {
        fin >> p >> q;

        c[source][i] = p;
        c[i + n][sink] = q;
    }

    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= n << 1; j++)
            c[i][j] = 1;

    for (int i = 1; i <= n; i++)
        c[i][i + n] = 0;

    fin.close();

    max_flow();

    return 0;
}
