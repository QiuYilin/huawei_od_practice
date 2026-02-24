#include <iostream>
#include <vector>
#include <queue>
// 最短路径问题
int main() {
  int target_x, target_y;
  std::cin >> target_x >> target_y;
  int m, n;
  std::cin >> m >> n;
  std::vector<std::vector<int>> grid(m, std::vector<int>(n, 0));
  std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> grid[i][j];
    }
  }

  std::queue<std::pair<int, int>> queue;
  queue.push({0, 0});
  visited[0][0] = true;
  int count = 0;
  std::vector<std::vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
  // 什么时候需要count辅助计数
  while (!queue.empty()) {
    int size = queue.size();
    count++;
    for (int i = 0; i < size; i++) {
      auto coor = queue.front();
      queue.pop();
      for (int i = 0; i < 4; i++) {
        auto new_x = coor.first + dir[i][0];
        auto new_y = coor.second + dir[i][1];
        if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n &&
            visited[new_x][new_y] ==false &&grid[new_x][new_y]==0) {
            queue.push({new_x,new_y});
            visited[new_x][new_y]=true;
            if(new_x==target_x&&new_y==target_y){
               std::cout << count << std::endl;
               return 0;
            }
        }
      }
    }
  }

  std::cout << -1 << std::endl;

  return 0;
}