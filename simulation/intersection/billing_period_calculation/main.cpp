#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// 通用 切割函数 函数 将字符串str根据delimiter进行切割
vector<string> split(const string& str, const string& delimiter) {
  vector<string> result;
  size_t start = 0;
  size_t end = str.find(delimiter);
  while (end != string::npos) {
    result.push_back(str.substr(start, end - start));
    start = end + delimiter.length();
    end = str.find(delimiter, start);
  }
  // 添加最后一个部分
  result.push_back(str.substr(start));
  return result;
}

// 同一使用分钟表示
int getTimeInt(string time) {
  vector<string> timeSplit = split(time, ":");
  int res = 0;
  res = stoi(timeSplit[0]) * 60 + stoi(timeSplit[1]);

  return res;
}

int toMin(string input) {
  stringstream ss(input);
  string h, m;
  std::getline(ss, h, ':');
  std::getline(ss, m);
  return 60 * stoi(h) + stoi(m);
}

vector<int> calBilling(string& startEnd) {
  // 先算第一档 区间重合的技巧
  // 第二档=min(10h,剩余时间)
  // 第三档 剩余时间-第一档-第二档
  stringstream ss(startEnd);
  string start, end;
  ss >> start >> end;
  int start_i = toMin(start);
  int end_i = toMin(end);
  auto level1_s = toMin("12:00");
  auto level1_e = toMin("13:30");
  auto level1_s1 = toMin("17:30");
  auto level1_e1 = toMin("18:00");
  vector<int> result;
  int level1_t =
      std::max(0, std::min(end_i, level1_e) - std::max(start_i, level1_s)) +
      std::max(0, std::min(end_i, level1_e1) - std::max(start_i, level1_s1));
  result.push_back(level1_t);
  int level2_t = std::min(10*60,end_i-start_i-level1_t);
  result.push_back(level2_t);
  int level3_t = end_i-start_i-level1_t-level2_t;
  result.push_back(level3_t);
  return result;
}

int main() {
  string input;
  getline(cin, input);
  vector<int> res = calBilling(input);
  // 输出结果
  for (int i = 0; i < 3; i++) {
    cout << res[i];
    if (i != 2) {
      cout << ",";
    }
  }
  return 0;
}
