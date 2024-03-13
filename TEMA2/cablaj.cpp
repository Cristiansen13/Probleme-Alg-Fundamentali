#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;
ifstream in("cablaj.in");
ofstream out("cablaj.out");

const double INF = 1e18;

struct localitate {
    int x, y;
};

double dist(const localitate& loc1, const localitate& loc2) {
    return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
}

double solve(int n, const vector<localitate>& coordinates) {
    vector<bool> visited(n, false);
    vector<double> min_dist(n, INF);
    min_dist[1] = 0;
    double total_length = 0;

    for (int j = 0; j < n; j++) {
        int min_idx = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (min_idx == -1 || min_dist[i] < min_dist[min_idx])) {
                min_idx = i;
            }
        }

        visited[min_idx] = true;
        total_length += min_dist[min_idx];

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                double distanta = dist(coordinates[min_idx], coordinates[i]);
                min_dist[i] = min(min_dist[i], distanta);
            }
        }
    }

    return total_length;
}

int main() {
    int n;
    in >> n;
    vector<localitate> localitati(n);
    for (int i = 0; i < n; i++)
        in >> localitati[i].x >> localitati[i].y;

    double rez = solve(n, localitati);
    out << fixed << rez << endl;
    return 0;
}