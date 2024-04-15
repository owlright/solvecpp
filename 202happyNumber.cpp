#include "common.hpp"
class Solution {
public:
    int getSum(int n)
    {
        int sum = 0;
        int curDigit = 0;
        while (n ) {
            curDigit = n % 10;
            sum += curDigit * curDigit;
            n = n / 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> used;
        while ( n != 1 && used.find(n) == used.end()) {
            used.insert(n);
            n = getSum(n);
        }
        return n == 1;
    }
};
int main()
{
    Solution solution;
    int n = 19;
    cout << solution.isHappy(n) << endl;
    return 0;
}