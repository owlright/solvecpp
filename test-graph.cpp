#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using Graph = vector<vector<int>>;
template <class T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& array)
{
    os << "[";
    for (auto i = 0; i < array.size(); i++) {
        if (i != 0)
            os << ",";
        os << array[i];
    }
    os << "]";
    return os;
}

void bfs(const Graph& G, int start, vector<bool>& visited)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;
    auto N = G.size();
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for (auto i = 0; i < N; i++) {
            if (!visited[i] && G[node][i] > 0) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

void dfs(const Graph& G, int start, vector<bool>& visited)
{
    stack<int> q;
    q.push(start);
    visited[start] = true;
    auto N = G.size();
    while (!q.empty()) {
        int node = q.top(); // ! the only difference between bfs and dfs is here
        q.pop();
        cout << node << " ";
        for (int i = 0; i < N; i++) {
            if (!visited[i] && G[node][i] > 0) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int dijistra(const Graph& G, int src, int dest, vector<int>* path)
{
    auto N = G.size();
    vector<int> dist(N, INT_MAX);
    vector<int> prev(N, -1);
    vector<bool> visited(N, false);

    // 如果父元素大于子节点(greater)，就交换，所以最后得到的是最小堆
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({ 0, src });
    if (src == dest) {
        if (path)
            path->push_back(src);
        return 0;
    }
    bool found = false;
    while (!pq.empty()) {
        auto [_, u] = pq.top(); // current node u
        pq.pop();
        visited[u] = true;
        for (int v = 0; v < N; v++) {
            if (!visited[v] &&  G[u][v] > 0 && dist[v] > dist[u] + G[u][v] ) { // update dist[i] If there is shorted path to v through u.

                dist[v] = dist[u] + G[u][v];
                prev[v] = u;
                pq.push(make_pair(dist[v], v));
            }
            if (u == dest) {
                found = true;
                break;
            }
        }
        if (found)
            break;
    }
    if (found) {
        if (path) {
            auto u = dest;
            while (u != -1) {
                path->insert(path->begin(), u);
                u = prev[u];
            }
        }
        return dist[dest];
    }
    return INT_MAX; // unreachable
}
int main()
{
    // 建图
    // clang-format off
    Graph G = {
        { -1, -1, 10, -1, 30, 100 },
        { -1, -1,  5, -1, -1,  -1 },
        { -1, -1, -1, 50, -1,  -1 },
        { -1, -1, -1, -1, -1,  10 },
        { -1, -1, -1, 20, -1,  60 },
        { -1, -1, -1, -1, -1,  -1 }
    };
    // clang-format on
    // vector<bool> visited(G.size(), false);
    // for (int i = 0; i < G.size(); i++) { // 以防这个图不是联通的，同时也说明可以利用bfs来判断图是否是联通的
    //     if (!visited[i]) {
    //         dfs(G, i, visited);
    //     }
    // }
    vector<int> path;
    int length = dijistra(G, 0, 5, &path);
    cout << path << " " << length << endl;
}