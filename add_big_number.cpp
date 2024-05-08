#include <bits/stdc++.h>
using namespace std;
typedef struct _BigNumber {
    int d[5100]; // Why 5100?
    int len;
    _BigNumber()
    {
        memset(d, 0, sizeof(d));
        len = 0;
    }
} BigNumber;

std::ostream& operator<<(std::ostream& os, const BigNumber& bn)
{
    for (int i = bn.len - 1; i >= 0; i--) {
        os << bn.d[i];
    }
    return os;
}

BigNumber convert2BigNumber(const std::string& str)
{
    BigNumber bn;
    bn.len = str.size();
    // Iterate through each character in the string
    for (int i = 0; i < bn.len; i++) {
        // Convert the character to an integer and store it in the BigNumber array reversely
        bn.d[i] = str[bn.len - i - 1] - '0';
    }
    return bn;
}

string add(BigNumber a, BigNumber b)
{
    BigNumber c;
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len; i++) {
        auto temp = a.d[i] + b.d[i] + carry;
        c.d[c.len++] = temp % 10; // 当前位结果
        carry = temp / 10; // 下一位进位
    }
    if (carry) {
        c.d[c.len++] = carry;
    }
    // ! Works only if you implement the operator<< for BigNumber
    // std::stringstream res; // Create a std::stringstream object
    // res << c;
    string res;
    for (int i = c.len - 1; i >= 0; i--) {
        res += std::to_string(c.d[i]);
    }
    return res;
}

int main()
{
    std::string a = "1234562847890"; // replace with the number you want to convert
    string b = "987654321055448";
    auto bn1 = convert2BigNumber(a);
    auto bn2 = convert2BigNumber(b);
    cout << add(bn1, bn2) << endl;
    return 0;
}