#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream in("rusuoaica.in");
ofstream out("rusuoaica.out");

struct MetroTunnel {
    int station1, station2, cost, index;
};

bool compareMetroTunnels(const MetroTunnel& t1, const MetroTunnel& t2) {
    if (t1.cost == t2.cost) {
        return t1.index < t2.index;
    }
    return t1.cost < t2.cost;
}

int findSet(int station, int parent[]) {
    int rootStation = station;
    while (parent[rootStation] > 0) {
        rootStation = parent[rootStation];
    }
    int root = rootStation;
    rootStation = station;
    while (root != rootStation){
        int aux = parent[rootStation];
        parent[rootStation] = root;
        rootStation = aux;
    }
    return root;
}

void unionSets(int rootStation1, int rootStation2, int parent[]) {
    if (parent[rootStation1] < parent[rootStation2]) {
        parent[rootStation1] += parent[rootStation2];
        parent[rootStation2] = rootStation1;
    } else {
        parent[rootStation2] += parent[rootStation1];
        parent[rootStation1] = rootStation2;
    }
}

void readInput(int& numStations, int& numTunnels, int& tunnelCost, vector<MetroTunnel>& metroTunnels, int parent[], int tunnelCosts[], bool isTunnelUsed[]) {
    in >> numStations >> numTunnels >> tunnelCost;

    for (int i = 1; i <= numStations; i++) {
        parent[i] = -1;
    }

    for (int i = 1; i <= numTunnels; i++) {
        in >> metroTunnels[i].station1 >> metroTunnels[i].station2 >> metroTunnels[i].cost;
        metroTunnels[i].index = i;
        tunnelCosts[i] = metroTunnels[i].cost;
    }

    for (int i = 2; i <= numStations; i++) {
        metroTunnels[numTunnels + i] = {1, i, tunnelCost, numTunnels + 1};
    }
}

long long calculateMetroCost(int numStations, int numTunnels, int tunnelCost, vector<MetroTunnel>& metroTunnels, int parent[], int tunnelCosts[], bool isTunnelUsed[]) {
    sort(metroTunnels.begin(), metroTunnels.begin() + numTunnels + numStations, compareMetroTunnels);

    long long totalCost = 0;

    for (auto tunnel : metroTunnels) {
        int station1 = tunnel.station1;
        int station2 = tunnel.station2;
        int cost = tunnel.cost;
        int rootStation1 = findSet(station1, parent);
        int rootStation2 = findSet(station2, parent);

        if (rootStation1 != rootStation2) {
            totalCost += 1LL * cost;
            unionSets(rootStation1, rootStation2, parent);
            if (tunnel.index) {
                isTunnelUsed[tunnel.index] = 1;
            }
        }
    }

    for (int i = 1; i <= numTunnels; i++) {
        if (!isTunnelUsed[i]) {
            totalCost -= tunnelCosts[i];
        }
    }

    return totalCost;
}

int main() {
    const int maxNumStations = (4e5) + 5;
    vector<MetroTunnel> metroTunnels(maxNumStations);
    int parent[maxNumStations];
    int numStations, numTunnels, tunnelCost;
    int station1, station2, cost;
    bool isTunnelUsed[maxNumStations];
    int tunnelCosts[maxNumStations];

    readInput(numStations, numTunnels, tunnelCost, metroTunnels, parent, tunnelCosts, isTunnelUsed);

    long long result = calculateMetroCost(numStations, numTunnels, tunnelCost, metroTunnels, parent, tunnelCosts, isTunnelUsed);

    out << result << '\n';

    return 0;
}
