#include <cmath>
#include <cstdlib>
#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
using namespace std;
// REVIEW 根据题意最后是统计累加的战斗力的
// 通用 split 函数
vector<string> split(const string& str, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // 添加最后一个部分
    result.push_back(str.substr(start));
    return result;
}

int main() {
    string s;
    getline(cin, s);
    // 异常情况判断
    if (s.empty()) {
        cout << -1;
        return 0;
    }
    vector<string> ans = split(s, " ");
    int n = ans.size();
    vector<int> numLeft(n);
    vector<int> numright(n);

    for (int i = 0; i < n; i++) {
        int tmp = stoi(ans[i]);
        // 异常输入
        if (tmp == 0) {
            cout << -1;
            return 0;
        }
        numLeft[i] = tmp;
        numright[i] = tmp;
    }
    
    long long sum = 0;
    int count = 0;
    //REVIEW 两个方向分别计算
    for (int i = 0; i < n; i++) {
        if (numLeft[i] > 0) {
            sum += numLeft[i];
        } else {
            int tmp = abs(numLeft[i]);
            if (tmp >= sum) { 
                numLeft[i] = numLeft[i] + sum;
                sum = 0;
            } else {
                numLeft[i] = 0;
                sum = sum - tmp;
            }
            // 统计往左走可以存活的数量
            if (numLeft[i] != 0) {
                // cout << i << " ";
                count++;
            }
        }
    }
    // 统计往右走可以存活的数量
    sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        int tmp = abs(numright[i]);
        if (numright[i] < 0) {
            sum += tmp;
        } else {
            if (tmp >= sum) {
                numright[i] = numright[i] - sum;
                sum = 0;
            } else {
                sum = sum - numright[i];
                numright[i] = 0;
                
            }
            // 统计往右走存活的数量
            if (numright[i] != 0) {
                // cout << i << " ";
                count++;
            }
        }
    }
    cout << count;
    return 0;
}

