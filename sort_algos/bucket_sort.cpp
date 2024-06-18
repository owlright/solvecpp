#include "sort_algos.hpp"
#include <algorithm>
/* 桶排序 */
void bucketSort(vector<float> &nums) {
    // 初始化 k = n/2 个桶，预期向每个桶分配 2 个元素
    int k = nums.size() / 2;
    vector<vector<float>> buckets(k);
    // 1. 将数组元素分配到各个桶中
    for (float num : nums) {
        // 输入数据范围为 [0, 1)，使用 num * k 映射到索引范围 [0, k-1]
        int i = num * k;
        // 将 num 添加进桶 bucket_idx
        buckets[i].push_back(num);
    }
    // 2. 对各个桶执行排序
    for (vector<float> &bucket : buckets) {
        // 使用内置排序函数，也可以替换成其他排序算法
        std::sort(bucket.begin(), bucket.end());
    }
    // 3. 遍历桶合并结果
    int i = 0;
    for (vector<float> &bucket : buckets) {
        for (float num : bucket) {
            nums[i++] = num;
        }
    }
}

void test_bucketSort() {
    Timer _;
    vector<float> nums { 0.3f, 0.2f, 0.1f, 0.5f, 0.6f, 0.4f };
    bucketSort(nums);
    cout << nums << endl;
}