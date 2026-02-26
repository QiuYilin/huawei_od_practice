#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void getMaxWater(std::vector<int>& nums) {
    int length = static_cast<int>(nums.size());

    int left = 0;
    int right = length - 1;

    vector<int> results(3, 0);

    int maxWater = 0;

    while (left < right) {
      // 更低的
      int lower = std::min(nums[left], nums[right]);
      int area = 0;

      // 遍历区间，计算面积
      for (int i = left + 1; i < right; i++) {
        area += std::max(0, lower - nums[i]);
      }

      if (maxWater <= area)  // 这里要小于等于
      {
        maxWater = area;
        results[0] = maxWater;
        results[1] = left;
        results[2] = right;
      }

      // 偏移指针
      if (nums[left] < nums[right])  // 左边低，右边高
      {
        left++;
      } else if (nums[left] > nums[right])  // 左边高，右边低
      {
        right--;
      } else if (nums[left] <
                 nums[left +
                      1])  // # 这里左右相等啦。就要看后面的是否比当前的要高
      {
        left++;
      } else {
        right--;
      }
    }

    std::cout << results[1] << " " << results[2] << ":" << results[0]
              << std::endl;
  }
};