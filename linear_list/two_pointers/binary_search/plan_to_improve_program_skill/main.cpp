#include <iostream>
#include <sstream>
#include <string>

#include <algorithm>
//审题 一天看一次答案 有序。用模拟方法
bool isValid(std::vector<int> time,int mid,int m){
  int cur =0;
  int count =0;
  for(int i=0;i<time.size();i++){
    if(time[i]>mid){
      return
    }
  }
}
int main(){
  std::string input;
  std::getline(std::cin,input);
  std::string m;
  std::cin >> m;
  std::stringstream ss(input);
  std::vector<int> time;
  std::string e;
  while(std::getline(ss,e,',')){
    time.push_back(std::stoi(e));
  }
  int l =0;
  int r =24;//疑问 怎么求和
  int result = 24;
  while(l<=r){
    int mid = l+(r-l)/2;
    if(isValid(time,mid,m)){
      result = mid;
      r=mid-1;
    }
    else{
      l=mid+1;
    }
  }
  std::cout << result << std::endl;
  return 0;
}