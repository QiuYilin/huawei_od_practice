#include <iostream>
#include <queue>
#include <vector>
std::vector<std::vector<int>> dir{{0, 1},  {0, -1},  {-1, 0}, {1, 0},
                                       {-1, 1}, {-1, -1}, {1, 1},  {1, -1}};

void bfs(int x, int y, std::vector<std::vector<int>>& grid) {
  std::queue<std::pair<int, int>> queue;
  queue.push({x, y});
  grid[x][y] = 0;
  while (!queue.empty()) {
    auto front = queue.front();
    queue.pop();
    for (int i = 0; i < 8; i++) {
      auto new_x = front.first + dir[i][0];
      auto new_y = front.second + dir[i][1];
      if (new_x >= 0 && new_x < grid.size() && new_y >= 0 &&
          new_y < grid[0].size() && grid[new_x][new_y] == 1) {
        queue.push({new_x, new_y});
        grid[new_x][new_y] = 0;
      }
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> grid(n, std::vector<int>(m, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> grid[i][j];
    }
  }

  // std::vector<std::vector<bool>> visited(n,std::vector<bool>(m,false));

  int count = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 1
          //&&visited[i][j]==false
      ) {
        count++;
        bfs(i, j, grid);
      }
    }
  }

  std::cout << count << std::endl;

  return 0;
}