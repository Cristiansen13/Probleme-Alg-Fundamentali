#include <fstream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAX_NODES = 100005;
const long long INFINITY_COST = 1LL << 60;

ifstream in("trilant.in");
ofstream out("trilant.out");

bool compareNodes(const int &nodeA, const int &nodeB, long long distance[]) {
    return distance[nodeA] > distance[nodeB];
}

void dijkstra(int source, int predecessor[MAX_NODES], long long distance[], int totalNodes, vector<pair<int, long long>> graph[]) {
    char isInQueue[MAX_NODES];
    memset(isInQueue, 0, sizeof isInQueue);

    for (int i = 1; i <= totalNodes; ++i)
        distance[i] = INFINITY_COST;

    memset(predecessor, 0, sizeof (predecessor[MAX_NODES]));
    distance[source] = 0;

    auto compareFunction = [&](const int &nodeA, const int &nodeB) {
        return distance[nodeA] > distance[nodeB];
    };

    priority_queue<int, vector<int>, decltype(compareFunction)> queue(compareFunction);
    isInQueue[source] = 1;

    for (queue.push(source); !queue.empty(); queue.pop()) {
        int currentNode = queue.top();
        isInQueue[currentNode] = 0;

        for (const auto &neighbor : graph[currentNode]) {
            int adjacentNode = neighbor.first;

            if (distance[adjacentNode] > distance[currentNode] + neighbor.second) {
                distance[adjacentNode] = distance[currentNode] + neighbor.second;
                predecessor[adjacentNode] = currentNode;

                if (isInQueue[adjacentNode]) continue;

                queue.push(adjacentNode);
                isInQueue[adjacentNode] = 1;
            }
        }
    }
}

void findMinimumCostTrilant(int nodeA, int nodeB, int nodeC, long long distance[], int totalNodes, vector<pair<int, long long>> graph[]) {
    long long distanceA[MAX_NODES], distanceB[MAX_NODES];
    int predecessorA[MAX_NODES], predecessorB[MAX_NODES], predecessorC[MAX_NODES];

    dijkstra(nodeA, predecessorA, distance, totalNodes, graph);
    for (int i = 1; i <= totalNodes; ++i)
        distanceA[i] = distance[i];

    dijkstra(nodeB, predecessorB, distance, totalNodes, graph);
    for (int i = 1; i <= totalNodes; ++i)
        distanceB[i] = distance[i];

    dijkstra(nodeC, predecessorC, distance, totalNodes, graph);

    long long minimumCost = INFINITY_COST;
    int commonNodeX = 0;

    for (int i = 1; i <= totalNodes; ++i)
        if (distanceA[i] + distanceB[i] + distance[i] < minimumCost)
            minimumCost = distanceA[i] + distance[i] + distanceB[i], commonNodeX = i;

    out << minimumCost << "\n";

    int numberOfNodes = 0, path[MAX_NODES];

    for (int currentNode = commonNodeX; currentNode != nodeA; currentNode = predecessorA[currentNode])
        path[++numberOfNodes] = currentNode;

    out << numberOfNodes + 1 << " ";
    for (int i = 1; i <= numberOfNodes; ++i)
        out << path[i] << " ";
    out << nodeA << "\n";

    numberOfNodes = 0;
    for (int currentNode = commonNodeX; currentNode != nodeB; currentNode = predecessorB[currentNode])
        path[++numberOfNodes] = currentNode;

    out << numberOfNodes + 1 << " ";
    for (int i = 1; i <= numberOfNodes; ++i)
        out << path[i] << " ";
    out << nodeB << "\n";

    numberOfNodes = 0;
    for (int currentNode = commonNodeX; currentNode != nodeC; currentNode = predecessorC[currentNode])
        path[++numberOfNodes] = currentNode;

    out << numberOfNodes + 1 << " ";
    for (int i = 1; i <= numberOfNodes; ++i)
        out << path[i] << " ";
    out << nodeC << "\n";
}

int main() {
    vector<pair<int, long long>> graph[MAX_NODES];
    int totalNodes, totalEdges, nodeA, nodeB, nodeC;
    long long distance[MAX_NODES];

    in >> totalNodes >> totalEdges >> nodeA >> nodeB >> nodeC;

    for (int i = 1; i <= totalEdges; ++i) {
        int nodeR, nodeY;
        long long cost;
        in >> nodeR >> nodeY >> cost;

        graph[nodeR].push_back({nodeY, cost});
        graph[nodeY].push_back({nodeR, cost});
    }

    findMinimumCostTrilant(nodeA, nodeB, nodeC, distance, totalNodes, graph);

    return 0;
}
