#include <iostream>
#include <string>
#include <vector>
// 审题 满足条件的个数
// 疑问 题目是什么鬼 11更合理
// 动态规划 规律 f()
// 回溯法
// 连续->双指针
bool isValid(std::vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] < 1) {
      return false;
    }
  }
  return true;
}

int main() {
  std::string input;
  std::cin >> input;
  int k = 0;
  std::cin >> k;
  std::vector<int> vec(10, 0);
  if (input.size() < k) {
    std::cout << 0 << std::endl;
    return 0;
  }
  int left = 0;
  int right = k - 1;
  for (int i = 0; i < k; i++) {
    if (std::isdigit(input[i])) {
      vec[input[i] - '0']++;  // stoi在什么头文件
    }
  }
  int count = 0;

  for (; right < input.size(); right++) {
    if (right != k - 1) {
      if (std::isdigit(input[right])) {
        vec[input[right] - '0']++;
      }
    }
    if (isValid(vec)) {
      count++;
    }
    if (std::isdigit(input[left])) {
      vec[input[left] - '0']--;
    }
    left++;
  }
  std::cout << count << std::endl;
  return 0;
}