#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// REVIEW 判断能否满足间隔和数量的子问题写法
bool check(vector<int> ans, int m, int dis) {
  int count = 1;
  int currentPosoition = ans[0];
  for (int i = 1; i < ans.size(); i++) {
    if (ans[i] - currentPosoition >= dis) {
      count++;
      currentPosoition = ans[i];
    }
  }
  return count >= m;
}

int main() {
  int n;
  cin >> n;
  vector<int> ans(n, 0);
  for (int i = 0; i < n; i++) {
    cin >> ans[i];
  }
  int count;
  int result;
  cin >> count;
  sort(ans.begin(), ans.end());
  // 二分设置边界
  int left = 1, right = ans[n - 1] - ans[0];
  while (left <= right) {
    int mid = (left + right + 1) >> 1;
    if (check(ans, count, mid)) {
      result = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  cout << result;
  return 0;
}
