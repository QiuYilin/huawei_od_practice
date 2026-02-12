#include <iostream>
#include <sstream>
#include <vector>
// REVIEW 题意 题目的距离条件有bug 规律是循环一次和前一个元素调整为正确顺序即可
// 这样调整必然满足前面的排序条件
int main() {
  std::string line;
  std::getline(std::cin, line);
  std::stringstream ss(line);
  std::vector<int> input;
  std::string height;
  while (ss >> height) {  // REVIEW std::isdigit只能判断char是否是数字
    // REVIEW std::stoi会自动停止在非数字前 无法判断是否转换成功
    for (auto c : height) {
      if (!isdigit(c)) {
        std::cout << "[ ]" << std::endl;
        return 0;
      }
    }
    input.push_back(stoi(height));  // TODO 非法参数
  }
  for (int i = 1; i < input.size(); i++) {
    if ((i % 2 == 0 && input[i] < input[i - 1]) ||
        (i % 2 == 1 && input[i] > input[i - 1])) {
      std::swap(input[i], input[i - 1]);
    }
  }
  for (int i = 0; i < input.size(); i++) {
    if (i > 0) {
      std::cout << " ";
    }
    std::cout << input[i];
  }
  std::cout << std::endl;
  return 0;
}
