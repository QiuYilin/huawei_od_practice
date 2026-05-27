#include <iostream>
#include <string>

#include <regex>
//审题 提取坐标
int main(){
  std::string input;
  std::cin >> input;
  std::regex pattern(R"(\((\d+),(\d+)\))");
  std::sregex_iterator begin(input.begin(),input.end(),pattern);//REVIEW 用sregex_token进一步提取x,y坐标
  std::sregex_iterator end{};
  std::vector<std::pair<int,int>> coors;
  for(auto it =begin;it!=end;it++){
    auto match = *it;
    if(match[1].str()[0]=='0'&&match[1].str().size()>1
      ||match[2].str()[0]=='0'&&match[2].str().size()>1){
      continue;
    }
    int x = std::stoi(match[1].str());//REVIEW 01 怎么处理
    int y = std::stoi(match[2].str());
    if(x>0&&x<1000&&y>0&&y<1000){
        coors.push_back({x,y});//REVIEW match到str需要转换
    }
  }
  if(coors.empty()){
    std::cout << "(0,0)" << std::endl;
  }
  else{
    int max = 0;
    int r_x=0;
    int r_y=0;
    for(int i=0;i<coors.size();i++){
      int x = coors[i].first;
      int y = coors[i].second;
      if(x*x+y*y>max){
        r_x = x;
        r_y = y;
        max = x*x+y*y;
      }
    }
    std::cout << "(" << r_x << "," << r_y << ")" << std::endl;
  }
}