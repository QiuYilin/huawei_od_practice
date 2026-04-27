#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
//REVIEW  查找和排序
//REVIEW  字符串操作 查找 切割 拼接 插入？
int main(){
  //①在目标目录内
  //②统计一级文件总和
  std::string target_dir;
  std::cin >> target_dir;
  std::cin.ignore();
  //REVIEW cin要遇到文件终止符才会停止 典型情况就是自己简单输入文本 换行之后程序不会输出
  std::string line;
  std::getline(std::cin,line);
  std::string e;
  std::stringstream ss(line);
  std::vector<std::pair<std::string,int>> inputs;
  while(ss>>e){
    inputs.push_back({e,0});
  }
  for(int i=0;i<inputs.size();i++){
    int s;
    std::cin >> s;
    inputs[i].second = s;
  }

  std::map<std::string,int> indicates;

  for(int i=0;i<inputs.size();i++){
    if(inputs[i].first.find(target_dir)!=-1){
      std::string path = std::string(inputs[i].first.begin()+target_dir.size()+1,inputs[i].first.end());
      if(path.find("/")!=-1){
        path = std::string(path.begin(),path.begin()+path.find("/"));
      }
      indicates[path]+=inputs[i].second;
    }
  }
  std::vector<std::pair<std::string,int>> indicate_array;
  //REVIEW 根据值对map排序
  for(auto p:indicates){
    indicate_array.push_back(p);
  }
  
  std::sort(indicate_array.begin(),indicate_array.end(),[](std::pair<std::string,int> a,std::pair<std::string,int> b){
    return a.second>b.second ? true:false;
  });

  if(indicates.empty()){
    std::cout << "" << std::endl;
  }
  else{
    for(int i=0;i<indicate_array.size();i++){
        if(i==0){
            std::cout << indicate_array[i].first;
        }
        else{
            if(indicate_array[i].second == indicate_array[0].second){
                std::cout << " " << indicate_array[i].first;
            }
            else{
                break;
            }
        }
    }
    std::cout << std::endl;
  }

  return 0;
}