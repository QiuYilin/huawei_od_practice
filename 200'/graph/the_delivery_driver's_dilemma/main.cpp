#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<climits>
#include<map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    //REVIEW Floyd多源最短路
    vector<vector<int>> graph(N+1, vector<int>(N+1, -1));
    // 离散化,将不连续的id转换成连续的
    map<int, int> mp;
    // 初始化地图距离
    for (int i = 0; i <= N; i++) {
        graph[i][i] = 0;
    }
    // 起点和客户的管理
    for (int i = 0; i < N; i++) {
        int id, distance;
        cin >> id >> distance;
        mp[id] = i + 1;
        graph[0][mp[id]] = distance;
        graph[mp[id]][0] = distance;
    }
    // 客户之间距离更新
    for (int i = 0; i < M; i++) {
        int start,end, distance;
        cin >> start >> end >> distance;
        graph[mp[start]][mp[end]] = distance;
        graph[mp[end]][mp[start]] = distance;
    }
    
    // Floyd-Warsahll算法预处理最短路径，求出各个点之间最短路径
    for (int k = 0; k <= N; k++) {
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= N; j++) {
                if (graph[i][k] == -1|| graph[k][j] == -1) {
                    continue;
                }
                if (graph[i][j] == -1) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                } else {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }
    //REVIEW 状态压缩
    // 状态压缩 访问过 2进制位为1的所有位置之后，当前位置所消耗的时间
    //①dp数组的含义 [哪些客户已经收到快递][当前位置]:已经给mask的客户送完快递，并且当前在位置cur的最小总距离
    //②递推公式 
    //    从cur位置去投递站
    //    dp[mask][0] = min(dp[mask][0],dp[mask][cur]+graph[cur][next])
    //    从cur位置去客户next
    //    int next_mask = mask|1<<(next-1)
    //    dp[next_mask][next]=min(dp[next_mask][next],dp[mask][cur]+graph[cur][next])
    vector<vector<int>> dp(1 << N, vector<int>(N+1, INT_MAX));
    dp[0][0] = 0;
    // 状态DP 确定走完所有景点之后并在最终位置的时间
    for (int mask = 0; mask < (1 << N); mask++) {
        for (int cur = 0; cur <= N; cur++) {
            if (dp[mask][cur] != INT_MAX) {
                for (int next = 0; next <= N; next++) {
                    if (graph[cur][next] == -1) {
                        continue;
                    }
                    if (next == 0) {
                        dp[mask][next] = min(dp[mask][next], dp[mask][cur] + graph[cur][next]);
                    } else {
                        // 状态转移
                        int next_maks = mask | (1 << (next - 1));
                        dp[next_maks][next] = min(dp[next_maks][next], dp[mask][cur] + graph[cur][next]);
                    }
                }
            }
        }
    }

    // 从终点回到起点
    int end = (1 << N) -1;
    int res = INT_MAX;
    for (int i = 0; i <= N; i++) {
        if (dp[end][i] != INT_MAX && graph[i][0] != -1) {
            res = min(res, dp[end][i] + graph[i][0]);
        }
    }
    cout << res;
    return 0;
}
