#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;
//REVIEW 需求不能跨月
//REVIEW 等价于求满足条件的临界值

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

//REVIEW 子问题 人力为presonCount时消耗时间会在m以内吗
//REVIEW 贪心 尽量让小需求和大需求在一起
bool check(vector<int>& requirements, int personCount, int m) {
    long needMonth = 0;
    int l = 0, r = requirements.size() -1;
    // 双指针求最小月数
    while (l <= r) {
        if (l == r) {
            needMonth++;
            r--;
            continue;
        }
        long actualPeronCount = requirements[l] + requirements[r];
        // 一同处理
        if (actualPeronCount <= personCount) {
            l++;
            r--;
        // 选择消耗工作量大的    
        } else {
            r--;
        }
        needMonth++;
    }
    return needMonth <= m;
}


int main() {
    int m;
    cin >> m;
    string input;
    // 忽略空行
    cin.ignore();
    getline(cin, input);
    vector<int> requirements  = split(input, " ");
    int n = requirements.size();
    
    sort(requirements.begin(), requirements.end());
    //REVIEW 人力的边界值
    long left = requirements[n-1];
    long right = requirements[n-1] + requirements[n - 2];
    // 二分
    while (left < right) {
        long mid = (left + right) >> 1;
        if (check(requirements, mid, m)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left;
    return 0;
}
