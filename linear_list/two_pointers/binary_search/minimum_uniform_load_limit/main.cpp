#include <iostream>

#include <vector>
#include <algorithm>
#include <numeric>//求和头文件
bool isValid(std::vector<int> goods,int limit,int k){
  int count = 0;
  int cur = 0;
  for(int i=0;i<goods.size();i++){
    if(goods[i] > limit){
      return false;
    }
    cur+=goods[i];
    if(cur>limit){
      count++;
      cur = goods[i];
    }
  }
  if(cur > 0){
    count++;
  }
  return count <=k;//REVIEW 顺序装包的模板
}

int minLoad(std::vector<int> goods,int k){
  int l =0;
  int r =std::accumulate(goods.begin(),goods.end(),0);
  int result = 0;
  while(l<=r){
    int mid = l+(r-l)/2;
    if(isValid(goods,mid,k)){
      result = mid;
      r=mid-1;
    }
    else{
      l=mid+1;
    }
  }
  return result;
}

int main(){
  int n = 0;
  std::cin >> n;
  std::vector<int> goods(n);
  std::vector<int> types(n);

  for(int i=0;i<n;i++){
    std::cin >> goods[i];
  }
  for(int i=0;i<n;i++){
    std::cin >> types[i];
  }

  int k=0;
  std::cin >> k;

  std::vector<int> dry;
  std::vector<int> wet;

  for(int i=0;i<types.size();i++){
    if(types[i]==0){
      dry.push_back(goods[i]);
    }  
    else{
      wet.push_back(goods[i]);
    }
  }

  int result = std::max(minLoad(dry,k),minLoad(wet,k));
  std::cout << result << std::endl;
  return 0;
}