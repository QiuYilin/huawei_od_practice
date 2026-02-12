#include <iostream>

#include <vector>
//审题 背包问题  背包容积T 01背包
//dp[i][j]前i个物体 容量j 
//dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i])
//REVIEW 降维后剩的维度是背包容量
//dp[j]=max(dp[j],dp[j-w[i]]+v[i])
//疑问 01背包一维怎么初始化的
int main(){
  int time,n;
  std::cin >> time >> n;
  std::vector<int> times(n);
  std::vector<int> values(n);
  for(int i=0;i<n;i++){
    std::cin >> times[i];
    std::cin >> values[i];
  }
  std::vector<int> dp(time+1);
  //疑问 需要初始化吗
  for(int i=0;i<n;i++){
    for(int j=time;j>=times[i];j--){//REVIEW 为了不包括已经用过的 j从大到小遍历
      dp[j]=std::max(dp[j],dp[j-times[i]]+values[i]);
    }
  }
  std::cout << dp[time] << std::endl;
  return 0;
}