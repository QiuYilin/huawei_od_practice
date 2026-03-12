#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;

// 通用 切割函数 函数 将字符串str根据delimiter进行切割
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

// nums 数组  index 当前开始索引 sum 之前选择元素和 tartget目标值 minvalue 数组中最小值
int dfs(vector<int>& nums, int index, int sum, int target, int minValue) {
    if (sum > target) {
        return 0;
    }
    // 和等于target值或者 差值小于minvalue
    if (sum == target || (target - sum < minValue && target - sum > 0)) {
        return 1;
    }

    int count = 0;
    for (int i = index; i < nums.size(); i++) {
        count += dfs(nums, i, sum + nums[i], target, minValue);
    }
    return count;
}


int main() {
    string input;
    int m;
    getline(cin, input);
    vector<int> nums = split(input, " ");
    cin >> m;

    //去除大于m的元素
    vector<int> filterNum;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] <= m) {
            filterNum.emplace_back(nums[i]);
        }
    }
    
    // 只能有1个不在N中，只有一种方案就是m
    if (filterNum.empty()) {
        cout << 1;
        return 0;
    }


   sort(filterNum.begin(), filterNum.end());
   int minValue = filterNum[0];

   int res = dfs(filterNum, 0, 0, m, minValue);

   cout << res;
   return 0;
}





