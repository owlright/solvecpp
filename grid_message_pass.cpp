#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int shortestTime(vector<vector<int>>& grid, int m, int n, int j, int k)
{
    queue<pair<int, int>> q;
    q.push({ j, k });
    grid[j][k] = -1; // 标记已访问

    int time = 0;
    int dir[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nx = x + dir[d][0];
                int ny = y + dir[d][1];

                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != -1) {
                    if (grid[nx][ny] == 1)
                        q.push({ nx, ny }), grid[nx][ny] = -1;
                    else
                        q.push({ nx, ny }), grid[nx][ny] = -2; // 塔B需要2次循环
                }
            }
        }
        if (!q.empty())
            time++;
    }

    return time == 0 ? -1 : time - 1;
}

int main()
{
    // 输入网格
    return 0;
}