#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;     // 输入的正整数，表示序列中最大元素值
  cin >> n;  // 读取n的值

  // pre0_odd[i]: 存储到位置i为止，所有以奇数结尾的全奇数序列的dp值前缀和
  // 全奇数序列：序列中所有元素都是奇数
  vector<long long> pre0_odd(n + 1, 0);

  // pre1_even[i]: 存储到位置i为止，所有以偶数结尾的全偶数序列的dp值前缀和
  // 全偶数序列：序列中所有元素都是偶数
  vector<long long> pre1_even(n + 1, 0);

  // pre2_even[i]: 存储到位置i为止，所有以偶数结尾的奇偶交替序列的dp值前缀和
  // 奇偶交替序列：相邻元素奇偶性不同，当前是偶数，下一个元素应该是奇数
  vector<long long> pre2_even(n + 1, 0);

  // pre2_odd[i]: 存储到位置i为止，所有以奇数结尾的奇偶交替序列的dp值前缀和
  // 当前是奇数，下一个元素应该是偶数
  vector<long long> pre2_odd(n + 1, 0);

  // ans0: 以n结尾的长度≥2的全奇数序列数量（不包含只含n自身的序列）
  // ans1: 以n结尾的长度≥2的全偶数序列数量
  // ans2: 以n结尾的长度≥2的奇偶交替序列数量
  long long ans0 = 0, ans1 = 0, ans2 = 0;

  // 遍历所有可能的序列结尾元素x（从1到n）
  for (int x = 1; x <= n; ++x) {
    int half = x / 2;  // 约束条件：序列中前一个元素的值必须≤当前元素的一半

    if (x % 2 == 1) {  // 情况1：当前元素x是奇数
      // dp0_val: 查询位置≤half的、以奇数结尾的全奇数序列总数
      // 这些序列后面可以接上当前的奇数x，形成更长的全奇数序列
      long long dp0_val = pre0_odd[half];

      // dp2_val: 查询位置≤half的、以偶数结尾的交替序列总数
      // 这些序列后面可以接上当前的奇数x，形成奇偶交替的序列
      long long dp2_val = pre2_even[half];

      // 更新全奇数序列：以x结尾的全奇数序列数 = 1（只含x自身）+
      // 前面可以接上的序列数
      long long dp0 = 1 + dp0_val;

      // 更新交替序列：以奇数x结尾的交替序列（下一个需要偶数）= 1 +
      // 前面以偶数结尾的交替序列数
      long long dp2 = 1 + dp2_val;

      // 更新前缀和数组
      pre0_odd[x] = pre0_odd[x - 1] + dp0;  // 累计到x位置的全奇数序列总数
      pre2_odd[x] =
          pre2_odd[x - 1] + dp2;        // 累计到x位置的以奇数结尾的交替序列总数
      pre1_even[x] = pre1_even[x - 1];  // x是奇数，全偶数序列前缀和保持不变
      pre2_even[x] = pre2_even[x - 1];  // 以偶数结尾的交替序列前缀和保持不变
    } else {                            // 情况2：当前元素x是偶数
      // dp1_val: 查询位置≤half的、以偶数结尾的全偶数序列总数
      long long dp1_val = pre1_even[half];

      // dp2_val: 查询位置≤half的、以奇数结尾的交替序列总数
      long long dp2_val = pre2_odd[half];

      // 更新全偶数序列：以x结尾的全偶数序列数 = 1 + 前面可以接上的序列数
      long long dp1 = 1 + dp1_val;

      // 更新交替序列：以偶数x结尾的交替序列（下一个需要奇数）= 1 +
      // 前面以奇数结尾的交替序列数
      long long dp2 = 1 + dp2_val;

      // 更新前缀和数组
      pre1_even[x] = pre1_even[x - 1] + dp1;  // 累计到x位置的全偶数序列总数
      pre2_even[x] =
          pre2_even[x - 1] + dp2;     // 累计到x位置的以偶数结尾的交替序列总数
      pre0_odd[x] = pre0_odd[x - 1];  // x是偶数，全奇数序列前缀和保持不变
      pre2_odd[x] = pre2_odd[x - 1];  // 以奇数结尾的交替序列前缀和保持不变
    }
  }

  // 最终结果计算：
  // 1: 只包含最后一个元素n的序列（长度为1的序列）
  // ans0: 以n结尾的长度≥2的全奇数序列数
  // ans1: 以n结尾的长度≥2的全偶数序列数
  // ans2: 以n结尾的长度≥2的交替序列数

  // cout << ans0+ans1+ans2+1 << "\n";
  if (n % 2 == 0) {
    cout << pre1_even[n / 2] + pre2_odd[n / 2] + 1
         << "\n";  // 偶数开头 对应全奇数前缀和 和 偶数开头的前缀和
  } else {
    cout << pre0_odd[n / 2] + pre2_even[n / 2] + 1 << "\n";
  }

  return 0;
}