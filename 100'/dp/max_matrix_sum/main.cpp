#include <cmath>
#include <iostream>
#include <vector>
// 审题 最大子数组和的二维变种
int main() {
  // 有m列 等价与m种情况 转换为一维 然后的规律是累加不可是负数
  // 我的办法复杂度太高
  int n = 0, m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> matrix(n, std::vector<int>(m, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int cur = 0;
      std::cin >> matrix[i][j];
    }
  }
  // 疑问所有数组都是负数怎么办 答案是最大的那个负数

  // REVIEW 遍历比求组合更方便
  int result = INT_MIN;
  for (int i = 0; i < n; i++) {  //[上边界

    // for(int j=i;j<n;j++){//下边界]
    //   for(int k=0;k<m;k++){
    //   std::vector<int> vec(m,0);
    //     for(int l=i;l<=j;l++){
    //         vec[k]+=matrix[l][k];
    //     }

    //   }
    //REVIEW 这样写少一个循环 同一上边界的 等价一维数组是累加关系
    std::vector<int> vec(m,0);
    for(int j=i;j<n;j++){//下边界]
      for(int k=0;k<m;k++){
        vec[k]+=matrix[j][k];
      }
    // 求vec的最大和子数组
    // dp[i]=max(dp[i-1],dp[i-1]+vec[i]);//疑问 动态表是如何体现连续的
    std::vector<int> dp(m, 0);
    dp[0] = vec[0];
    for (int k = 1; k < m; k++) {
      dp[k] = std::max(vec[k], dp[k - 1] + vec[k]);
    }
    for (int k = 0; k < m; k++) {
      if (dp[k] > result) {
        result = dp[k];
      }
    }
  }
}
std::cout << result << std::endl;
return 0;
}
