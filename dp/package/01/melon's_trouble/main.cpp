#include <iostream>
#include <vector>
#include <numeric>
//dp[i][j]=std::max(dp[i-1][j],dp[i-1][j-w[i]]+1);
//dp[j]=min(dp[j],dp[j-w[i]]+1) //
int main(){
  int n;
  std::cin >> n;
  std::vector<int> w(n);
  for(int i=0;i<n;i++){
    std::cin >> w[i];
  }
  auto sum = std::accumulate(w.begin(),w.end(),0);
  if(sum%2!=0){
    std::cout << -1 << std::endl;
     return 0;
  }
  std::vector<int> dp(sum/2+1,n);
  dp[0]=0;
  for(int i=0;i<n;i++){
    for(int j=sum/2;j>=w[i];j--){
      dp[j]=std::min(dp[j],dp[j-w[i]]+1);
    }
  }
  std::cout << (dp[sum/2]==n? -1:dp[sum/2]) << std::endl;
  return 0;
}