#include <iostream>
#include <vector>
int main(){
  int n =0;
  std::cin >> n;
  std::vector<int> dp(n+1,0);
  dp[0]=1;
  dp[1]=1;
  dp[2]=1;
  for(int i=3;i<n+1;i++){
    dp[i]=dp[i-1]+dp[i-3];
  }
  std::cout << dp[n] << std::endl;
  return 0;
}