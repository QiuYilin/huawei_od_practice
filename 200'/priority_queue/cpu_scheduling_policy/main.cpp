#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
#include<queue>
using namespace std;

//REVIEW 时间线+优先队列  模拟当前时间点的跳跃

struct Task{
    int id;
    int priority;
    int executeTime;
    int arriveTime;

    Task(int id, int priority, int executeTime, int arriveTime):id(id),priority(priority),executeTime(executeTime),arriveTime(arriveTime) {}
};



// 自定义比较函数：
struct CompareTask {
    bool operator()(const Task& a, const Task& b) const {
        if (a.priority == b.priority) {
            return a.arriveTime > b.arriveTime;  // 到达时间 小的优先
        }
        return a.priority < b.priority;  // priority 大的优先
    }
};


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
    vector<Task> tasks;
    string input;
    while (getline(cin, input)) {
        if (input.empty()) {
            break;
        }
        vector<int> arr = split(input, " ");
        tasks.push_back({arr[0], arr[1], arr[2], arr[3]});
    }
    // 使用优先队列
    priority_queue<Task, vector<Task>, CompareTask> pq;
    int n = tasks.size();
    int index = 0;
    pq.push(tasks[index]);
    index++;

    int currentTime = pq.top().arriveTime;//REVIEW 初始时间是第一个任务的到达时间
    while (index < n) {//遍历所有任务 逐步加入优先队列
        Task currentTask = pq.top();
        pq.pop();//取出当前任务 按不同情况 可能执行更优先的任务 重新加入剩余时间等待的任务或者  从等待队列中取
        Task nextTask = tasks[index];
        index++;
        
        int currentTaskEndTime = currentTime + currentTask.executeTime;
        // 当前任务执行结束时间 大于下一个任务到达时间, 更新剩余执行时间. 优先级抢占等问题统一让优先队列处理
        if (currentTaskEndTime > nextTask.arriveTime) {
            currentTask.executeTime -= nextTask.arriveTime - currentTime;
            currentTime = nextTask.arriveTime;
            pq.push(currentTask);
        // 当前栈顶元素可以执行完成
        } else {
            cout << currentTask.id << " " << currentTaskEndTime << endl;
            currentTime = currentTaskEndTime;
            // 当前执行任务执行完成时间和下一个任务到达时间之前空闲时间, 此时优先队列中存在的任务就是等待任务,让其中优先级最高执行,充分利用空闲时间
            if (nextTask.arriveTime > currentTime) {
                while (!pq.empty()) {
                    Task idleTask = pq.top();
                    pq.pop();
                    int ideleTaskEndTime = currentTime + idleTask.executeTime;
                    // 同上
                    if (ideleTaskEndTime > nextTask.arriveTime) {
                        idleTask.executeTime -= nextTask.arriveTime - currentTime;
                        pq.push(idleTask);
                        break;
                    // 同上    
                    } else {
                       cout << idleTask.id << " " << ideleTaskEndTime << endl;
                       currentTime = ideleTaskEndTime;
                    }
                }
                currentTime = nextTask.arriveTime;
            }
        }
        // 入对
        pq.push(nextTask);
    }
    // 剩余未执行任务都在队列中,不存在抢占问题,直接按照优先队列安排输出即可
    while (!pq.empty()) {
        Task currentTask = pq.top();
        pq.pop();
        int currentTaskEndTime = currentTime + currentTask.executeTime;
        cout << currentTask.id << " " << currentTaskEndTime << endl;
        currentTime = currentTaskEndTime;
    }
    return 0;
}


