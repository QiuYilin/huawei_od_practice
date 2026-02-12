#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <algorithm>
//审题 
//不连续 用回溯-   组合和子集是什么关系
void backtrack(int &result,std::vector<int> &path,int sum,int index,int k,int target,std::vector<int> input){
  if(path.size()==k&&sum==target){
    result++;
    return;
  }
  else if(path.size()>k){
    return;
  }
  //-4 -1 -1 0 1 2
  for(int i=index;i<input.size();i++){
    //REVIEW 层去重 
    if(i!=index && input[i]==input[i-1]){
      continue;
    }
    if(input[i]>0&&sum+input[i]>target){//REVIEW 剪枝
      break;//同一层后面的数字更大 没必要继续
    }
    path.push_back(input[i]);
    sum+=input[i];
    //if(sum<=target){
      backtrack(result,path,sum,i+1,k,target,input);
    //}
    path.pop_back();
    sum-=input[i];
  }
}
int main(){
  std::string line;
  std::getline(std::cin,line);
  std::stringstream ss(line);
  std::vector<int> input;
  int val;
  while(ss>>val){
    input.push_back(val);
  }
  std::sort(input.begin(),input.end());
  int k;
  std::cin >> k;
  int target;
  std::cin >> target;
  int result  = 0;
  std::vector<int> path;
  backtrack(result,path,0,0,k,target,input);
  std::cout << result <<std::endl;
  return 0;
}