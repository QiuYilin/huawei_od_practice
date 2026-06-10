#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

vector<int> split(const string& str, const string& delimiter) {
    vector<int> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(stoi(str.substr(start, end - start)));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    result.push_back(stoi(str.substr(start)));
    return result;
}

// 朴素 DP 版本（不使用前缀最大值优化）
long getMaxChargeDemand(int n, int m, int k, vector<int>& demand) {
    long ans = 0;
    // dp[i][j] 表示以 i 结尾，选 j 个站的最大和
    vector<vector<long>> dp(n, vector<long>(m + 1, -1));
    
    for (int i = 0; i < n; i++) {
        // 第 1 个站
        dp[i][1] = demand[i];
        
        // 第 j 个站（j >= 2）
        for (int j = 2; j <= m; j++) {
            // 遍历所有可能的前一个站的位置
            // 前一个站必须满足距离 >= k，所以 t <= i - k
            for (int t = 0; t <= i - k; t++) {
                if (dp[t][j-1] != -1) {
                    dp[i][j] = max(dp[i][j], dp[t][j-1] + demand[i]);
                }
            }
        }
        
        // 更新答案
        if (dp[i][m] > ans) {
            ans = dp[i][m];
        }
    }
    
    return ans;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    cin.ignore();
    string input;
    getline(cin, input);
    vector<int> demand = split(input, ",");
    
    long res = getMaxChargeDemand(n, m, k, demand);
    cout << res << endl;
    
    return 0;
}


// #include<iostream>
// #include<vector>
// #include<string>
// #include <utility> 
// #include <sstream>
// #include<algorithm> 
// #include<cmath>
// #include<map>
// using namespace std;

// // 通用 切割函数 函数 将字符串str根据delimiter进行切割
// vector<int> split(const string& str, const string& delimiter) {
//     vector<int> result;
//     size_t start = 0;
//     size_t end = str.find(delimiter);
//     while (end != string::npos) {
//         result.push_back(stoi(str.substr(start, end - start)));
//         start = end + delimiter.length();
//         end = str.find(delimiter, start);
//     }
//     // 添加最后一个部分
//     result.push_back(stoi(str.substr(start)));
//     return result;
// }

// long getMaxChargeDemand(int n,int m, int k, vector<int>& demand) {
//     long ans = 0;
//     // dp[i][j]记录在i创建第j个充电桩的充电需求量最大和
//     vector<vector<long>> dp(n + 1, vector<long>(m + 1, -1));
    
//     // maxCount[x]当前位置为i时，前0-(i-k)中已经创建x个充电装所有满足的最大需求
//     vector<long> maxCount(m+1, -1); 
//     for (int i = 0; i < n; i++) {//遍历索引
//         // 更新maxCount
//         if (i >= k) {
//             for (int j = 1; j <= m; j++) {
//                 maxCount[j] = max(maxCount[j], dp[i-k][j]);
//             }
//         }

//         dp[i][1] = demand[i];
//         for (int j = 2; j <= m; j++) {//遍历充电桩
//             if (maxCount[j-1] == -1) {
//                 continue;
//             }
//             dp[i][j] = maxCount[j - 1] + demand[i];
//         }
//         ans = max(ans, dp[i][m]);
//     }
//     return ans;
// }

// int main(){
//     int n, m, k;
//     cin >> n >> m >> k;
//     // 忽略换行
//     cin.ignore();
//     string input;
//     getline(cin, input);
//     vector<int> demand = split(input, ",");

//     long res = getMaxChargeDemand(n, m, k, demand);
//     cout << res;
//     return 0;
// }


// class Solution {
// public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      * 找最合适的建站方案
//      * @param n int整型 n个区域
//      * @param m int整型 m个站点
//      * @param k int整型 站之间的最小距离
//      * @param demands int整型vector 每个区域的充电诉求
//      * @return int整型
//      */
//     int solve(int n, int m, int k, vector<int>& demands) {
//         // write code here
//         // 穷举 Cn-m超时
//         // 改记忆化？
//         int result = 0;
//         backtrack(result,0,0,m,k,0,demands);
//         return result;
//     }
// private:
//     //unordered_map<> map; //count index 
//     void backtrack(int &result,int cur,int count,int m,int k,int index,const vector<int>& demands){
//         if(count==m){
//             result=max(result,cur);
//             return;
//         }
//         //剪枝

//         for(int i=index;i<demands.size()-(m-count-1)*k;i++){
//             cur+=demands[i];
//             count++;
//             backtrack(result,cur,count,m,k,i+k,demands);
//             cur-=demands[i];
//             count--;
//         }
//     }
// };

// class Solution {
// public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      * 找最合适的建站方案
//      * @param n int整型 n个区域
//      * @param m int整型 m个站点
//      * @param k int整型 站之间的最小距离
//      * @param demands int整型vector 每个区域的充电诉求
//      * @return int整型
//      */
//     int solve(int n, int m, int k, vector<int>& demands) {
//         // write code here
//         // 穷举 Cn-m超时
//         // 改记忆化？
//         dp[i][j]=max(dp[i-1][j]);
//     }
// };


