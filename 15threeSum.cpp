#include "common.hpp"

class Solution {
public:
    // // Custom hash function for the tuple
    // struct TupleHash {
    //     std::size_t operator()(const std::tuple<int, int, int>& t) const
    //     {
    //         // Use std::hash to hash each element and combine them
    //         return std::hash<int>()(std::get<0>(t)) ^ std::hash<int>()(std::get<1>(t))
    //             ^ std::hash<int>()(std::get<2>(t));
    //     }
    // };

    // // Custom equality function for the tuple
    // struct TupleEqual {
    //     bool operator()(const std::tuple<int, int, int>& t1, const std::tuple<int, int, int>& t2) const
    //     {
    //         if (std::get<0>(t1) == std::get<0>(t2) && std::get<1>(t1) == std::get<1>(t2)
    //             && std::get<2>(t1) == std::get<2>(t2)
    //         return true;
    //     }
    // };

    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> result;
        unordered_map<int, tuple<int, int>> posRecord;
        unordered_map<int, unordered_map<int, unordered_set<int>>> valueRecord;

        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                posRecord[-(nums[i] + nums[j])] = std::make_tuple(i, j);

                for (int pos3 = j + 1; pos3 < nums.size(); pos3++) {
                    if (posRecord.find(nums[pos3]) != posRecord.end()) {
                        auto& another2 = posRecord[nums[pos3]];
                        auto pos1 = std::get<0>(another2);
                        auto pos2 = std::get<1>(another2);
                        if (valueRecord.find(nums[pos1]) != valueRecord.end()
                            && valueRecord[nums[pos1]].find(nums[pos2]) != valueRecord[nums[pos1]].end()) {
                            auto& usedValues = valueRecord[nums[pos1]][nums[pos2]];
                            if (usedValues.find(nums[pos3]) == usedValues.end()) { // the first time we this combination
                                result.emplace_back(vector<int> { nums[pos1], nums[pos2], nums[pos3] });
                                valueRecord[nums[pos1]][nums[pos2]].insert(nums[pos3]);
                                valueRecord[nums[pos2]][nums[pos1]].insert(nums[pos3]);
                            } else {
                                continue;
                            }
                        } else {
                            valueRecord[nums[pos1]][nums[pos2]] = unordered_set<int> { nums[pos3] };
                            valueRecord[nums[pos2]][nums[pos1]] = unordered_set<int> { nums[pos3] };
                            result.emplace_back(vector<int> { nums[pos1], nums[pos2], nums[pos3] });
                        }
                    }
                }
            }
        }

        return result;
    }
};

int main()
{
    vector<int> nums = { -1, 0, 1, 2, -1, -4 };
    Solution sol;
    cout << sol.threeSum(nums) << endl;
}