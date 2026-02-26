// #include <iostream>
// //审题
// // Cn 1 Cn2 Cn3 Cnn
// // 5,2和6,9怎么处理 穷举组合问题
// int main(){
//   //预处理 怎么判断2和5有没有同时出现 6和9有没有同时出现
//   //超复杂
//   return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
using namespace std;
//REVIEW 要求大小是全排列而不是全组合 不要从数字去考虑 变种条件：存在可以互换的情况：并列的两条递归式
void generatePermutations(const vector<int>& nums, vector<bool>& used, string current, const int mapping[], vector<int>& results) {
    if (!current.empty()) {
        results.push_back(stoi(current));
    }
    //终止条件
    if (current.length() == nums.size()) return;
    
    //递归回溯
    for (size_t i = 0; i < nums.size(); i++) {
        if (used[i]) continue;

        used[i] = true;
        generatePermutations(nums, used, current + to_string(nums[i]), mapping, results);
        //REVIEW 处理可以互换的情况
        if (mapping[nums[i]] && find(nums.begin(), nums.end(), mapping[nums[i]]) == nums.end()) {
            generatePermutations(nums, used, current + to_string(mapping[nums[i]]), mapping, results);
        }

        used[i] = false;
    }
}

int main() {
    string input;
    getline(cin, input);

    vector<int> nums;
    // 防止重复
    vector<bool> seen(10, false);
    int maxValue = INT_MIN;

    size_t pos = 0;
    while ((pos = input.find(',')) != string::npos) {
        int num = stoi(input.substr(0, pos));
        if (num < 1 || num > 9 || seen[num]) {
            cout << -1 << endl;
            return 0;
        }
        seen[num] = true;
        nums.push_back(num);
        input = input.substr(pos + 1);
    }

    int lastNum = stoi(input);
    if (lastNum < 1 || lastNum > 9 || seen[lastNum]) {
        cout << -1 << endl;
        return 0;
    }
    seen[lastNum] = true;
    nums.push_back(lastNum);
   
    // 判断数量  2 5 是否同时存在， 6 9 是否同时存在
    if (nums.size() != 4 || (seen[2] && seen[5]) || (seen[6] && seen[9])) {
        cout << -1 << endl;
        return 0;
    }
    
    // 确定N
    for (int num : nums) {
        maxValue = max(maxValue, num);
    }

    int mapping[10] = {0};
    mapping[2] = 5;
    mapping[5] = 2;
    mapping[6] = 9;
    mapping[9] = 6;

    vector<int> results;
    vector<bool> used(nums.size(), false);

    generatePermutations(nums, used, "", mapping, results);

    if (results.empty()) {
        cout << -1 << endl;
        return 0;
    }

    sort(results.begin(), results.end());
    cout << results[min(maxValue, (int)results.size()) - 1] << endl;

    return 0;
}

