#include <iostream>
#include <map>
#include <queue>
#include <random>

std::map<size_t, double> find_max_N(const std::map<size_t, double>& value_map, size_t N)
{

    std::priority_queue<std::pair<double, size_t>, std::vector<std::pair<double, size_t>>,
        std::greater<std::pair<double, size_t>>>
        max_heap;

    for (auto& p : value_map) {
        if (max_heap.size() < N) {
            max_heap.push(p);
        } else {
            if (p.second > max_heap.top().first) {
                max_heap.pop();
                max_heap.push(p);
            }
        }
    }

    std::map<size_t, double> result;
    while (!max_heap.empty()) {
        result[max_heap.top().second] = max_heap.top().first;
        max_heap.pop();
    }

    return result;
}

int main()
{
    std::map<size_t, double> value_map;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1000);

    for (size_t i = 0; i < 100; i++) {
        value_map[i] = dist(mt);
    }

    auto result = find_max_N(value_map, 100);

    std::cout << "Max 100 values: " << std::endl;
    for (auto& p : result) {
        std::cout << p.first << ": " << p.second << std::endl;
    }

    return 0;
}