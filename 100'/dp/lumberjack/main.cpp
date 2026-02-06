// #include <iostream>
// #include <vector>
// #include <algorithm>
// //数字会不会很大
// //dp[i] 长度为i的树木的最大收益
// //dp[i]=max(dp[m]*dp[n])  m+n=i;
// class State{
// public:
//   State(int val,std::vector<int> sol,int t):value(val),solution(sol),time(t){

//   }
//   int value;
//   std::vector<int> solution;
//   int time;
// };
// int main(){
//     int n;
//     std::cin >> n;
//     std::vector<State> dp(n+1);

//     for(int i=1;i<n+1;i++){
//         dp[i]=State(i,{i},0);
//     }
//     for(int i=2;i<n+1;i++){//10
//       for(int j=i/2;j>=1;j--){//1*9 2*8 3*7 4*6 5*5
//         if(dp[j].value*dp[i-j].value>dp[i].value){
//           dp[i].value=dp[j].value*dp[i-j].value;
//           dp[i].solution.clear();
//           //dp[i].second.assign(dp[j].second.begin(),dp[j].second.end());//疑问 vector的拼接
//           dp[i].solution.insert(dp[i].solution.end(),dp[j].solution.begin(),dp[j].solution.end());
//           dp[i].solution.insert(dp[i].solution.end(),dp[i-j].solution.begin(),dp[i-j].solution.end());
//         }
//       }
//     } 
//     std::sort(dp[n].second.begin(),dp[n].second.end());
//     for(int i=0;i<dp[n].second.size();i++){
//         if(i!=0){
//           std::cout << " ";
//         }
//         std::cout << dp[n].second[i];
//     }
//     std::cout << std::endl;
//     return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct State {
    int max_profit;           // 最大收益
    int min_cuts;             // 最少切割次数
    std::vector<int> lengths; // 对应的长度列表
};

int main() {
    int n;
    std::cin >> n;
    
    std::vector<State> dp(n + 1);
    
    // 初始化：不切割的情况
    for (int i = 1; i <= n; i++) {
        dp[i].max_profit = i;        // 不切割的收益就是长度本身
        dp[i].min_cuts = 0;          // 切割次数为0
        dp[i].lengths = {i};         // 只有一段
    }
    
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i / 2; j++) {
            int profit = dp[j].max_profit * dp[i - j].max_profit;
            int cuts = dp[j].min_cuts + dp[i - j].min_cuts + 1; // 加1表示当前切割
            
            // 判断是否需要更新
            bool update = false;
            if (profit > dp[i].max_profit) {
                update = true;
            } else if (profit == dp[i].max_profit) {
                // 收益相同，选择切割次数更少的
                if (cuts < dp[i].min_cuts) {
                    update = true;
                } 
            }
            
            if (update) {
                dp[i].max_profit = profit;
                dp[i].min_cuts = cuts;
                dp[i].lengths.clear();
                // 合并两部分的长度
                dp[i].lengths.insert(dp[i].lengths.end(), 
                                     dp[j].lengths.begin(), dp[j].lengths.end());
                dp[i].lengths.insert(dp[i].lengths.end(), 
                                     dp[i - j].lengths.begin(), dp[i - j].lengths.end());
            }
        }
    }
    
    // 排序输出
    std::sort(dp[n].lengths.begin(), dp[n].lengths.end());
    for (size_t i = 0; i < dp[n].lengths.size(); i++) {
        if (i > 0) std::cout << " ";
        std::cout << dp[n].lengths[i];
    }
    std::cout << std::endl;
    
    return 0;
}