#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
using namespace std;
const int INF = 1e9;

struct Cell {
    int row, col;
};

bool isValid(int row, int col, int N, int M) {
    return (row >= 0 && row < N && col >= 0 && col < M);
}

int minimumDiamonds(vector<vector<int>>& forest, int N, int M, int startRow, int startCol, int destRow, int destCol) {
    vector<vector<int>> distance(N, vector<int>(M, INF));
    deque<Cell> dq;

    dq.push_back({startRow, startCol});
    distance[startRow][startCol] = 0;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};

    while (!dq.empty()) {
        Cell current = dq.front();
        dq.pop_front();
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];
            if (isValid(newRow, newCol, N, M)) {
                if (forest[newRow][newCol] == forest[current.row][current.col] && distance[newRow][newCol] > distance[current.row][current.col]) {
                    distance[newRow][newCol] = distance[current.row][current.col];
                    dq.push_front({newRow, newCol});
                } else if (distance[newRow][newCol] > distance[current.row][current.col] + 1){
                    distance[newRow][newCol] = distance[current.row][current.col] + 1;
                    dq.push_back({newRow, newCol});
                }
            }
        }
    }
    return distance[destRow][destCol];
}

int main() {
    ifstream cin("padure.in");
    ofstream cout("padure.out");
    int N, M, pl, pc, cl, cc;
    cin >> N >> M >> pl >> pc >> cl >> cc;
    vector<vector<int>> forest(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> forest[i][j];
        }
    }
    int minDiam = minimumDiamonds(forest, N, M, pl - 1, pc - 1, cl - 1, cc - 1);
    cout << minDiam << endl;
    return 0;
}
