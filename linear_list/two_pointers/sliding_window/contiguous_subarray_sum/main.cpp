#include <iostream>
#include <vector>

int main() {
  int n, x;
  std::cin >> n >> x;
  std::vector<int> input(n);
  //std::vector<int> sum(n);
  for (int i = 0; i < n; i++) {
    std::cin >> input[i];
  }
  int l=0;
  int cur_sum = 0;
  int result = 0;
  for(int r=0;r<n;r++){
    cur_sum+=input[r];
    while(cur_sum>=x){
      result+=n-r;
      cur_sum-=input[l];
      l++;
    }
  }
  std::cout << result << std::endl;
  return 0;
}