#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// 检查从start开始的k个连续数字的字符频率是否与目标匹配
bool checkSequence(int start, int k, const unordered_map<char, int>& target_freq) {
    unordered_map<char, int> current_freq;
    
    // 统计从start开始的k个数字的所有字符
    for (int i = start; i < start + k; i++) {
        string num_str = to_string(i);
        for (char c : num_str) {
            current_freq[c]++;
        }
    }
    
    // 比较两个频率映射是否完全相同
    return current_freq == target_freq;
}

int main() {
    string s;
    int k;
    cin >> s >> k;
    
    // REVIEW 统计输入字符串的字符频率
    unordered_map<char, int> target_freq;
    for (char c : s) {
        target_freq[c]++;
    }
    
    // 枚举所有可能的起始数字
    // 由于数字不超过1000，且序列长度为k，所以start最大为1000-k+1
    for (int start = 1; start <= 1000 - k + 1; start++) {//REVIEW 正整数不超过1000 直接暴力枚举 而不通过已有数字简化
        if (checkSequence(start, k, target_freq)) {
            cout << start << endl;
            return 0;
        }
    }
    
    return 0;
}