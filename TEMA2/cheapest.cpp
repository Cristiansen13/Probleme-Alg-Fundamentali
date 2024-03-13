class Solution {
public:
    #define MAX 105
    #define INF 1e9
    int dist[MAX], inq[MAX];

    struct T {
        int node, price;
    };

    vector < T > v[MAX];

    struct P {
        int node, price, steps;
    };

    struct cmp {
        bool operator()(P a, P b) {
            return a.price < b.price;
        }
    };

    priority_queue < P, vector < P >, cmp > pq;

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        for (auto &curr : flights) {
            int &from = curr[0];
            int &to = curr[1];
            int &price = curr[2];
            v[from].push_back({to, price});
        }
        
        for (int i = 0; i < n; i++) {
            dist[i] = INF;
        }

        dist[src] = 0;
        pq.push({src, 0, 0});
        inq[src] = 1;

        while (!pq.empty()) {
            int node = pq.top().node;
            int steps = pq.top().steps;
            inq[node] = 0;
            pq.pop();

            if (steps > k) {
                continue;
            }

            for (auto &[to, price] : v[node]) {
                if(dist[node] + price < dist[to] && steps <= k) {
                    dist[to] = dist[node] + price;
                    if(!inq[to]) {
                        pq.push({to, dist[to], steps + 1});
                        inq[to]=1;
                    }
                }
            }
        }

        return (dist[dst] == INF ? -1 : dist[dst]);
    }
};