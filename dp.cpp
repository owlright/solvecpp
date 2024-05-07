#include <bits/stdc++.h>
using namespace std;
int main()
{
    int M = 3;
    int N = 4;
    // cin >> M >> N;
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    vector<vector<int>> dp(M, vector<int>(N+1, 0));
    // for (int i = 0; i < M; i++) {
    //     cin >> weight[i];
    // }
    // for (int i = 0; i < M; i++) {
    //     cin >> value[i];
    // }
    for (int j = weight[0]; j <= N; j++) {
        dp[0][j] = value[0];
    }
    for (int i = 1; i < M; i++) { // 遍历物品
        for (int j = 0; j <= N; j++) { // 遍历容量
            if (j >= weight[i]) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j <= N; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << dp[M-1][N] << endl;
}