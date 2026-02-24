#include <iostream>
#include <queue>
#include <vector>
std::vector<std::vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

void bfs(std::vector<std::vector<int>> grid,
         std::vector<std::vector<bool>>& visited, int x, int y, int& area) {
  std::queue<std::pair<int, int>> queue;
  queue.push({x, y});
  visited[x][y] = true;
  area++;
  while (!queue.empty()) {
    auto front = queue.front();
    queue.pop();
    for (int i = 0; i < 4; i++) {
      auto new_x = front.first + dir[i][0];
      auto new_y = front.second + dir[i][1];
      if (new_x >= 0 && new_x < grid.size() && new_y >= 0 &&
          new_y < grid[0].size() && visited[new_x][new_y] == false &&
          grid[new_x][new_y] == 1) {
        queue.push({new_x,new_y});
        area++;
        visited[new_x][new_y]=true;
      }
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> grid(n, std::vector<int>(m, 0));
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> grid[i][j];
    }
  }
  int result = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (visited[i][j] == false && grid[i][j] == 1) {
        int area = 0;
        bfs(grid, visited, i, j, area);
        result = std::max(result, area);
      }
    }
  }
  std::cout << result << std::endl;
  return 0;
}