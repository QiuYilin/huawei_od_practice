#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
// 审题：棋盘格，最大岛屿面积
std::vector<std::vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

void bfs(std::vector<std::string> grid, std::vector<std::vector<bool>>& visited,
         int x, int y,int &result) {
  std::queue<std::pair<int,int>> queue;
  result+=grid[x][y]-'0';
  queue.push({x,y});
  visited[x][y]=true;

  while(!queue.empty()){
    auto top = queue.front();
    queue.pop();
    auto cur_x = top.first;
    auto cur_y = top.second;
    for(int i=0;i<4;i++){
      auto new_x = cur_x+dir[i][0];
      auto new_y = cur_y+dir[i][1];
      if(new_x>=0&&new_x<grid.size()
         && new_y>=0&&new_y<grid[0].size()
         && visited[new_x][new_y]==false
         && grid[new_x][new_y]!='0'){
        result+=grid[new_x][new_y]-'0';
        queue.push({new_x,new_y});
        visited[new_x][new_y]=true;
      }
    }
  }
}

int main() {
  std::string line;
  std::vector<std::string> grid;
  
  while (std::cin >> line) {//疑问 输入为什么不停止
    grid.push_back(line);
  }
  
  // int n=0;
  // std::cin >> n;
  // for (int i=0;i<n;i++) {//疑问 输入为什么不停止
  //   std::cin >> line;
  //   grid.push_back(line);
  // }

  int max_area = 0;

  std::vector<std::vector<bool>> visited(
      grid.size(), std::vector<bool>(grid[0].size(), false));
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if(grid[i][j]!='0'&&visited[i][j]==false){
        int area = 0;
        bfs(grid, visited, i, j,area);
        max_area = std::max(max_area,area);
      }
    }
  }
  std::cout << max_area << std::endl;
}