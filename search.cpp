#include "common.hpp"

int binarySearch(vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return -1;
}

int main()
{
    vector<int> nums = { -1, 0, 3, 5, 9, 12 };
    int target = 9;
    cout << binarySearch(nums, target) << endl;
}