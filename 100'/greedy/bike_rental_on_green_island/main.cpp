#include <algorithm>
#include <iostream>
#include <vector>
// 题意
// 每辆自行车最多坐两人 最大载重M
// 先考虑最重的人 从前面找人
int main() {  // 疑问负载的英文，
  int m = 0, n = 0;
  std::cin >> m >> n;
  std::vector<int> weights(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> weights[i];
  }
  std::sort(weights.begin(), weights.end());
  int result = 0;
  int j = 0;  // 表示还没有利用过的人
  for (int i = weights.size() - 1; i >= 0;
       i--) {  // 疑难 我有这样的习惯 想用数据结构记录变化
               // 然后在遍历时发现迭代器会变化 : 应该沿用vector+双指针
    if (i < j) {
      break;
    } else if (i > j) {
      if (weights[i] + weights[j] > m) {
        result++;
      } else {
        ++j;
        result++;
      }
    }
    else{
      result++;
    }
  }
  std::cout << result << std::endl;
  return 0;
}