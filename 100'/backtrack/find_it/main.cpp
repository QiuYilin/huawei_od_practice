#include <iostream>
#include <vector>
// 审题
// REVIEW 棋盘路径 是一个需要枝去重的向四个方向探索的回溯
std::vector<std::vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
// 疑问 只有递归可以用返回值传递结果？
// REVIEW 因为是四个方向 要么在循环外处理当前点 要么确保初始点ok 在判断中处理新点
void dfs(std::pair<int, int> start, std::vector<std::vector<char>> grid,
         std::string word, int index, std::vector<std::vector<bool>> visited,bool& flag) {
  // 疑问 dfs处理当前点在循环之前？
  if (grid[start.first][start.second] != word[index]) {
    return;
  } else {
    if (index == word.size() - 1) {
      flag = true;
      return;
    }
  }
  for (int i = 0; i < 4; i++) {
    int new_x = start.first + dir[i][0];
    int new_y = start.second + dir[i][1];
    if (new_x >= 0 && new_x < grid.size() && new_y >= 0 &&
        new_y < grid[0].size()&&visited[new_x][new_y]==false) {
      visited[new_x][new_y]=true;
      dfs({new_x, new_y}, grid, word, index + 1,visited, flag);
      visited[new_x][new_y]=false;
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::string word; std::cin >> word;
  std::vector<std::vector<char>> grid(n, std::vector<char>(m));
  std::vector<std::pair<int, int>> entries;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> grid[i][j];
      if (grid[i][j] == word[0]) {
        entries.push_back({i, j});
      }
    }
  }
  if (entries.empty()) {
    std::cout << "NO" << std::endl;
    return 0;
  }
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m,false));
  for (int i = 0; i < entries.size(); i++) {
    bool flag = false;
    visited[entries[i].first][entries[i].second]=true;
    dfs(entries[i], grid, word, 0, visited,flag);
    if(flag){
      std::cout << entries[i].first+1 << " " << entries[i].second+1 << std::endl;
    }
  }
  return 0;
}
