#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <algorithm> // 使用 remove_if

using namespace std;

int main() {
    int numberOfRows, numberOfColumns;
    cin >> numberOfRows >> numberOfColumns;
    cin.ignore(); // 忽略换行符

    vector<queue<int>> queueList;
    string inputLine;

    // 读取输入，每行数据存入队列
    while (getline(cin, inputLine) && !inputLine.empty()) {
        istringstream iss(inputLine);
        queue<int> numberQueue;
        int number;
        while (iss >> number) {//REVIEW 按空格切割不需要使用getline
            numberQueue.push(number);
        }
        queueList.push_back(numberQueue);
    }

    vector<int> matrix(numberOfColumns * numberOfRows, 0);//REVIEW 一维数组可以解决列表元素不足的问题
    int matrixIndex = 0;
    int queueIndex = 0;

    // 处理矩阵填充
    while (matrixIndex < matrix.size()) {
        // 每个列表每次最多选取numberOfRows个元素
        for (int i = 0; i < numberOfRows; ++i) {
            if (!queueList[queueIndex].empty()) {
                matrix[matrixIndex++] = queueList[queueIndex].front();
                queueList[queueIndex].pop();
                if (matrixIndex >= matrix.size()){
                    break;
                }
            } else {
                break;
            }
            
        }
        // 移动到下一个队列
        queueIndex = (queueIndex + 1) % queueList.size();
    }

    // 按列优先顺序输出矩阵
    for (int row = 0; row < numberOfRows; ++row) {
        for (int col = 0; col < numberOfColumns; ++col) {
            cout << matrix[col * numberOfRows + row] << " ";
        }
    }

    return 0;
}

