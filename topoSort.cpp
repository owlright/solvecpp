#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <unordered_map>
#include <vector>
/*
DAG
即有向无环图，用DAG可以描述一些有依赖关系的任务组，而这些任务还有另一个属性，即都有一个权重，标示这个任务的重要性，我们需要你实现一个算法，对DAG
里面的节点进行排序，保证排序不违背DAG的依赖关系，即有一个任务A如果排在任务B前面，那么在DAG中不能存在有B到A的路径，另外有一个要求是，让权重大的任务尽量优先执行。输入︰在第一行给定DAG的节点数n和边数e，后面n行，每一行是节点的标号和权重，最后e行是边的描述。
排序好的节点标号，在一行内输出，用空格隔开。输入样例:
4 4
1 2
2 3
3 5
4 4
1 2
1 3
2 4
3 4
输出：1 3 2 4
*/

using namespace std;
using Graph = unordered_map<int, vector<int>>;
void dfs(int node, Graph& graph, vector<bool>& visited, stack<int>& sorted_nodes)
{
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, sorted_nodes);
        }
    }
    sorted_nodes.push(node);
}

vector<int> topologicalSort(int n, Graph& graph)
{
    vector<bool> visited(n + 1, false);
    stack<int> sorted_nodes;

    for (int node = 1; node <= n; ++node) {
        if (!visited[node]) {
            dfs(node, graph, visited, sorted_nodes);
        }
    }

    vector<int> result;
    while (!sorted_nodes.empty()) {
        result.push_back(sorted_nodes.top());
        sorted_nodes.pop();
    }

    return result;
}

int main()
{

    std::vector<pair<int, int>> node_weights;
    Graph graph;
    // int n, e;
    // cin >> n >> e;
    // for (int i = 0; i < n; ++i) {
    //     int node, weight;
    //     cin >> node >> weight;
    //     node_weights[node] = weight;
    // }

    // for (int i = 0; i < e; ++i) {
    //     int start, end;
    //     cin >> start >> end;
    //     graph[start].push_back(end);
    // }
    int n = 4;
    int e = 4;
    node_weights.push_back({ 1, 2 });
    node_weights.push_back({ 2, 3 });
    node_weights.push_back({ 3, 5 });
    node_weights.push_back({ 4, 4 });
    graph[1].push_back(2);
    graph[1].push_back(3);
    graph[2].push_back(4);
    graph[3].push_back(4);

    // 根据节点权重进行排序
    sort(node_weights.begin(), node_weights.end(),
        [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; });

    // 执行拓扑排序
    vector<int> sorted_nodes = topologicalSort(n, graph);

    // 输出排序结果
    for (int node : sorted_nodes) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}