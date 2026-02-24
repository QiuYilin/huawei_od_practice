#include <iostream>
#include <vector>
#include <queue>

int main(){
  int n,m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> grid(n,std::vector<int>(m,0));
  //std::vector<std::vector<bool>> visited(n,std::vector<bool>(m,false));
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      std::cin >> grid[i][j];
    }
  }
  std::queue<std::pair<int,int>> queue;
  grid[0][0]=1;
  queue.push({0,0});
  std::vector<std::vector<int>> dir{{0,1},{0,-1},{-1,0},{1,0}};
  while(!queue.empty()){
    auto front = queue.front();
    queue.pop();
    for(int i=0;i<4;i++){
      auto new_x = front.first+dir[i][0];
      auto new_y = front.second+dir[i][1];
      if(new_x>=0&&new_x<n&&new_y>=0&&new_y<m
         &&grid[new_x][new_y]==0){
        grid[new_x][new_y]=1;
        queue.push({new_x,new_y});
      }
    }
  }
  int result = 0;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if(grid[i][j]==0||grid[i][j]==2){
        result++;
      }
    }
  }
  std::cout << result << std::endl;
  return 0;
}