#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

// 审题 输出编号
std::vector<int> split(std::string line) {
  std::vector<int> result;
  std::stringstream ss(line);
  std::string s;
  while (std::getline(ss, s, ',')) {
    result.push_back(std::stoi(s));
  }
  return result;
}

int main() {
  std::string line;
  std::getline(std::cin, line);
  auto info = split(line);
  int m = info[0], n = info[1];
  if (m < 3 || m > 10 || n < 3 || n > 100) {
    std::cout << "-1" << std::endl;
    return 0;
  }
  std::vector<std::pair<int, std::vector<int>>> player_scores(
      n, {0, std::vector<int>(m, 0)});
  for (int i = 0; i < n; i++) {
    player_scores[i].first = i;
  }
  for (int i = 0; i < m; i++) {  // 评委
    std::getline(std::cin, line);
    auto scores = split(line);
    for (int j = 0; j < n; j++) {  //
                                   //   player_scores[j][i] = scores[j];
      //   if (player_scores[j][i] < 1 || player_scores[j][i] > 10) {
      //     std::cout << "-1" << std::endl;
      //     return 0;
      //   }
      if (scores[j] < 1 || scores[j] > 10) {
        std::cout << "-1" << std::endl;
        return 0;
      }
      player_scores[j].second[i] = scores[j];
    }
  }
  for (int i = 0; i < n; i++) {
    std::sort(player_scores[i].second.begin(), player_scores[i].second.end(),
              std::greater<int>());
  }
  std::sort(player_scores.begin(), player_scores.end(),
            [](std::pair<int, std::vector<int>> a,
               std::pair<int, std::vector<int>> b) {
              auto a_s = a.second;
              auto b_s = b.second;
              int a_sum = 0;
              int b_sum = 0;
              for (int i = 0; i < a_s.size(); i++) {//REVIEW 每次算和臃肿了 pair不够存 可以建个类
                a_sum += a_s[i];
                b_sum += b_s[i];
              }
              if (a_sum > b_sum) {
                return true;
              } else if (b_sum > a_sum) {
                return false;
              } else {
                for (int i = 0; i < a_s.size(); i++) {
                  if (a_s[i] > b_s[i]) {
                    return true;
                  } else if (a_s[i] < b_s[i]) {
                    return false;
                  } else {
                    continue;
                  }
                }
              }
            });

  for (int i = 0; i < 3; i++) {
    if (i > 0) {
      std::cout << ",";
    }
    std::cout << player_scores[i].first + 1;
  }
  std::cout << std::endl;

  return 0;
}