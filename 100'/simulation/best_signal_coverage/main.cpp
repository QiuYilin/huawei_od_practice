#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
// 审题
// 有信号衰减
// 坐标是只能在AP里选还是什么意思
// REVIEW 怎么遍历所有坐标: REVIEW {0,0}->{xMax,yMax}简化 考虑交叉区域比较麻烦
int getDistance(std::vector<int>& coord, std::vector<int>& tower) {
  int xDistance = std::abs(coord[0] - tower[0]);
  int yDistance = std::abs(coord[1] - tower[1]);
  return std::max(xDistance, yDistance);
}

std::vector<int> getBestCoord(std::vector<std::vector<int>> & towers,int radius){
  int xMax = INT_MIN,yMax = INT_MIN;
  for(auto &&tower : towers){
    int x = tower[0],y=tower[1];
    xMax = std::max(xMax,x);
    yMax = std::max(yMax,y);
  }
  int targetX = 0,targetY = 0;
  int maxQuality = 0;
  for(int x = 0;x<=xMax;x++){
    for(int y=0;y<=yMax;y++){
      std::vector<int> cood = {x,y};
      int quality =0;
      for(auto && tower:towers){
        int distance = getDistance(cood,tower);
        if(distance <= radius){
          quality += floor((double)tower[2]/(1+distance));
        }
      }
      if(quality > maxQuality){
        maxQuality = quality;
        targetX = x;
        targetY = y;
      }
    }
  }
  return {targetX,targetY};
}

int main() {
  int N, D;
  std::cin >> N >> D;
  std::vector<std::vector<int>> towers(N);
  for (int i = 0; i < N; i++) {
    int x, y, s;
    std::cin >> x >> y >> s;
    towers[i] = {x, y, s};
  }
  // 获取最大坐标
  std::vector<int> res = get return 0;
}