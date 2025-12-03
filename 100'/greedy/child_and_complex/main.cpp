#include <iostream>
#include <sstream>
#include <vector>
#include <map>

//题意：题目应该修改为班级至少有多少人 并不是所有小朋友都填了
//规律 相同数字的人可能在同一个小区
int main() {
  std::string line;
  std::getline(std::cin,line);
  std::stringstream ss(line);
  std::vector<int> input;
  int number = 0;
  while(ss>>number){
    input.push_back(number);
  }
  std::map<int,int> map;

  for(int i=0;i<input.size();i++){
    map[input[i]]++;
  }
  int result = 0;
  for(auto pair:map){
    int n = pair.first;
    int cnt = pair.second;
    result += std::ceil((double)cnt/(n+1))*(n+1);
  }

  std::cout << result << std::endl;
  return 0;
}


