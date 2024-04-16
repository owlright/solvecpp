#pragma once
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
using namespace std::chrono;
template <typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i != vec.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}
#define HOUR_IN_MICROSECONDS (3600 * 1000000LL)
#define MINUTE_IN_MICROSECONDS (60 * 1000000)
#define SECOND_IN_MICROSECONDS 1000000
#define MILLI_IN_MICROSECONDS 1000
class Timer {
private:
    time_point<high_resolution_clock> start_time;

public:
    Timer() : start_time(high_resolution_clock::now()) { }

    ~Timer()
    {
        auto end_time = high_resolution_clock::now();
        auto totalTime = duration_cast<microseconds>(end_time - start_time).count();
        auto hours_ = totalTime / HOUR_IN_MICROSECONDS;
        auto minutes_ = (totalTime - hours_ * HOUR_IN_MICROSECONDS) / MINUTE_IN_MICROSECONDS;
        auto seconds_
            = (totalTime - hours_ * HOUR_IN_MICROSECONDS - minutes_ * MINUTE_IN_MICROSECONDS) / SECOND_IN_MICROSECONDS;
        auto milliseconds_ = (totalTime - hours_ * HOUR_IN_MICROSECONDS - minutes_ * MINUTE_IN_MICROSECONDS
                                 - seconds_ * SECOND_IN_MICROSECONDS)
            / MILLI_IN_MICROSECONDS;

        cout << hours_ << "h " << minutes_ << "min " << seconds_ << "s " << milliseconds_ << "ms " << totalTime % 1000
             << "us" << endl;
    }
};

// Function wrapper to measure execution time for functions with any number of arguments
template <typename F, typename... Args> void measureTime(F&& func, Args&&... args)
{
    auto start = high_resolution_clock::now();
    std::invoke(std::forward<F>(func), std::forward<Args>(args)...);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Function execution time: " << duration << " milliseconds" << endl;
}

struct ListNode;
void printLinkedList(ListNode* head);
ListNode* createLinkedList(vector<int> nums);