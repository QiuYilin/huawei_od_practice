#include <iostream>
#include <vector>
// 题意 贪心商人 股票买卖一
// REVIEW 规律是如果前一天的价格低于今天价格 就把差值纳入利润
// 3 2 6 7
int main() {
  int number = 0;  // 商品数量
  std::cin >> number;
  int days = 0;
  std::cin >> days;
  std::vector<int> item(number, 0);
  for (int i = 0; i < number; i++) {
    std::cin >> item[i];
  }
  std::vector<std::vector<int>> prices(number, std::vector<int>(days, 0));
  for (int i = 0; i < number; i++) {
    for (int j = 0; j < days; j++) {
      std::cin >> prices[i][j];
    }
  }
  int result = 0;
  for (int i = 0; i < number; i++) {
    for (int j = 1; j < days; j++) {//REVIEW
      int profit = std::max(0,prices[i][j]-prices[i][j-1]);//REVIEW 
      result += profit * item[i];
    }
  }
  std::cout << result << std::endl;
  return 0;
}