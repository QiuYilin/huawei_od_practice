#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;


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

int main() {
    // 处理输入
    string costInput,daysInput;
    getline(cin, costInput);
    getline(cin, daysInput);


    vector<int> costs = split(costInput, " ");
    vector<int> days = split(daysInput, " ");
    
    // // 最大游玩日期
    int maxDay = days.back();

    // dp[i]的含义完成i天之前所有游玩日的消费
    vector<int> dp(maxDay + 1, 0);
    
    int index = 0;
    
    // 枚举天数
    for (int i = 1; i <= maxDay; i++) {
        // 当前天不是游玩天,不需要消费,消费金额等于前i-天
        if (i != days[index]) {
            dp[i] = dp[i-1];
            continue;
        }
        // 选择一日票
        int buyOne = dp[i-1] + costs[0];

        int buyThree = (i - 3 >= 0 ? dp[i-3] : 0) + costs[1];

        int buySeven = (i - 7 >= 0 ? dp[i-7] : 0) + costs[2];

        int buyMonth = (i - 30 >= 0 ? dp[i-30] : 0) + costs[3];
        
        // 选取其中的最小值
        dp[i] = min({buyOne, buyThree, buySeven, buyMonth});
        index++;
    }
    cout << dp[maxDay];
    return 0;
}
