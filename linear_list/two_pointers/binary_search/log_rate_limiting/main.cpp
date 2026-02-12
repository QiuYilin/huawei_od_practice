#include <iostream>

#include <vector>
#include <algorithm>
bool isValid(std::vector<int> records,int cur,int total){
  long long sum =0;//REVIEW sum 可能超大
  for(int i=0;i<records.size();i++){
    if(records[i]<=cur){
      sum+=records[i];
    }
    else{
      sum+=cur;
    }
  }
  return sum<=total;
}

int main(){
  int n;
  std::cin >> n;
  std::vector<int> records(n);
  for(int i=0;i<records.size();i++){
    std::cin >> records[i];
  } 
  int total;
  std::cin >> total;
  int l = 0;
  int max = *std::max_element(records.begin(),records.end());
  int r =max;
  int result = 0;
  while(l<=r){
    int mid = l+(r-l)/2;
    if(isValid(records,mid,total)){
      result = mid;
      l=mid+1;
    }
    else{
      r=mid-1;
    }
  }
  if(result==max){
    std::cout << -1 << std::endl;
  }
  else{
    std::cout << result << std::endl;
  }
  return 0;
}