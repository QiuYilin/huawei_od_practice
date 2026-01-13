#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
// 审题
std::unordered_set<char> set{'a', 'e', 'i', 'o', 'u'};

bool isVowel(char c) {
  if (set.find(c) != set.end()) {
    return true;
  } else {
    return false;
  }
}

bool isConsonant(char c) {
  if (std::isalpha(c) && !isVowel(c)) {
    return true;
  } else {
    return false;
  }
}

int main() {
  std::vector<std::string> inputs;
  std::string ele;
  std::string line;
  std::getline(std::cin, line);
  std::stringstream ss(line);
  while (ss >> ele) {  // 疑问 为什么不结束
    inputs.push_back(ele);
  }
  for (int i = 0; i < inputs.size(); i++) {
    bool flag = true;
    for (int j = 0; j < inputs[i].size(); j++) {
      if (!std::isalpha(inputs[i][j])) {
        flag = false;
      }
    }
    if (!flag) {
      continue;
    } else {
      std::reverse(inputs[i].begin(),
                   inputs[i].end());  // REVIEW reverse属于algorithm头文件
    }
  }
  int count = 0;
  for (int i = 0; i < inputs.size(); i++) {
    for (int j = 0; j + 3 < inputs[i].size(); j++) {
      if (isConsonant(inputs[i][j]) && isVowel(inputs[i][j + 1]) &&
          isConsonant(inputs[i][j + 2]) &&
          inputs[i][j + 2] != 'r'  // REVIEW r除外
          && inputs[i][j + 3] == 'e') {
        count++;
      }
    }
  }
  std::cout << count << std::endl;
  return 0;
}
