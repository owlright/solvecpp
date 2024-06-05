#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>
#include <stack>
using namespace std;
using Graph = vector<vector<int>>;
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

int main()
{
    // 建图
    // clang-format off
    Graph G = {
        { 0, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 0 },
        { 0, 1, 0, 1, 0 },
        { 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0 }
    };
    // clang-format on
    vector<bool> visited(G.size(), false);
    for (int i = 0; i < G.size(); i++) { // 以防这个图不是联通的，同时也说明可以利用bfs来判断图是否是联通的
        if (!visited[i]) {
            dfs(G, i, visited);
        }
    }
}