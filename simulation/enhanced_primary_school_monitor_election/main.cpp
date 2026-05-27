// #include <algorithm>
// #include <cmath>
// #include <iostream>
// #include <map>
// #include <sstream>
// #include <string>
// #include <unordered_map>
// #include <utility>
// #include <vector>
// using namespace std;

// // 通用 切割函数 函数 将字符串str根据delimiter进行切割
// vector<string> split(const string& str, const string& delimiter) {
//   vector<string> result;
//   size_t start = 0;
//   size_t end = str.find(delimiter);
//   while (end != string::npos) {
//     result.push_back(str.substr(start, end - start));
//     start = end + delimiter.length();
//     end = str.find(delimiter, start);
//   }
//   // 添加最后一个部分
//   result.push_back(str.substr(start));
//   return result;
// }

// string voteMonitor(vector<string>& names, vector<string>& votes) {
//   if (votes.size() > 3 * names.size()) {
//     return "Invalid election.";
//   }

//   for (int i = 0; i < votes.size(); i++) {
//     //只能匹配唯一一个人
//     //名字连续？
//     for (int j = 0; j < names.size(); j++) {
        
//     }
//   }
// }

// int main() {
//   string names;
//   string votes;
//   getline(cin, names);
//   getline(cin, votes);
//   vector<string> name = split(names, " ");
//   vector<string> vote = split(votes, " ");
//   string res = voteMonitor(name, vote);
//   cout << res;
//   return 0;
// }

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
#include<unordered_map>
using namespace std;

// 输入候选人名单 + 选票字符串
//         ↓
// 1. 预处理：建立所有合法子串 → 候选人索引的映射
//         ↓
// 2. 统计票数：对每张选票查表，累加到对应候选人
//         ↓
// 3. 合法性检查：票数是否超限、是否有有效票等
//         ↓
// 4. 确定班长：最高票（同票按名字字典序最小）
//         ↓
// 5. 输出结果

// 通用 切割函数 函数 将字符串str根据delimiter进行切割
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

string voteMonitor(vector<string>& names, vector<string>& votes) {
    int n = names.size();
    int m = votes.size();

    // 判断非常情况
    if (m > 3 * n) {
        return "Invalid election.";
    }

    // 预处理所有“合法子串” -> 映射到候选人，>=0 为合法 -1 多人发生冲突
    unordered_map<string, int> mp;
    for (int i = 0; i < n; i++) {
        string name = names[i];
        //非少数民族
        if (name.find('-') == string::npos) {
            if (!mp.count(name)) {
                mp[name] = i;        // 第一次出现
            } else if (mp[name] != i) {
                mp[name] = -1;       // 标记为冲突
            }
        } else {//少数民族
            vector<string> parts = split(name,"-");
            int k = parts.size();
            for (int l = 0; l < k; l++) {
                string cur = parts[l];
                if (!mp.count(cur)) {
                    mp[cur] = i;        // 第一次出现
                } else if (mp[cur] != i) {
                    mp[cur] = -1;       // 标记为冲突
                }                
                for (int r = l + 1; r < k; r++) {
                    cur += "-" + parts[r];
                    if (!mp.count(cur)) {
                        mp[cur] = i;        // 第一次出现
                    } else if (mp[cur] != i) {
                        mp[cur] = -1;       // 标记为冲突
                    }                     
                }
            }
        }
    }


    // 统计票数
    vector<int> cnt(n, 0);
    for (auto& vote : votes) {
        // 无效
        if (!mp.count(vote) || mp[vote] == -1) {
            continue;
        } 
        cnt[mp[vote]]++;
    }

    // 合法性判断
    bool hasVote = false;
    for (int i = 0; i < n; i++) {
        if (cnt[i] > 0) {
            hasVote = true;
        } 
        // 非法情况
        if (cnt[i] > n) {
            return "Invalid election.";
        }
    }
    // 无有效票
    if (!hasVote) {
        return "Invalid election.";
    }

    // 确定班长
    int maxVote = -1;
    string res;
    for (int i = 0; i < n; i++) {
        if (cnt[i] > maxVote) {
            maxVote = cnt[i];
            res = names[i];
        } else if (cnt[i] == maxVote && names[i] < res) {
            res = names[i];
        }
    } 
    return res;
}


int main() {
    string names;
    string votes;
    getline(cin, names);
    getline(cin, votes);
    vector<string> name = split(names, " ");
    vector<string> vote = split(votes, " ");
    string res = voteMonitor(name, vote);
    cout << res;
    return 0;
}
