#include <iostream>
#include <map>
// 找最小 窗口度量：窗口内特定元素数目满足要求

bool shouldShrink(std::map<char,int> src_map,std::map<char,int> target_map){
    for(auto c:target_map){
      auto dir = c.first;
      auto cnt = c.second;
      if(src_map[dir]<cnt){
        return false;
      }
    }
    return true;
}
int main() {
  std::string input;
  std::cin >> input;
  // 求出要求先
  std::map<char, int> input_map;
  if (input.size() % 4 != 0) {  // 疑问 不满足要求输出什么
    std::cout << "-1" << std::endl;
    return 0;
  }
  for (int i = 0; i < input.size(); i++) {
    input_map[input[i]]++;
  }
  if (input_map['A'] == input_map['S'] && input_map['A'] == input_map['D'] &&
      input_map['A'] == input_map['W']) {
    std::cout << "0" << std::endl;
    return 0;
  }
  std::map<char,int> target_map;
  int right_cnt = input.size()/4;
  for(auto c:input_map){
    auto cnt = c.second;
    if(cnt > right_cnt){
      target_map[c.first]=cnt-right_cnt;
    }
  }
  
  std::map<char,int> cur_map;
  int left =0;
  int min_lenth =input.size()+1;
  for (int right = 0; right < input.size(); right++){
    cur_map[input[right]]++;
    while(shouldShrink(cur_map,target_map)){
        min_lenth = std::min(min_lenth,right-left+1);//疑问：left和right的区间关系
        cur_map[input[left]]--;
        left++;
    }
  }
  std::cout << min_lenth << std::endl;
  return 0;
} 