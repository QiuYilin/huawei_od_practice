#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <iomanip>

using namespace std;
//REVIEW 根据题意，B的情况要先排除掉A
int main() {
    int n;
    cin >> n;
    
    vector<pair<string, string>> ans(n);
    for (int i = 0; i < n; i++) {
        cin >> ans[i].first >> ans[i].second;
    }

    int matchCount = 0;
    string result;

    // 遍历所有可能的四位数
    for (int i = 0; i < 10000; i++) {
        // 生成四位数字符串（手动填充 '0'）
        char answer[5];//char *answer = new char[5]; C 风格的写法数组少不了[]
        snprintf(answer, 5, "%04d", i);//REVIEW 将数字转为四位字符的方法

        bool is_match = true;
        for (const auto& p : ans) {
            const string& guess = p.first;
            const string& expected = p.second;
            
            int countA = 0, countB = 0;
            array<int, 10> v1{}, v2{};

            for (int pos = 0; pos < 4; pos++) {
                int c1 = answer[pos] - '0';
                int c2 = guess[pos] - '0';

                if (c1 == c2) {
                    countA++;
                } else {
                    v1[c1]++;
                    v2[c2]++;
                }
            }

            for (int pos = 0; pos < 10; pos++) {
                countB += min(v1[pos], v2[pos]);//REVIEW 计算位置不正确的方法
            }

            // 验证匹配
            if (to_string(countA) + "A" + to_string(countB) + "B" != expected) {
                is_match = false;
                break;  // 不符合规则，提前跳出
            }
        }

        if (is_match) {
            matchCount++;
            result = answer;
            if (matchCount > 1) {  // 早停策略
                cout << "NA";
                return 0;
            }
        }
    }

    cout << (matchCount == 1 ? result : "NA");
    return 0;
}

