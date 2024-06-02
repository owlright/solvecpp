#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
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
// using NodeWeight = unordered_map<int, int>;
using NodeWeight = vector<int>;
using NodeWeightPair = pair<int, int>;
struct NodeWeightCompare {
    bool operator()(const NodeWeightPair& a, const NodeWeightPair& b) const
    {
        return a.second < b.second;
    }
};
using NodeWeightQueue = priority_queue<NodeWeightPair, vector<NodeWeightPair>, NodeWeightCompare>;

vector<int> topologicalSort(int n, Graph& graph, NodeWeight& node_weights)
{
    // Initialize visited and indegree array
    vector<int> indegree(n + 1);
    vector<bool> visited(n + 1, false);
    for (const auto& [node, neighbors] : graph) {
        for (int neighbor : neighbors) {
            ++indegree[neighbor];
        }
    }

    NodeWeightQueue q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.push({ i, node_weights[i] });
        }
    }

    std::vector<int> result;
    while (!q.empty()) {
        auto [n, w] = q.top();
        q.pop();
        if (!visited[n]) {
            result.push_back(n);
            visited[n] = true;
            for (int neighbor : graph[n]) {
                --indegree[neighbor];
                if (indegree[neighbor] == 0) {
                    q.push({ neighbor, node_weights[neighbor] });
                }
            }
        }
    }

    return result;
}

int main()
{

    NodeWeight node_weights;
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
    node_weights.resize(n + 1);
    node_weights[1] = 2;
    node_weights[2] = 3;
    node_weights[3] = 5;
    node_weights[4] = 4;
    graph[1].push_back(2);
    graph[1].push_back(3);
    graph[2].push_back(4);
    graph[3].push_back(4);

    // 根据节点权重进行排序
    // sort(node_weights.begin(), node_weights.end(),
    //     [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; });

    // 执行拓扑排序
    vector<int> sorted_nodes = topologicalSort(n, graph, node_weights);

    // 输出排序结果
    for (int node : sorted_nodes) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}