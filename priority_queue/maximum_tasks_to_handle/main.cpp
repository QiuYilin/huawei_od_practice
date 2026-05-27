// #include <iostream>

// #include <vector>

// #include <queue>

// //12  234  34  怎么处理重叠部分？？  12 34  234
// //贪心 优先处理时间段最短的？
// class cmp{
// public:
//     bool operator() (std::pair<int,int> a,std::pair<int,int> b){
//         int a_l = a.second-a.first;
//         int b_l = b.second-b.first;
//     }
// };


// int main(){
//     int n = 0;
//     std::cin >> n;
//     std::vector<std::pair<int,int>> tasks(n);
//     std::priority_queue<std::vector<std::pair<int,int>>,std::pair<int,int>,cmp> pri_queue;
//     for(int i=0;i<n;i++){
//         int prev,next;
//         std::cin >> prev >> next;
//         tasks[i].first  = prev;
//         tasks[i].second = next;
//     }

//     return 0;
// }

#include <iostream>
#include <vector>
#include <queue>
#include<utility>
#include <functional>

using namespace std;


// REVIEW 比较函数，用于优先队列根据任务的结束时间进行排序
struct compare {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) {
        return a.second > b.second;
    }
};

int main() {
    int n;
    cin >> n; // 读取任务的总数

    //REVIEW 容器一：一维：起始时间  二维：具体时间段
    vector<vector<pair<int,int>>> tasks(100001);

    
    for (int i = 0; i < n; i++) {
        int startTime, endTime;
        cin >> startTime >> endTime;
        tasks[startTime].emplace_back(startTime, endTime);
    }
   
    priority_queue<pair<int,int>, vector<pair<int,int>>, compare> pq;
    // 结果
    int ans = 0; 

    //REVIEW 遍历每个时间点
    for (int i = 0; i < 100001; i++) {
        // 移除超过终止时间的任务
        while (!pq.empty() && pq.top().second < i) {
            pq.pop();
        }

        // 开始时间为现在的任务入队
        for (const pair<int,int> task : tasks[i]) {
            pq.push(task);
        }

        // 完成任务数加一
        if (!pq.empty()) {
            ans++;
            pq.pop();
        }
    }

    cout << ans << endl; 
    return 0;
} 
