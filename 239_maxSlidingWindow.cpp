#include "common.hpp"
class MyQueue { // 单调队列（从大到小）
public:
    deque<int> que; // 使用deque来实现单调队列
    // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
    // 同时pop之前判断队列当前是否为空。
    void pop(int value)
    {
        if (!que.empty() && value == que.front()) {
            que.pop_front();
        }
    }
    // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
    // 这样就保持了队列里的数值是单调从大到小的了。
    void push(int value)
    {
        while (!que.empty() && value > que.back()) {
            que.pop_back();
        }
        que.push_back(value);
    }
    // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
    int front() { return que.front(); }
};

int main()
{
    vector<int> nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
    int k = 3;
    vector<int> res;
    MyQueue que;
    for (int i = 0; i < nums.size(); i++) {
        if (i < k - 1) {
            que.push(nums[i]);
        } else {
            que.push(nums[i]);
            res.push_back(que.front());
            que.pop(nums[i - k + 1]);
        }
    }
    cout << "Sliding window maximum: " << res << endl;
    return 0;
}