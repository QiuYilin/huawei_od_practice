#include <iostream>

#include <vector>

#include <algorithm>
int main(){
  int weight,people_n;
  std::cin >> weight >> people_n;
  std::vector<int> p_weights(people_n);
  for(int i=0;i<people_n;i++){
    std::cin >> p_weights[i];
  }
  //疑问 对撞指针的模板
  std::sort(p_weights.begin(),p_weights.end());
  int l=0,r=people_n-1;
  int result = 0;
  while(l<=r){//疑问边界
    if(l==r){
      result++;
      break;
    }
    if(p_weights[l]+p_weights[r]<=weight){
      result++;
      l++;
      r--;
    }
    else if(p_weights[l]<p_weights[r]){
      result++;
      r--;
    }
    else{
      result++;
      l++;
    }
  }
  std::cout << result << std::endl;
  return 0;
}