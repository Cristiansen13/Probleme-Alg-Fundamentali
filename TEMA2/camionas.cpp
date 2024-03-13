#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

ifstream in("camionas.in");
ofstream out("camionas.out");

const int INF = 1000000001;
const int MaxNodes = 50001;

void findMinimumResistance(int numberOfNodes, int numberOfEdges, int truckWeight, const vector<pair<int, int>>* graph) {
    vector<int> distance(numberOfNodes + 1, INF);
    vector<int> visited(numberOfNodes + 1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;

    distance[1] = 0;
    priorityQueue.push({0, 1});

    while (!priorityQueue.empty()) {
        int currentNode = priorityQueue.top().second;
        priorityQueue.pop();
        visited[currentNode] = 0;

        for (const auto& edge : graph[currentNode]) {
            int neighborNode = edge.first;
            int edgeWeight = edge.second;

            if (distance[neighborNode] > distance[currentNode] + edgeWeight && edgeWeight <= truckWeight) {
                distance[neighborNode] = distance[currentNode] + edgeWeight;

                if (!visited[neighborNode]) {
                    priorityQueue.push({distance[neighborNode], neighborNode});
                    visited[neighborNode] = 1;
                }
            }
        }
    }

    out << distance[numberOfNodes] << endl;
}

int main() {
    int numberOfNodes, numberOfEdges, truckWeight;
    in >> numberOfNodes >> numberOfEdges >> truckWeight;

    vector<pair<int, int>> graph[MaxNodes];

    for (int i = 0; i < numberOfEdges; i++) {
        int node1, node2, resistance;
        in >> node1 >> node2 >> resistance;

        if (resistance < truckWeight) {
            graph[node1].push_back({node2, 1});
            graph[node2].push_back({node1, 1});
        } else {
            graph[node1].push_back({node2, 0});
            graph[node2].push_back({node1, 0});
        }
    }

    findMinimumResistance(numberOfNodes, numberOfEdges, truckWeight, graph);

    return 0;
}
