#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

// 检查 vector 中是否有引擎处于未激活状态（即状态为 -1）
bool hasInactiveEngines(const vector<int>& engineStatuses) {
    return find(engineStatuses.begin(), engineStatuses.end(), -1) != engineStatuses.end();
}

// 激活指定引擎的相邻引擎
void activateAdjacentEngines(vector<int>& engineStatuses, int currentEngine, int activationTime, int totalEngines) {
    int leftEngine = currentEngine == 0 ? totalEngines - 1 : currentEngine - 1; // 计算左边相邻引擎的索引
    int rightEngine = currentEngine == totalEngines - 1 ? 0 : currentEngine + 1; // 计算右边相邻引擎的索引
    if (engineStatuses[leftEngine] == -1) {
        engineStatuses[leftEngine] = activationTime; // 若左引擎未激活，则激活
    }
    if (engineStatuses[rightEngine] == -1) {
        engineStatuses[rightEngine] = activationTime; // 若右引擎未激活，则激活
    }
}

// 更新所有引擎的激活状态，直到所有引擎都被激活
void updateEngineStatuses(vector<int>& engineStatuses, int startTime) {
    bool continueUpdate = true;
    while (continueUpdate) {
        for (size_t i = 0; i < engineStatuses.size(); i++) {
            if (engineStatuses[i] == startTime) {
                activateAdjacentEngines(engineStatuses, i, startTime + 1, engineStatuses.size()); // 激活当前引擎的相邻引擎
            }
        }
        startTime++; // 增加时间步长，检查下一个时间点
        continueUpdate = hasInactiveEngines(engineStatuses); // 检查是否还有未激活的引擎
    }
    int lastActivationTime = *max_element(engineStatuses.begin(), engineStatuses.end()); // 获取最后一个被激活的时间
    int countActiveEngines = count(engineStatuses.begin(), engineStatuses.end(), lastActivationTime); // 计算最后激活时间的引擎数量
    cout << countActiveEngines << endl; // 输出最后激活时间的引擎数量
    for (size_t i = 0; i < engineStatuses.size(); i++) {
        if (engineStatuses[i] == lastActivationTime) {
            cout << i << " "; // 输出最后激活时间的引擎编号
        }
    }
    cout << endl;
}

int main() {
    string input;
    while (getline(cin, input)) {
        stringstream ss(input);
        int numberOfEngines, numberOfEntries;
        ss >> numberOfEngines >> numberOfEntries;

        vector<int> engineStatuses(numberOfEngines, -1); // 初始状态设置所有引擎为未激活
        int earliestActivation = numeric_limits<int>::max(); // 设置最早的激活时间为最大值

        for (int i = 0; i < numberOfEntries; i++) {
            getline(cin, input);
            stringstream ss2(input);
            int activationTime, engineIndex;
            ss2 >> activationTime >> engineIndex;
            engineStatuses[engineIndex] = activationTime; // 设置激活时间
            earliestActivation = min(earliestActivation, activationTime); // 更新最早的激活时间
        }
        updateEngineStatuses(engineStatuses, earliestActivation); // 根据最早的激活时间开始更新状态
    }
    return 0;
}