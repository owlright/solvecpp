#include "sort_algos.hpp"

int main()
{
    // vector<int> nums { 3, 2, 1, 5, 6, 4 };
    // nums[0] = 3;
    // {
    //     Timer _;
    //     mergeSort(nums, 0, nums.size() - 1);
    //     cout << nums << endl;
    // }

    // bucketSort
    vector<float> nums { 0.3, 0.2, 0.1, 0.5, 0.6, 0.4 };
    {
        Timer _;
        bucketSort(nums);
        cout << nums << endl;
    }
    return 0;
}