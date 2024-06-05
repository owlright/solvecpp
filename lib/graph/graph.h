#pragma once
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>
#define ASSERT(x) assert(x)

namespace simnet {
template <typename T> using Mat = std::vector<std::vector<T>>;
using std::list;
using std::make_pair;
using std::map;
using std::pair;
using std::queue;
using std::stack;
using std::unordered_set;
using std::vector;

class Graph {
public:
    using Edge = pair<int, int>;
    using EdgeWeight = pair<int, double>;

public:
    void add_edge(int src, int dest, double weight = 1.0, bool bidirectional = false);
    void set_weight(int src, int dest, double weight = 1.0);
    void remove_edge(int src, int dest);
    void add_node(int n);
    void remove_node(int n);
    bool has_node(int n) const;
    bool has_edge(const int& src, const int& dest) const;
    bool has_edge(const Edge&) const;

    void update_dist();
    double distance(int src, int dest) const;
    double weight(int src, int dst) const;
#pragma warning(disable : 4267) // “return”: 从“size_t”转换到“int”，可能丢失数据
    int get_vertices_number() const
    {
        return adjout.size();
    }
    int get_max_vertice() const
    {
        return max_vertice;
    }
#pragma warning(default : 4267)
    double get_cost() const;

public:
    /**
     * graph algorithms
     */
    vector<int> dfs(int root, bool directionOut = true) const;
    vector<int> bfs(int root, bool directionOut = true) const;
    bool is_tree() const;
    bool is_connected() const;

public:
    bool operator==(const Graph& other) const
    {
        if (adjout.size() != other.adjout.size())
            return false;
        for (const auto& [src, vw1] : adjout) {
            auto it = other.adjout.find(src);
            if (it == other.adjout.end()) {
                return false;
            }
            auto& vw2 = it->second;
            if (vw1.size() != vw2.size()) {
                return false;
            }
            std::unordered_set<int> s1;
            std::unordered_set<int> s2;
            for (auto i = 0; i < vw1.size(); i++) {
                s1.insert(vw1[i].first);
                s2.insert(vw2[i].first);
            }
            if (s1 != s2) {
                return false;
            }
        }
        return true;
    };
    struct Hash {
        size_t operator()(const Graph& graph) const
        {
            size_t hash = 0;
            for (const auto& node : graph.nodes) {
                // 基于键和值的哈希值计算
                hash ^= std::hash<int>()(node);
            }
            return hash;
        }
    };

public:
    const vector<int>& get_nodes() const
    {
        return nodes;
    }
    double** get_dist() const;
    const vector<EdgeWeight>& out_neighbors(int src) const
    {
        if (adjout.find(src) != adjout.end()) {
            return adjout.at(src);
        } else {
            return emptyEdge;
        }
    }
    const vector<EdgeWeight>& in_neighbors(int src) const
    {
        if (adjin.find(src) != adjin.end()) {
            return adjin.at(src);
        } else {
            return emptyEdge;
        }
    }
#pragma warning(disable : 4267)
    int indegree(int v) const
    {
        ASSERT(adjin.find(v) != adjin.end());
        return adjin.at(v).size();
    }
    int outdegree(int v) const
    {
        ASSERT(adjout.find(v) != adjout.end());
        return adjout.at(v).size();
    }
#pragma warning(default : 4267)
public:
    // void draw(const char* filename, const char* engine = "neato");

public:
    explicit Graph();
    ~Graph();
    Graph(const Graph& other);
    // assign constructor;
    // Graph a, b
    // a = b will call this;
    Graph& operator=(const Graph& other);
    // Move constructor
    Graph(Graph&& other);
    // Move assignment operator
    // auto a = getNetworkCopy() will call this
    Graph& operator=(Graph&& other);

private:
    double** dist { nullptr };
    std::vector<int> nodes;
    int max_vertice { -1 };
    map<int, vector<EdgeWeight>> adjout;
    map<int, vector<EdgeWeight>> adjin;
    vector<EdgeWeight> emptyEdge;
};
}
