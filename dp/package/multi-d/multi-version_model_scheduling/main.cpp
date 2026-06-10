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

// int getMaxAccuracy(int n, int t, vector<int>& accuracys, vector<int>& latencys) {
//     //完全背包
//     vector<int> dp(t+1,0);
//     for(int i=0;i<accuracys.size();i++){
//         for(int j=latencys[i];j<t+1;j++){
//            //dp[i][j]=max(dp[i-1][j],dp[i-1][j-latencys[i]]+accuracys[i])
//            dp[j]=max(dp[j],dp[j-latencys[i]]+accuracys[i]);
//         }
//     }
//     return dp[t];
// }

// int main() {
//     int n ,t;
//     cin >> n;
//     cin >> t;
//     cin.ignore();
//     string accuracyInput, latencyInput;
//     getline(cin, accuracyInput);
//     getline(cin, latencyInput);
//     vector<int> accuracy = split(accuracyInput, ",");
//     vector<int> latency = split(latencyInput, ",");

//     int res = getMaxAccuracy(n, t, accuracy, latency);
//     cout << res;
//     return 0;
// }

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

// int getMaxAccuracy(int n, int t, vector<int>& accuracys, vector<int>& latencys) {
//     // dp[i][j] 含义 查询i次，指定j时间能达到的最大准确率
//     vector<vector<int>> dp(n + 1, vector<int>(t+1, -1));
//     dp[0][0] = 0;
//     for (int i = 1; i <= n; i++) {//遍历查询次数 小到大 
//         for (int j = 0; j < latencys.size(); j++) {//遍历物品 小到大
//             int latency = latencys[j];
//             int accuracy = accuracys[j];
//             for (int m = t; m >= latency; m--) {//遍历背包 大到小
//                 // 状态可达
//                 if (dp[i-1][m - latency] != -1) {
//                     dp[i][m] = max(dp[i][m], dp[i-1][m - latency] + accuracy);
//                 }
//             }
//         }
//     }
    
//     // 不超过 t的最大准确率
//     int res = 0;
//     for (int i = 0; i <= t; i++) {
//         res = max(res, dp[n][i]);
//     }
//     return res;
// }

// int main() {
//     int n ,t;
//     cin >> n;
//     cin >> t;
//     cin.ignore();
//     string accuracyInput, latencyInput;
//     getline(cin, accuracyInput);
//     getline(cin, latencyInput);
//     vector<int> accuracy = split(accuracyInput, ",");
//     vector<int> latency = split(latencyInput, ",");

//     int res = getMaxAccuracy(n, t, accuracy, latency);
//     cout << res;
//     return 0;
// }

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// 字符串切割函数
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

// 计算最大总准确率（三维DP版本）
// n: 需要查询的次数
// t: 总时间预算
// accuracys: 各模型的准确率
// latencys: 各模型的延迟
int getMaxAccuracy(int n, int t, vector<int>& accuracys, vector<int>& latencys) {
    int m = accuracys.size();  // 模型种类数
    
    // dp[k][i][j]: 考虑前k种模型，选择i个查询，总时间为j的最大准确率
    // 初始化为 -1 表示不可达
    vector<vector<vector<int>>> dp(m + 1, 
        vector<vector<int>>(n + 1, 
            vector<int>(t + 1, -1)));
    
    // 初始状态：0种模型，0次查询，0时间，准确率为0
    dp[0][0][0] = 0;
    
    // 遍历每种模型
    for (int k = 1; k <= m; k++) {
        int acc = accuracys[k - 1];  // 当前模型的准确率
        int lat = latencys[k - 1];   // 当前模型的延迟
        
        // 遍历所有可能的查询次数
        for (int i = 0; i <= n; i++) {
            // 遍历所有可能的时间
            for (int j = 0; j <= t; j++) {
                // 情况1：不选当前模型（直接继承上一层的状态）
                if (dp[k - 1][i][j] != -1) {
                    dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i][j]);
                }
                
                // 情况2：选当前模型（可以选多次，完全背包）
                // 枚举选多少个当前模型
                for (int cnt = 1; i + cnt <= n && j + cnt * lat <= t; cnt++) {
                    if (dp[k - 1][i][j] != -1) {
                        dp[k][i + cnt][j + cnt * lat] = max(
                            dp[k][i + cnt][j + cnt * lat],
                            dp[k - 1][i][j] + cnt * acc
                        );
                    }
                }
            }
        }
    }
    
    // 找考虑所有模型后，查询n次，时间不超过t的最大准确率
    int res = 0;
    for (int j = 0; j <= t; j++) {
        res = max(res, dp[m][n][j]);
    }
    return res;
}

int main() {
    int n, t;
    
    // 读取查询次数和总时间预算
    cin >> n;
    cin >> t;
    cin.ignore();  // 忽略换行符
    
    // 读取准确率列表
    string accuracyInput;
    getline(cin, accuracyInput);
    vector<int> accuracy = split(accuracyInput, ",");
    
    // 读取延迟列表
    string latencyInput;
    getline(cin, latencyInput);
    vector<int> latency = split(latencyInput, ",");
    
    // 计算结果
    int res = getMaxAccuracy(n, t, accuracy, latency);
    
    // 输出结果
    cout << res << endl;
    
    return 0;
}