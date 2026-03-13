// // #include <iostream>
// // //审题 
// // //贪心：
// // //分两半 01背包？？？ 不一样 对每组差距有要求
// // //规律  dp构建不起来啊
// // int main(){

// //     return 0;
// // }

// #include<iostream>
// #include<vector>
// #include<string>
// #include <utility> 
// #include <sstream>
// #include<algorithm> 
// using namespace std;


// // 通用 split 函数
// vector<string> split(const string& str, const string& delimiter) {
//     vector<string> result;
//     size_t start = 0;
//     size_t end = str.find(delimiter);
//     while (end != string::npos) {
//         result.push_back(str.substr(start, end - start));
//         start = end + delimiter.length();
//         end = str.find(delimiter, start);
//     }
//     // 添加最后一个部分
//     result.push_back(str.substr(start));
//     return result;
// }

// //REVIEW dp[i] i个队伍最多能匹配的队伍数量
// // minSum[i] i个队伍匹配之后最小差值的和
// // 增加一个队伍的匹配队伍的数量变化只会跟i-1和i-2队伍状态关联
// int main() {
//     int n,d;
//     cin >> n >> d;
//     // 处理换行符
//     cin.ignore();

//     string s;
//     getline(cin, s);
//     vector<string> ansStr = split(s, " ");
//     vector<int> ans(n);
//     for (int i = 0; i < n; i++) {
//         ans[i] = stoi(ansStr[i]);
//     }

//     //REVIEW 将队伍实力排序
//     //REVIEW 基本规律 尽量让相邻的队伍匹配
//     sort(ans.begin(), ans.end());
//     //  dp[i] 代表i个队伍能匹配的队伍数量
//     vector<int> dp(n+1, 0);
//     //minSum[i] i个队伍匹配之后差值的和 
//     vector<int> minSum(n+1, 0);

//     for (int i = 2; i <= n; i++) {
//         bool canMatch = false;
//         // 能否匹配
//         if (ans[i-1] - ans[i-2] <= d) {
//             canMatch = true;
//         }
//         if (canMatch) {
//             //REVIEW 不匹配当前队伍是dp[i-1] 匹配当前队伍就是dp[i-2]+1
//             if (dp[i-1]  < dp[i-2] + 1) {
//                 dp[i] = dp[i-2] + 1;
//                 minSum[i] = minSum[i-2] + ans[i-1] - ans[i-2];
//             } else if (dp[i-1]  > dp[i-2] + 1) {
//                 dp[i] = dp[i-1];
//                 minSum[i] = minSum[i-1];             
//             } else {
//                 dp[i] = dp[i-1];
//                 minSum[i] = min(minSum[i-1], minSum[i-2] + ans[i-1] - ans[i-2]);
//             }
//         } else {
//             dp[i] = dp[i-1];
//             minSum[i] = minSum[i-1];
//         }
        
//     }
//     if (dp[n] == 0) {
//         cout << -1;
//     }else {
//         cout << minSum[n];
//     }
//     return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int n, d;
    cin >> n >> d;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    // 排序是关键
    sort(nums.begin(), nums.end());
    
    // dp[i][j] 表示前i个队伍中，恰好匹配j对时的最小总差距
    // i从0到n，j从0到n/2
    int maxPairs = n / 2;
    vector<vector<int>> dp(n + 1, vector<int>(maxPairs + 1, INT_MAX / 2));
    
    // 初始化：配0对时差距为0
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    
    // 动态规划
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= maxPairs; j++) {
            // 情况1：第i个队伍不参与配对
            dp[i][j] = dp[i-1][j];
            
            // 情况2：第i个队伍和i-1配对
            int gap = nums[i-1] - nums[i-2];
            if (gap <= d) {
                dp[i][j] = min(dp[i][j], dp[i-2][j-1] + gap);
            }
        }
    }
    
    // 找最大的j使得dp[n][j]有有效值
    for (int j = maxPairs; j >= 0; j--) {
        if (dp[n][j] < INT_MAX / 2) {
            if (j == 0) {
                cout << -1 << endl;
            } else {
                cout << dp[n][j] << endl;
            }
            return 0;
        }
    }
    
    return 0;
}
