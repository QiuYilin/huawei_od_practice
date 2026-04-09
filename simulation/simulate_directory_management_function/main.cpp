#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

// 将路径栈转换成字符串，如 ["abc", "efg"] -> "/abc/efg/"
string get_path_string(const vector<string>& path_stack) {
    if (path_stack.empty()) return "/";
    string result;
    for (const string& dir : path_stack) {
        result += "/" + dir;
    }
    return result + "/";
}

// 获取当前路径的字符串表示（不含末尾/），用于set键
string get_current_key(const vector<string>& path_stack) {
    if (path_stack.empty()) return "";
    string result;
    for (const string& dir : path_stack) {
        if (!result.empty()) result += "/";
        result += dir;
    }
    return result;
}

int main() {
    vector<string> path_stack; // REVIEW 用栈+所有绝对路径的set来模拟
    set<string> directories;   // 
    directories.insert("");    // 根目录
    
    vector<string> commands;
    string line;
    
    // 读取所有命令
    while (getline(cin, line)) {
        commands.push_back(line);
    }
    
    string output;
    
    for (const string& cmd_line : commands) {
        istringstream iss(cmd_line);
        string cmd, arg;
        iss >> cmd;//REVIEW 按照空格切割的方法 使用stringstream但是不需要getline
        
        if (cmd == "mkdir") {
            iss >> arg;
            // 参数必须是小写字母
            bool valid = true;
            for (char c : arg) {
                if (c < 'a' || c > 'z') {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;
            
            string parent_key = get_current_key(path_stack);
            string new_dir_key = parent_key.empty() ? arg : parent_key + "/" + arg;
            
            // 如果目录不存在，则创建
            if (directories.find(new_dir_key) == directories.end()) {
                directories.insert(new_dir_key);
            }
        }
        else if (cmd == "cd") {
            iss >> arg;
            if (arg == "..") {
                // 返回上级目录
                if (!path_stack.empty()) {
                    path_stack.pop_back();
                }
            } else {
                // 参数必须是小写字母
                bool valid = true;
                for (char c : arg) {
                    if (c < 'a' || c > 'z') {
                        valid = false;
                        break;
                    }
                }
                if (!valid) continue;
                
                string parent_key = get_current_key(path_stack);
                string target_key = parent_key.empty() ? arg : parent_key + "/" + arg;
                
                // 检查目录是否存在
                if (directories.find(target_key) != directories.end()) {
                    path_stack.push_back(arg);
                }
            }
        }
        else if (cmd == "pwd") {
            output = get_path_string(path_stack);
        }
        // 其他命令忽略
    }
    
    // 输出最后一条命令的结果
    if (!output.empty()) {
        cout << output << endl;
    }
    
    return 0;
}