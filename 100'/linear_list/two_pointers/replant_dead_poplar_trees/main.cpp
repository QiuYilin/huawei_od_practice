#include <iostream>
#include <vector>
// 审题 死k棵树的最长子序列
int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> trees(n, 1);
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    int dead = 0;
    std::cin >> dead;
    trees[dead - 1] = 0;
  }
  int k = 0;
  std::cin >> k;
  int left = 0;
  int dead_count = 0;
  int result = 0;
  // 疑问：滑动窗口的模板[]
  for (int right = 0; right < trees.size(); right++) {
    if (trees[right] == 0) {
      dead_count++;
    }
    if (dead_count > k) {
      while (trees[left] != 0 && left <= right) {  // left到下一个死树之后
        left++;
      }
      if(trees[left]==0){
        left++;
        dead_count--;
      }
    } 
    result = std::max(result, right-left+1);
  }
  std::cout << result << std::endl;
  return 0;
}

// 1 0 1 0 1 1 0 1 1 1
          // l r r