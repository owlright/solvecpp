#include "sort_algos.hpp"
/* 快速排序v1 最左边为pivot */
void quickSort(vector<int>& nums, int left, int right)
{
    if (left >= right)
        return;
    // cout << left << " " << right << endl;
    int i = left, j = right, base = nums[left];
    while (i < j) {
        while (i < j && nums[j] > base) // 从右往左找到第一个小于 base 的元素
            j--;
        while (i < j && nums[i] <= base) // 从左往右找到第一个大于 base 的元素
            i++;
        // if (i != j)
        swap(nums[i], nums[j]);
    }
    swap(nums[left], nums[j]);
    quickSort(nums, left, i - 1);
    quickSort(nums, i + 1, right);
}
/* -------------------------------------------------------------------------- */
int partitionRandom(vector<int>& nums, int left, int right)
{
    int pivotIndex = (left + right) >> 1;
    swap(nums[pivotIndex], nums[left]);
    int pivot = nums[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[j] >= pivot)
            j--;
        while (i < j && nums[i] <= pivot)
            i++;
        swap(nums[i], nums[j]);
    }
    swap(nums[i], nums[left]);
    return i;
}

void quickSort2(vector<int>& nums, int left, int right)
{
    if (left >= right)
        return;
    // cout << left << " " << right << endl;
    auto index = partitionRandom(nums, left, right);
    quickSort2(nums, left, index - 1);
    quickSort2(nums, index + 1, right);
}

void quickSort3(vector<int>& nums, int left, int right)
{
    while (left < right) {
        auto index = partitionRandom(nums, left, right);
        if (index - left < right - index) {
            quickSort3(nums, left, index - 1);
            left = index + 1;
        } else {
            quickSort3(nums, index + 1, right);
            right = index - 1;
        }
    }
}
