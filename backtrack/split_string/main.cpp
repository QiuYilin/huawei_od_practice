#include <iostream>
#include <vector>
#include <string>
#include <cmath>
//审题：水仙花数
//穷举+剪枝
//REVIEW 可以直接通过前缀和处理
bool isValid(std::string s){
  int sum = 0;
  for(int i=0;i<s.size();i++){
    sum+=s[i];//REVIEW ASCII直接处理
  }
  //整数转字符串
  std::string sum_s = std::to_string(sum);
  if(sum_s.size()!=3){
    return false;
  }
  int sum_new = 0;
  for(int i=0;i<sum_s.size();i++){
    sum_new+=std::pow(sum_s[i]-'0',3);
  }
  return sum_new==sum;
}
//REVIEW path_size只是辅助计算参数 全局的结果都在result中
void backtrack(const std::string &input,std::vector<int> &result,int &path_size,int index){
  //终止条件
  if(index >= input.size()){
    result.push_back(path_size);
    return;
  }
  for(int i=index;i<input.size();i++){
    //REVIEW 子串是[index,i]
    if(isValid(input.substr(index,i-index+1))){
        path_size++;
        backtrack(input,result,path_size,i+1);
        path_size--;
    }
  }
}

int main(){
  //疑问 字母转ASCII码？ 直接等于？
  std::string input;
  std::cin >> input;
  std::vector<int> result;
  int path_size = 0;
  backtrack(input,result,path_size,0);
  if(result.size() == 0){
    std::cout << "0" << std::endl;
  }
  else if(result.size() >1){
    std::cout << "-1" << std::endl;
  }
  else{
    std::cout << result[0] << std::endl;
  }
  return 0;
}