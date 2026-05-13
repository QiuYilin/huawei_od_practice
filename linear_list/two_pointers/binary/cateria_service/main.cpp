#include <iostream>

#include <vector>
bool isValid(std::vector<int> people,int m,int mid){
  int rest = m;
  for(int i=0;i<people.size();i++){
    if(rest<people[i]){
      return false;
    }
    rest=rest-people[i]+mid;
  }
  return true;
}

int main(){
  int n =0;
  std::cin >> n;
  int m =0;
  std::cin >> m;
  std::vector<int> people(n);
  for(int i=0;i<n;i++){
    std::cin >> people[i];
  }
  int l=0;
  int r=100;
  while(l<r){
    int mid = l+(r-l)/2;
    if(isValid(people,m,mid)){
      r=mid;
    }
    else{
      l=mid+1;
    }
  }
  std::cout << l << std::endl;
  return 0;
}