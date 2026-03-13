#include <iostream>
#include <vector>
#include <cmath>
//dp[i][j] = std::max(dp[i-1][j],dp[i][j-w[i]]+v[i]);
int main(){
    int n;
    std::cin >> n;
    std::vector<std::pair<int,int>> w;
    for(int i=0;i<n;i++){
      int size;
      std::cin >> size;
      w.push_back({size,std::ceil((float)size/512)});
    } 
    std::vector<int> dp(1474560/512+1);
    //std::vector<int> result(1474560/512+1);
    int r;
    dp[0]=0;
    for(int i=0;i<n;i++){
      for(int j=1474560/512;j>=w[i].second;j--){  
        // if(dp[j-w[i].second]+w[i].second>=dp[j]){
        //     dp[j]=dp[j-w[i].second]+w[i].second;
        // }
        dp[j]=std::max(dp[j],dp[j-w[i].second]+w[i].first);//REvIEW 实际大小是价值
      }
    }
    std::cout << dp[1474560/512] << std::endl;
    return 0;
}