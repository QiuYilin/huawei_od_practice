#include <iostream>
#include <vector>
// 深广搜
std::vector<std::vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
void dfs(std::vector<std::vector<int>> grid,
         std::vector<std::vector<bool>>& visited, int x, int y, int& area,
         int& entry, std::pair<int, int>& coor) {
  visited[x][y] = true;
  area++;
  if (x == 0 || x == grid.size() - 1 || y == 0 || y == grid[0].size() - 1) {
    entry++;
    coor = {x, y};
  }
  for (int i = 0; i < 4; i++) {
    auto new_x = x + dir[i][0];
    auto new_y = y + dir[i][1];
    if (new_x >= 0 && new_x < grid.size() && new_y >= 0 &&
        new_y < grid[0].size() && visited[new_x][new_y] == false &&
        grid[new_x][new_y] == 1) {
      dfs(grid, visited, new_x, new_y, area, entry, coor);
    }
  }
}
int main() {
  int m = 0, n = 0;
  std::cin >> m >> n;
  std::vector<std::vector<int>> grid(m, std::vector<int>(n, 0));
  std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::string cur;
      std::cin >> cur;
      if (cur == "O") {
        grid[i][j] = 1;
      }
    }
  }
  int result = 0;
  int cnt = 0;
  std::pair<int, int> right_coor{0, 0};
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int area = 0;
      int entry = 0;
      if (grid[i][j] == 1 && visited[i][j] == false) {
        std::pair<int, int> coor{0, 0};
        dfs(grid, visited, i, j, area, entry, coor);
        if (entry == 1) {
          if (result < area) {
            result = area;
            right_coor = coor;
            cnt = 0;
          } else if (result == area) {
            cnt++;
          }
        }
      }
    }
  }
  if (result == 0) {
    std::cout << "NULL" << std::endl;
  } else if (cnt == 0) {
    std::cout << right_coor.first << " " << right_coor.second << " " << result
              << std::endl;
  } else {
    std::cout << result << std::endl;
  }

  return 0;
}