#include <cstdio>
#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
using namespace std;


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

//REVIEW 可以跳过一天的情况下的最小值的子问题
bool check(vector<int> ans, int time, int totalDay) {
    int todayCost = 0;
    int maxCost = 0;
    bool canHelp = true;

    int day = 1;
    int i = 0;
    int n = ans.size();
    while (i < n) {
        todayCost += ans[i];
        maxCost = max(maxCost, ans[i]);//记录当前最大消耗题 不满足的时候删掉

        if (todayCost > time) {
            // 跳过用时最长的题目
            if (canHelp) {
               todayCost -= maxCost;
               canHelp = false;
               i++; 
            } else {
                day++;
                // 重置状态
                todayCost =0;
                maxCost = 0;
                canHelp = true;
            }
        } else {
            i++;
        }    
    }
    return day <= totalDay;
}

int main() {
    string s;
    getline(cin, s);
    int t;
    cin >> t;
    vector<string> ansStr = split(s, ",");
    int n = ansStr.size();
    vector<int> ans (n,0);
    int sum = 0;
    for (int i = 0;i<n;i++) {
        ans[i] = stoi(ansStr[i]);
        sum += ans[i];
    }
    int l = 0, r = sum;
    // 二分
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(ans,mid, t)) {
           r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << l;
    return 0;
}
