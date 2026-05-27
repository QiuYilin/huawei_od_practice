#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
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

vector<vector<int>> priorityPackets(int n, int k,
                                    vector<vector<int>>& packets) {
  vector<int> firstBigger(n, -1);
  stack<int> stack;
  for (int i = 0; i < n; i++) {
    int cur_pri = packets[i][1];
    while (!stack.empty() && cur_pri > packets[stack.top()][1]) {
      firstBigger[stack.top()] = i;
      stack.pop();
    }
    stack.push(i);
  }
  vector<vector<int>> result;

  for (int i = 0; i < n - k + 1; i++) {
    vector<int> path;
    for (int j=i;j<i+k;j++) {
      if (firstBigger[j] != -1 && firstBigger[j] <= i + k - 1) {
        path.push_back(packets[firstBigger[j]][0]);
      }
    }
    result.push_back(path);
  }

  return result;
}

int main() {
  int n;
  int k;
  cin >> n;
  cin >> k;
  cin.ignore();
  string input;
  getline(cin, input);

  // 提取出对应packets
  vector<string> packetsStr = split(input, " ");
  vector<vector<int>> packets(packetsStr.size());
  for (int i = 0; i < packetsStr.size(); i++) {
    vector<string> tmp = split(packetsStr[i], ":");
    packets[i] = {stoi(tmp[0]), stoi(tmp[1])};
  }

  vector<vector<int>> res = priorityPackets(n, k, packets);
  // 输出结果
  if (res.empty()) {
    return 0;
  }
  for (int i = 0; i < res.size(); i++) {
    if (i != 0) {
      cout << " ";
    }
    for (int j = 0; j < res[i].size(); j++) {
      if (j != 0) {
        cout << ",";
      }
      cout << res[i][j];
    }
  }
  return 0;
}
