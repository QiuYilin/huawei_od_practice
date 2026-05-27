#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

vector<vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

void dfs(int& result, pair<int, int> start, pair<int, int> end,
         const vector<vector<int>>& grid, vector<vector<bool>> visited, int k) {
  if (start.first == end.first && start.second == end.second) {
    result++;
    return;
  }
  for (int i = 0; i < dir.size(); i++) {
    auto new_x = start.first + dir[i][0];
    auto new_y = start.second + dir[i][1];
    if (new_x >= 0 && new_x < grid.size() && new_y >= 0 &&
        new_y < grid[0].size() && visited[new_x][new_y] == false &&
        grid[new_x][new_y] - grid[start.first][start.second] <= k &&
        grid[new_x][new_y] - grid[start.first][start.second] >= 0) {
      visited[new_x][new_y] = true;
      dfs(result, {new_x, new_y}, end, grid, visited, k);
      visited[new_x][new_y] = false;
    }
  }
}

int cal(int n, int m, int k, vector<vector<int>>& grid) {
  pair<int, int> start;
  pair<int, int> end;
  int lowest = INT_MAX;
  int highest = INT_MIN;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] > highest) {
        highest = grid[i][j];
        end = {i, j};
      }
      if (grid[i][j] < lowest) {
        lowest = grid[i][j];
        start = {i, j};
      }
    }
  }
  int result = 0;
  vector<vector<bool>> visited(n, vector<bool>(m, false));
  visited[start.first][start.second] = true;
  dfs(result, start, end, grid, visited, k);
  return result;
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> grid(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> grid[i][j];
    }
  }

  int res = cal(n, m, k, grid);
  cout << res;
  return 0;
}
