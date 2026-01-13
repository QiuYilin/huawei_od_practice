#include <iostream>
#include <string>
#include <vector>

#include <algorithm>
//审题
//目标：长度N 相同字符不能相邻 排列
void backtrack(std::string input,int k,int &result,std::string &path,std::vector<bool> &used){
  if(path.size()==k){
    result++;
    return;
  }
  else if(path.size()>k){
    return;
  }
  for(int i=0;i<input.size();i++){
    if(used[i]==true){
      continue;
    }
    if(i!=0&&input[i]==input[i-1]&&!used[i-1]){//REVIEW 排列问题的层去重
      continue;
    }
    if(!path.empty()&&path.back()==input[i]){
      // while(i+1<input.size()&&input[i+1]==path.back()){
      //   i++;
      // }
      continue;
    }
    path.push_back(input[i]);
    used[i]=true;
    backtrack(input,k,result,path,used);
    path.pop_back();
    used[i]=false;
  }
}
int main(){
  std::string input;
  int k;
  std::cin >> input;
  std::cin >> k;
  std::sort(input.begin(),input.end());
  int result = 0;
  std::string path;
  std::vector<bool> used(input.size(),false);
  backtrack(input,k,result,path,used);
  std::cout << result << std::endl;
  return 0;
}