#include <iostream>

#include <vector>
bool dfs(std::vector<std::vector<int>> &grid,int x,int y){
  if(x==grid.size()-1&&y==grid[0].size()-1){
    if(grid[x][y]!=-1){
        grid[x][y]=1;
        return true;
    } 
    else{
        return false;
    }
  }
  if(x<0||x>=grid.size()||y<0||y>=grid[0].size()){
    return false;
  }
  if(grid[x][y]==-1){//墙
    return false;
  }
  if(grid[x][y]==1){
    return true;
  }
  if(grid[x][y]==2){
    return false;
  }
  //疑问 怎么避免重复
  bool up = dfs(grid,x,y+1);
  bool right = dfs(grid,x+1,y);
  if(up||right){
    grid[x][y]=1;
  }
  else{
    grid[x][y]=2;//死路
  }
  return up||right;
}

int main(){
  int x,y;
  std::cin >> x>>y;
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> grid(x,std::vector<int>(y,0));
  for(int i=0;i<n;i++){
    int a,b;
    std::cin >> a >> b;
    grid[a][b]=-1;
  }
  dfs(grid,0,0);
  int trap=0,untouch=0;
  for(int i=0;i<x;i++){
    for(int j=0;j<y;j++){
      if(grid[i][j]==0){
        untouch++;
      }
      else if(grid[i][j]==2){
        trap++;
      }
    }
  }
  std::cout << trap << " " << untouch << std::endl;
  return 0;
}