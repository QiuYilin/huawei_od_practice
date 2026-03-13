#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include <regex>
#include<algorithm>
using namespace std;
//REVIEW  固定一个维度 得到最长递增子序列的等价问题

vector<vector<int>> parseStringTo2DArray(const string &s) {
    vector<vector<int>> result;
    regex rowPattern(R"(\[(\d+),(\d+)\])"); // 正则匹配 [num1,num2]
    smatch match;

    string::const_iterator searchStart(s.cbegin());
    while (regex_search(searchStart, s.cend(), match, rowPattern)) {
        result.push_back({stoi(match[1]), stoi(match[2])});
        searchStart = match.suffix().first; // 继续搜索下一个匹配项
    }

    return result;
}

//固定长度  
bool cmp(vector<int> ans1, vector<int> ans2) {
    if (ans1[0] == ans2[0]) {
        // 宽度降序
        return ans1[1] > ans2[1];
    } 
    // 长度升序
    return ans1[0] < ans2[0];
}

int main() {
    string s;
    cin >> s;
    vector<vector<int>> ans = parseStringTo2DArray(s);
    if (ans.size() == 0) {
        cout << 0;
        return 0;
    }
    //REVIEW 先固定一个维度
    sort(ans.begin(), ans.end(), cmp);
    int n = ans.size();
    vector<int> width(n); 
    for (int i = 0; i < n; i++) {
        width[i] = ans[i][1];
    }
    
    // dp[i]代表递增子序列长度为i能取的最小
    //贪心+二分优化
    vector<int> dp;
    dp.push_back(width[0]);
    for (int i = 1; i < width.size(); i++) {
        if (width[i] > dp[dp.size() -1]) {
            dp.push_back(width[i]);
        } else {
            //REVIEW lower_bound的用法
            //找到第一个 >= width[i] 的位置
            auto it = lower_bound(dp.begin(), dp.end(), width[i]);
            *it = width[i];
        }
        
    }

    cout << dp.size();
    
    // 超限做法
    // std::vector<int> dp(n,1);
    // int result = 0;
    // dp[0]=1;
    // for(int i=1;i<n;i++){
    //   for(int j=0;j<i;j++){
    //     if(width[i]>width[j]){
    //       dp[i]=std::max(dp[i],dp[j]+1);
    //     }
    //   }
    //   result = std::max(dp[i],result);
    // }
    // std::cout << result << std::endl;
    return 0;
}
