// #include <algorithm>
// #include <iostream>
// #include <vector>
// // 规律 优先当前时间点积分最高的 其次找下一个时间积分最高的
// int main() {
//   int task_n;
//   std::cin >> task_n;
//   int time;
//   std::cin >> time;
//   // 疑问用什么数据结构
//   std::vector<std::vector<int>> tasks(
//       time + 1, std::vector<int>());  // 疑问 要不要优先级队列
//   for (int i = 0; i < task_n; i++) {
//     int t, s;
//     std::cin >> t >> s;
//     if(t<=time){
//       tasks[t].push_back(s);
//     }
//   }
//   for (int i = 1; i < tasks.size(); i++) {
//     std::sort(tasks[i].begin(), tasks[i].end(), [](int a, int b) {
//       if (a > b) {
//         return true;//REVIEW 返回布尔值
//       } else {
//         return false;
//       }
//     });
//   }
//   int result = 0;
//   for (int i = 1; i < time + 1; i++) {
//     if (!tasks[i].empty()) {
//       result += tasks[i].front();
//     } else {
//       int j = i + 1;
//       while (j < tasks.size() && tasks[j].empty()) {
//         j++;
//       }
//       if (j < tasks.size()) {
//         result += tasks[j].front();
//         tasks[j].erase(tasks[j].begin());
//       }
//     }
//   }
//   std::cout << result << std::endl;
//   return 0;
// }

//REVIEW 不一定当前时间点的最大值就是最大的 
// 1 10   (时间1，积分10)
// 1 20   (时间1，积分20)
// 2 100  (时间2，积分100)
// 3 90   (时间3，积分90)
// 3 80   (时间3，积分80)
// 也不能仅因为后面时间点有更大积分就直接抛弃当前时间点
// 1 10   (时间1，积分10)
// 1 90   (时间1，积分20)
// 2 100  (时间2，积分100)
// 3 20   (时间3，积分90)
// 3 80   (时间3，积分80)

//REVIEW 规律

#include<iostream>
#include <iterator>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<list>
#include<queue>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;
    vector<pair<int, int>> ans(n);//保存所有任务 附带时间和积分信息
    for (int i = 0; i < n; i++) {
        int dielineTime, score;
        cin >> dielineTime >> score;
        ans[i] = {dielineTime, score};
    }
    // 按照结束时间排序
    sort(ans.begin(), ans.end());

    int res = 0;
    int currentTime = 0;//REVIEW 用于处理同一天的情况
    //REVIEW 做一个大小上限是t的优先级队列 小顶堆
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int i = 0; i < ans.size(); i++) {
        pair<int, int> ele = ans[i];
        int endTime = ele.first;
        int score = ele.second;
        // 当前时间小于结束时间时，可以直接进行判断
        if (endTime > currentTime) {
            //REVIEW 如果当前已选择的任务数量还没有达到可用时间总数，就直接把这个新任务加入选择
            if (minHeap.size() < t) {
                minHeap.push(ele.second);
            } else {
                // 替换之前获得积分少的工作
                int minValue = minHeap.top();
                if (minValue < ele.second) {
                    minHeap.pop();
                    minHeap.push(ele.second);
                }
            }
            currentTime++;  
        } else {//REVIEW 如果是同一天的 必须和之前的比较
            if (minHeap.empty()) {
                continue;
            }
            //尝试替换之前工作积分少的
            int minValue = minHeap.top();
            if (score > minValue) {
                minHeap.pop();
                minHeap.push(score);
            }
        } 
    }

    while (!minHeap.empty()) {
        res += minHeap.top();
        minHeap.pop();
    }
    cout << res;
}
