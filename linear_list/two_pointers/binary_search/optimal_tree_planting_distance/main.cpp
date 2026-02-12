#include <iostream>
#include <sstream>

#include <vector>
#include <cmath>
#include <algorithm>
//REVIEW 一棵树上有多少桃子要根据题目输入判定
bool isValid(std::vector<int> peach,int s,int target){
  int count = 0;  
  for(int i=0;i<peach.size();i++){
    count += std::ceil((float)peach[i]/s);
  }
  return count<=target;
}

int main(){
  std::string trees;
  std::getline(std::cin,trees);
  std::stringstream ss(trees);
  std::vector<int> peach;
  std::string e;
  while(ss>>e){
    peach.push_back(std::stoi(e));
  }
  int h;
  std::cin >> h;
  if(peach.size()<=0||peach.size()>=10000||h<=0||h>=10000||peach.size()>h){
    std::cout << 0 << std::endl;
    return 0;
  }
  int l=1;
  int r=*std::max_element(peach.begin(),peach.end());
  while(l<r){
    int mid = l+(r-l)/2;
    if(isValid(peach,mid,h)){
      r=mid;
    }
    else{
      l=mid+1;
    }
  }
  std::cout << l << std::endl;
  return 0;
}