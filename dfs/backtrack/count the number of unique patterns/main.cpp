// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <string>
// #include <algorithm>
// using namespace std;

// //AAABBBCCC
// // A
// // B B B C C C
// void backtrack(int &result,string &path,vector<bool> used,string s){
//     if(path.size()==s.size()){
//         result++;
//         return;
//     }
//     for(int i=0;i<s.size();i++){
//         if(used[i]==true){
//           continue;
//         }
//         if(i>=1&&used[i]==false&&s[i]==s[i-1]&&used[i-1]==false){
//           continue;
//         }
//         if(i>=1&&used[i]==false&&s[i]==s[i-1]&&used[i-1]==true&&path.back()==s[i]){
//           continue;
//         }
//         path.push_back(s[i]);
//         used[i]=true;
//         backtrack(result,path,used,s);
//         path.pop_back();
//         used[i]=false;
//     }
// }

// int countValidPatterns(string& s) {
//   //全排列
//   std::sort(s.begin(),s.end());
//   string path;
//   vector<bool> used(s.size(),false);
//   int result = 0;
//   backtrack(result,path,used,s);
//   return result;
// }

// int main() {
//     string s;
//     cin >> s;

//     int ans = countValidPatterns(s);
//     cout << ans << endl;

//     return 0;
// }

//记忆化
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

unordered_map<string, int> memo;

// 把状态转成key
string getKey(vector<int>& cnt, int prev) {
    string key;
    for (int x : cnt) {
        key += to_string(x) + ",";
    }
    key += "|" + to_string(prev);
    return key;
}

// DFS + 记忆化
int dfs(vector<int>& cnt, int prev, int remain) {
    if (remain == 0) return 1;

    string key = getKey(cnt, prev);
    if (memo.count(key)) return memo[key];

    int res = 0;

    for (int i = 0; i < 26; i++) {
        if (cnt[i] > 0 && i != prev) {
            cnt[i]--;

            res += dfs(cnt, i, remain - 1);

            cnt[i]++; // 回溯
        }
    }

    memo[key] = res;
    return res;
}


int countValidPatterns(string& s) {
    vector<int> cnt(26, 0);
    for (char c : s) {
        cnt[c - 'A']++;
    }

    int n = s.size();

    int ans = dfs(cnt, -1, n);
    return ans;
}

int main() {
    string s;
    cin >> s;

    int ans = countValidPatterns(s);
    cout << ans << endl;

    return 0;
}

