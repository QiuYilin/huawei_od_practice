#include <iostream>
#include <queue>
#include <vector>

int main() {
  int m,n,k;
  std::cin >> m >> n >> k;
  std::vector<std::vector<int>> grid(m,std::vector<int>(n,0));
  std::vector<std::vector<bool>> visited(m,std::vector<bool>(n,false));
  for(int i=0;i<m;i++){
    for(int j=0;j<n;j++){
      std::cin >> grid[i][j];
    }
  }
  int peak =grid[0][0];//REVIEW 
  int min_path = 0;
  int path = 0;
  std::queue<std::pair<int,int>> queue;
  queue.push({0,0});
  visited[0][0]=true;
  std::vector<std::vector<int>> dir{{0,1},{0,-1},{-1,0},{1,0}};
  while(!queue.empty()){
    path++;
    int size = queue.size();
    for(int i=0;i<size;i++){
      auto front = queue.front();
      queue.pop();
      for(int j=0;j<4;j++){
        auto new_x = front.first+dir[j][0];//REVIEW 注意j
        auto new_y = front.second+dir[j][1];
        if(new_x>=0&&new_x<m&&new_y>=0&&new_y<n
          &&std::abs(grid[new_x][new_y]-grid[front.first][front.second])<=k 
          &&visited[new_x][new_y]==false){
          queue.push({new_x,new_y});
          visited[new_x][new_y]=true;
          if(grid[new_x][new_y]>peak){
            peak=grid[new_x][new_y];
            min_path= path;
          }
        }
      }
    }
  }
  std::cout << peak << " " << min_path << std::endl;
  return 0;
}