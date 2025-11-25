#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int k;
    cin >> k;
    cin.ignore();
    string s;
    getline(cin, s);
    
    vector<string> commands;
    int i = 0;
    int n = s.length();
    
    while (i < n) {//REVIEW 使用完整的else链条而不是continue
        if (s[i] == '"') {//①遇到双引号
            // 处理双引号包围的命令字
            int j = i + 1;
            // 找到匹配的结束双引号
            while (j < n && s[j] != '"') {//REVIEW 直接双指针处理掉命令字
                j++;
            }
            if (j < n) {
                // 提取双引号内的内容（不包括双引号本身）
                string command = s.substr(i, j - i + 1);
                commands.push_back(command);
                i = j + 1;
            } 
            // else {
            //     // 没有匹配的结束双引号，按普通字符处理
            //     string command;
            //     command += s[i];
            //     commands.push_back(command);
            //     i++;
            // }
        } else if (s[i] == '_') {//②跳过连续下划线
            while (i < n && s[i] == '_') {
                i++;
            }
        } else {//③直接双指针处理普通命令字
            int start = i;
            while (i < n && s[i] != '_' && s[i] != '"') {
                i++;
            }
            string command = s.substr(start, i - start);
            commands.push_back(command);
        }
    }
    
    // 验证索引
    if (k < 0 || k >= commands.size()) {
        cout << "ERROR" << endl;
        return 0;
    }
    
    // 加密指定字段
    commands[k] = "******";
    
    // 构建结果字符串
    string result;
    for (int i = 0; i < commands.size(); i++) {
        if (i > 0) {
            result += "_";
        }
        result += commands[i];
    }
    
    cout << result << endl;
    return 0;
}