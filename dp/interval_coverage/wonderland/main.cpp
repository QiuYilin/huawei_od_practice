#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

int main(){
    std::vector<int> costs(4,0);
    for(int i=0;i<4;i++){
        std::cin >> costs[i];
    } 
    std::string day;
    std::vector<int> days;
    while(std::cin >> day){
      days.push_back(std::stoi(day));//stoi的头文件
    }
    //REVIEW 规律① 当天不玩 等价于前一天 实现技巧
    std::vector<int> dp(365+1,INT_MAX);
    dp[0]=0;
    int index = 0;
    for(int i=1;i<=365&&index<days.size();i++){
      if(i!=days[index]){
        dp[i]=dp[i-1];
        continue;
      }
      auto one   = i>=1 ? dp[i-1]+costs[0] : costs[0];//规律②
      auto three = i>=3 ? dp[i-3]+costs[1] : costs[1];
      auto week  = i>=7 ? dp[i-7]+costs[2] : costs[2];
      auto month = i>=30 ? dp[i-30]+costs[3] : costs[3];
      dp[i]=std::min({one,three,week,month});
      index++;
    }
    std::cout << dp[days.back()] << std::endl;
    return 0;
}