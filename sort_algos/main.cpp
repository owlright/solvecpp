#include "sort_algos.hpp"

int main()
{
    vector<int> nums { 3, 2, 1, 5, 6, 4 };
    nums[0] = 3;
    {
        Timer _;
        mergeSort(nums, 0, nums.size() - 1);
        cout << nums << endl;
    }

    return 0;
}