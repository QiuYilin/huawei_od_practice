#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// uu = j tt = b ttt=bt tttt = bb ttttt = bbt tttttt = bbb  u/t > 3次
// u和t只会出现在末尾

vector<vector<int>> count(string s) {
  map<char, int> map;
  int slow = 0;
  int fast = 0;
  while (fast < s.size()) {
    slow = fast;
    if (s[slow] == 'u') {
      while (fast < s.size()&&s[fast] == 'u') {//REVIEW 一定要排查边界
        fast++;
      }
      int count = fast - slow;

      if (count != 1) {
        map['j'] += count / 2;
      }

      if (count % 2 != 0) {
        map['u'] += 1;
      }
    } else if (s[slow] == 't') {
      while (fast < s.size()&&s[fast] == 't') {
        fast++;
      }
      int count = fast - slow;

      if (count != 1) {
        map['b'] += count / 2;
      }

      if (count % 2 != 0) {
        map['t'] += 1;
      }
    } else {
      map[s[slow]]++;
      fast++;
    }
  }
  vector<vector<int>> result;
  for (auto it = map.begin(); it != map.end(); it++) {
    auto c = (*it).first;
    if (isdigit(c)) {
      result.push_back({c - '0', (*it).second});
    } else {
      result.push_back({10 + c - 'a', (*it).second});
    }
  }
  sort(result.begin(), result.end(), [](vector<int> a, vector<int> b) {
    if (a[1] > b[1]) {
      return true;
    } else if (a[1] == b[1]) {
      return a[0] < b[0] ? true : false;
    } else {
      return false;
    }
  });
  return result;
}

int main() {
  string s;
  cin >> s;
  vector<vector<int>> res = count(s);
  // 输出结果
  int n = res.size();
  for (int i = 0; i < n; i++) {
    cout << res[i][0] << ":" << res[i][1];
    if (i != n - 1) {
      cout << " ";
    }
  }
  return 0;
}
