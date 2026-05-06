#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

int main(){
  std::vector<int> input;
  std::string input_s;
  std::getline(std::cin,input_s);
  std::stringstream ss(input_s);
  std::string e;
  while(ss>>e){
    input.push_back(std::stoi(e));
  }
  int m;
  std::cin >> m;

  auto min = *std::min_element(input.begin(),input.end());//REVIEW 有没有办法偷懒

  if(min>m){//REVIEW 当min>m时 方案只有一个
    std::cout << 1 << std::endl;
    return 0;
  }

  std::vector<int> dp(m+1,0);

  dp[0]=1;

  for(int i=0;i<input.size();i++){
    for(int j=input[i];j<m+1;j++){
        dp[j]=dp[j]+dp[j-input[i]];
    }
  }
  if(min<=0){
    std::cout << dp[m] << std::endl;
  }
  else{
    int result = 0;
    for(int i=0;i<min;i++){
      //if(m-i>=0){//REVIEW 
        result += dp[m-i];
      //}
    }
    std::cout << result << std::endl;
  }
  return 0;
}