#include <iostream>

#include <vector>
//REVIEW 用 longlong
long long dfs(std::vector<long long> pizza,int l,int r){
  if(l==r){
    return 0;
  }
  if(pizza[l]>pizza[r]){
    l=(l-1+pizza.size())%pizza.size();
  }
  else{
    r=(r+1)%pizza.size();
  }
  if(l==r){
    return pizza[l];
  }
  return std::max(dfs(pizza,(l-1+pizza.size())%pizza.size(),r)+pizza[l],dfs(pizza,l,(r+1)%pizza.size())+pizza[r]);
}

int main(){
  int n;
  std::cin >> n;
  std::vector<long long> pizza(n);
  for(int i=0;i<n;i++){
    std::cin >> pizza[i];
  }
  long long result = 0;
  for(int i=0;i<n;i++){
    result = std::max(result,dfs(pizza,(i-1+n)%n,(i+1)%n)+pizza[i]);
  }
  std::cout << result << std::endl;
  return 0;
}