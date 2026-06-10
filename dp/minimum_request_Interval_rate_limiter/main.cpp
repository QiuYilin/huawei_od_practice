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

vector<int> split(const string& str, const string& delimiter) {
  vector<int> result;
  size_t start = 0;
  size_t end = str.find(delimiter);
  while (end != string::npos) {
    result.push_back(stoi(str.substr(start, end - start)));
    start = end + delimiter.length();
    end = str.find(delimiter, start);
  }
  // 添加最后一个部分
  result.push_back(stoi(str.substr(start)));
  return result;
}

int getValidCount(vector<int>& timestamps, int minInterval) {
  // dp[i]//前i个信号有几种方案
  // dp[i]=dp[i-2]+dp[i-1]
  // 使用i dp[前面第一个小于dp[i] interval 的元素]+1
  // 不使用i dp[i-1]
  sort(timestamps.begin(), timestamps.end());
  std::vector<int> dp(timestamps.size(), 0);
  dp[0] = 2;

  // dp[0]=2 [] [1]
  // dp[1]=2+1=3 [] [1] [2]
  // dp[2]=dp[1]+dp[1]+1=3+ [] [1] [2] [4] [1 4] [2 4] [4]

  for (int i = 1; i < timestamps.size(); i++) {
    dp[i] = dp[i - 1];

    int prev = -1;
    for (int j = i - 1; j >= 0; j--) {
      if (timestamps[i] - timestamps[j] >= minInterval) {
        prev = j;
        break;
      }
    }

    if (prev != -1) {
      dp[i] += dp[prev];
    } else {
      dp[i]++;
    }
  }

  return dp[timestamps.size() - 1];
}

int main() {
  string time;
  int minInterval;
  getline(cin, time);
  cin >> minInterval;
  vector<int> timestamps;
  timestamps = split(time, ",");
  int res = getValidCount(timestamps, minInterval);
  cout << res;
  return 0;
}
// #include<iostream>
// #include<vector>
// #include<string>
// #include <utility>
// #include <sstream>
// #include<algorithm>
// #include<cmath>
// #include<map>
// using namespace std;

// vector<int> split(const string& str, const string& delimiter) {
//     vector<int> result;
//     size_t start = 0;
//     size_t end = str.find(delimiter);
//     while (end != string::npos) {
//         result.push_back(stoi(str.substr(start, end - start)));
//         start = end + delimiter.length();
//         end = str.find(delimiter, start);
//     }
//     // 添加最后一个部分
//     result.push_back(stoi(str.substr(start)));
//     return result;
// }

// int getValidCount(vector<int>& timestamps, int minInterval) {
//     int res = 0;
//     // 从小到大进行排序
//     sort(timestamps.begin(), timestamps.end());
//     int n = timestamps.size();
//     // dp[i]表示以i结束的合法数量
//     vector<int> dp(n, 0);

//     for (int i = 0; i < n; i++) {
//         // 只包含本身
//         dp[i] = 1;
//         for (int j = 0; j < i; j++) {
//             if (timestamps[i] - timestamps[j] >= minInterval) {
//                 dp[i] += dp[j];
//             }
//         }
//     }

//     // 累加结果
//     int sum = 0;
//     for (int i = 0; i < n; i++) {
//         sum += dp[i];
//     }
//     // 额外加上空集
//     return sum + 1;
// }

// int main() {
//     string time;
//     int minInterval;
//     getline(cin, time);
//     cin >> minInterval;
//     vector<int> timestamps;
//     timestamps = split(time, ",");
//     int res = getValidCount(timestamps, minInterval);
//     cout << res;
//     return 0;
// }
