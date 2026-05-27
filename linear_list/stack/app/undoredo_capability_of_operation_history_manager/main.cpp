#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

// 切割函数
vector<string> split(const string& str, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start));
    return result;
}

string executeCommand(vector<vector<string>>& commands) {
    //执行=没有可以被重做的内容 此命令可以被撤销
    //被撤销=可以被重做 被重做=可以被撤销
    stack<string> undoStack;   // 撤销栈（存储历史命令）可以被撤销的命令
    stack<string> redoStack;   // 重做栈 可以被恢复的命令
    
    for (auto& command : commands) {
        if (command.empty()) continue;
        
        if (command[0] == "execute") {
            // 执行新命令：清空重做栈，压入撤销栈
            while (!redoStack.empty()) {
                redoStack.pop();
            }
            undoStack.push(command[1]);
        } 
        else if (command[0] == "undo") {
            // 撤销：如果撤销栈为空，说明从未执行任何操作
            if (undoStack.empty()) {
                return "undo failed";
            }
            // 将当前状态移到重做栈
            string current = undoStack.top();
            undoStack.pop();
            redoStack.push(current);
        } 
        else if (command[0] == "redo") {
            // 重做：如果重做栈为空，说明没有可重做的操作
            if (redoStack.empty()) {
                return "redo failed";
            }
            // 将重做栈的顶部移回撤销栈
            string next = redoStack.top();
            redoStack.pop();
            undoStack.push(next);
        }
    }
    
    // 返回当前操作描述
    if (undoStack.empty()) {
        return "";
    }
    return undoStack.top();//返回重做栈的顶
}

int main() {
    vector<string> inputs;
    string input;
    while (getline(cin, input)) {
        inputs.push_back(input);
    }
    
    vector<vector<string>> commands;
    for (int i = 0; i < inputs.size(); i++) {
        commands.push_back(split(inputs[i], ","));
    }
    
    string res = executeCommand(commands);
    cout << res;
    
    return 0;
}