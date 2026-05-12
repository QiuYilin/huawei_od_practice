#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include <cctype>
using namespace std;

int main() {
    string input;
    int k;
    getline(cin, input);
    cin >> k;
    int n = input.size();
    
    // 不满足
    if (n < 10 + k) {
        cout << 0;
        return 0;
    }
    
    // 存储结果
    int res = 0;
    vector<int> digitCount(10, 0);
    // 0 - 9 字符出现种类
    int numberCount = 0;
    // 英文字母字符出现数量
    int countChar = 0;
    int left = 0;
    
    // 将原来的 while (right < n) 改为 for 循环
    for (int right = 0; right < n; right++) {
        char c = input[right];
        if (isalpha(c)) {
            countChar++;
        }
        if (isdigit(c)) {
            digitCount[c - '0']++;
            if (digitCount[c - '0'] == 1) {
                numberCount++;
            }
        }
        
        // 超过k个字符，尝试缩小区间 移动左指针
        while (left <= right && countChar > k) {//REVIEW 和最大同逻辑 第一个条件
            char leftChar = input[left];
            if (isalpha(leftChar)) {
                countChar--;
            }
            if (isdigit(leftChar)) {
                digitCount[leftChar - '0']--;
                if (digitCount[leftChar - '0'] == 0) {
                    numberCount--;
                } 
            }
            left++;
        }
        
        // 满足合法序列情况，尝试移动左边界寻求更多合法子串
        if (numberCount == 10 && countChar == k) {
            // 不真实移动左指针，左指针移动只会发生在英文字母字符超过k时 使用备份数据进行模拟
            int tmpLeft = left;
            vector<int> tempCount = digitCount;
            int tmpNumberCount = numberCount;
            int tmpCountChar = countChar;
            while (tmpLeft <= right && tmpCountChar == k && tmpNumberCount == 10) {//REVIEW 条件二
                res++;
                char ch = input[tmpLeft];
                if (isalpha(ch)) {
                    tmpCountChar--;
                }
                if (isdigit(ch)) {
                    tempCount[ch - '0']--;
                    if (tempCount[ch - '0'] == 0) {
                        tmpNumberCount--;
                    } 
                } 
                tmpLeft++;
            }
        }
    }
    
    cout << res;
    return 0;
}