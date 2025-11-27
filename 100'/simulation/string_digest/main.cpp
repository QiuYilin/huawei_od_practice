#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<map>
using namespace std;

// 自定义排序
bool cmp(pair<char, int> p1, pair<char, int> p2) {
    if (p1.second == p2.second) {
        return p1.first < p2.first;
    }
    return p1.second > p2.second;
}


int main() {
    string s;
    cin >> s;
    // 转换为小写并过滤非字母字符
    string filtered = "";
    for (char c : s) {
        if (isalpha(c)) {//REVIEW 判断字母的函数是isalpha
            filtered += tolower(c);//REVIEW 比起删除，另外建立一个string更好
        }
    }

    // 统计每个字符的总频次
    map<char, int> mp;
    for (char c : filtered) {
        mp[c]++;
    }
    
    s = filtered;
    int n = s.size();
    vector<pair<char, int>> res;
    string tmp = "";
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            tmp += s[i];
            continue;
        }
        // 连续终止
        if (s[i] != s[i-1]) {
            char c = s[i-1];
            int length = tmp.size();
            mp[c] -= length;
            if (length == 1) {
                res.push_back({c, mp[c]});
            } else {
                res.push_back({c, length});
            }
            tmp = string(1, s[i]);
        } else {
            tmp += s[i];
        }
    }
    // 末尾边界处理
    if (tmp != "") {
        char c = tmp[0];
        int length = tmp.size();
        mp[c] -= length;
        if (length == 1) {
            res.push_back({c, mp[c]});
        } else {
            res.push_back({c, length});
        }
    }
    // 自定义排序
    sort(res.begin(), res.end(), cmp);
    string resString = "";

    for (int i = 0; i < res.size(); i++) {
        pair<char,int> p = res[i];
        resString += (string(1, p.first) + to_string(p.second));
    }
    cout << resString;
    return 0;
}
