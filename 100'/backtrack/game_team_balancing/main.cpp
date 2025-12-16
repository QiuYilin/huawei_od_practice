#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
// 审题 n是偶数
// 组合问题 Cn / n/2 < 2^24
// 01背包？ 最接近sum/2？ 疑问 背包问题的时间复杂度 但是要求了必须取一半

//剪枝
void backtrack(std::vector<int> input,int k,std::vector<int>& path, std::vector<int>& paths,
               int index,int sum) {
  if(path.size()==k){
    paths.push_back(sum);
    return;
  }
  for(int i=index;i<input.size();i++){
    path.push_back(input[i]);
    sum+=input[i];
    backtrack(input,k,path,paths,i+1,sum);
    path.pop_back();
    sum-=input[i];
  }
}

int main() {
  std::string line;
  std::getline(std::cin, line);

  std::vector<int> input;
  std::stringstream ss(line);
  int val;
  while (ss >> val) {
    input.push_back(val);
  }

  int n = input.size();
  int k = n / 2;
  int sum =0;
  for(int i=0;i<input.size();i++){
    sum+=input[i];
  }
  std::vector<int> path; 
  std::vector<int> sums;
  backtrack(input,k,path,sums,0,0);
  int min_d = INT_MAX;
  for(int i=0;i<sums.size();i++){
    int other = sum-sums[i];
    int d = std::abs(other-sums[i]);
    min_d=std::min(min_d,d);
  }
  std::cout << min_d << std::endl;
  return 0;
}