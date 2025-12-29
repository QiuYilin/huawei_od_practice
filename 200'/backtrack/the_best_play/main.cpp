#include <iostream>
#include <string>
#include <vector>

void backtrack(std::vector<int> cardCount, int count, int index, int score,
               int& result) {
  if (count == 0) {
    result = std::max(score, result);
    return;
  }
  if (cardCount[index] == 0) {
    backtrack(cardCount, count, index + 1, score, result);
  }
  // 炸弹
  if (cardCount[index] >= 4) {
    cardCount[index] -= 4;
    count -= 4;
    score += 4 * index * 3;
    backtrack(cardCount, count, index, score, result);
    score -= 4 * index * 3;
    count += 4;
    cardCount[index] += 4;
  }
  // 顺子
  if (cardCount[index] >= 1 && cardCount[index + 1] >= 1 &&
      cardCount[index + 2] >= 1 && cardCount[index + 3] >= 1 &&
      cardCount[index + 4] >= 1) {
    cardCount[index] -= 1;
    cardCount[index + 1] -= 1;
    cardCount[index + 2] -= 1;
    cardCount[index + 3] -= 1;
    cardCount[index + 4] -= 1;
    count -= 5;
    score += (index * 5 + 1 + 2 + 3 + 4) * 2;
    backtrack(cardCount, count, index, score, result);
    cardCount[index] += 1;
    cardCount[index + 1] += 1;
    cardCount[index + 2] += 1;
    cardCount[index + 3] += 1;
    cardCount[index + 4] += 1;
    count += 5;
    score -= (index * 5 + 1 + 2 + 3 + 4) * 2;
  }
  // 三张
  if (cardCount[index] >= 3) {
    cardCount[index] -= 3;
    count -= 3;
    score += 3 * index * 2;
    backtrack(cardCount, count, index, score, result);
    cardCount[index] += 3;
    count += 3;
    score -= 3 * index * 2;
  }
  // 对
  if (cardCount[index] >= 2) {
    cardCount[index] -= 2;
    count -= 2;
    score += 2 * index * 2;
    backtrack(cardCount, count, index, score, result);
    cardCount[index] += 2;
    count += 2;
    score -= 2 * index * 2;
  }
  // 单张
  cardCount[index] -= 1;
  count -= 1;
  score += index;
  backtrack(cardCount, count, index, score, result);
  cardCount[index] += 1;
  count += 1;
  score -= index;
}

// #include <stdio> 疑问 为什么找不到stdlib头文件
// REVIEW 资源消耗类型的回溯
int main() {
  std::vector<int> cardCount(14, 0);
  std::string input;
  std::cin >> input;
  for (int i = 0; i < input.size(); i++) {
    if (std::isdigit(input[i])) {
      if (input[i] == '0') {
        cardCount[10]++;
      } else {
        cardCount[input[i] - '0']++;
      }
    } else {
      if (input[i] == 'J') {
        cardCount[11]++;
      } else if (input[i] == 'Q') {
        cardCount[12]++;
      } else if (input[i] == 'K') {
        cardCount[13]++;
      }
    }
  }
  int result = 0;
  backtrack(cardCount,input.size(),1,0,result);
  std::cout << result << std::endl;
  return 0;
}