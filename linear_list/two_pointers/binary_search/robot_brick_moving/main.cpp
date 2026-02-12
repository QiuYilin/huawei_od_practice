#include <iostream>
#include <algorithm>

#include <vector>
#include <cmath>
bool isValid(std::vector<int> bricks,int energy){
  int count = 0;
  for(int i=0;i<bricks.size();i++){
    count+=std::ceil((float)bricks[i]/energy);
    if(count >  8){
      return false;
    }
  }
  return true;
}

int main(){
  std::vector<int> bricks;
  std::string brick;
  while(std::cin >> brick){
    bricks.push_back(std::stoi(brick));
  }
  if(bricks.size()>8){
    std::cout << "-1" << std::endl;
    return 0;
  }
  int l=0;
  int r=*std::max_element(bricks.begin(),bricks.end());
  int result =0;
  while(l<=r){
    int mid = l+(r-l)/2;
    if(isValid(bricks,mid)){
      r=mid-1;
      result = mid;
    }
    else{
      l=mid+1;
    } 
  }
  std::cout << result << std::endl;
  return 0;
}