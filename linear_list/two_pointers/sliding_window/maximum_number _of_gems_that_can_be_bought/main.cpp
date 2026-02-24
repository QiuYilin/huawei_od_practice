#include <iostream>
#include <vector>

int main(){
  int n;
  std::cin >> n;
  std::vector<int> gem(n);
  for(int i=0;i<n;i++){
    std::cin >> gem[i];
  }
  int v;
  std::cin >> v;
  int l = 0;
  int length = 0;
  int max_length=0;
  int sum=0;
  for(int r=0;r<n;r++){
    length++;
    sum+=gem[r];
    while(sum>v){
      length--;
      sum-=gem[l];
      l++;
    }
    max_length=std::max(max_length,length);
  }
  std::cout << max_length << std::endl;
  return 0;
}