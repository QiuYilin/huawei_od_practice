#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
//审题 重组可以满足需求==字符频次相同
// 统计字符串 num 中的字符频次
void addNumberToMap(int num, unordered_map<char, int>& count) {
    for (char c : to_string(num)) {
        count[c]++;
    }
}

// 从统计 map 中移除一个数字的字符频次
void removeNumberFromMap(int num, unordered_map<char, int>& count) {
    for (char c : to_string(num)) {
        if (--count[c] == 0) {
            count.erase(c);
        }
    }
}

int main() {
    string s;
    int k;
    
    // 读取输入
    cin >> s >> k;



    // 统计目标字符频次
    unordered_map<char, int> base;
    for (char c : s) {
        base[c]++;
    }

    // 滑动窗口：维护当前窗口的字符统计
    unordered_map<char, int> count;

    // 初始化窗口（从 1 到 k）
    for (int i = 1; i <= k; i++) {
        addNumberToMap(i, count);
    }

    // 检查初始窗口是否匹配
    if (count == base) {
        cout << 1 << endl;
        return 0;
    }

    // 滑动窗口遍历 1 到 (1000 - k)
    for (int i = 2; i <= 1000 - k + 1; i++) {
        // 移除窗口左端的数字
        removeNumberFromMap(i - 1, count);
        // 添加窗口右端的新数字
        addNumberToMap(i + k - 1, count);

        // 检查窗口是否匹配
        if (count == base) {
            cout << i << endl;
            return 0;
        }
    }

    return 0;
}

