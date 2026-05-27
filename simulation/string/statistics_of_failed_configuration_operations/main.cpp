#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;

// 通用 切割函数 函数 将字符串str根据delimiter进行切割
vector<string> split(const string& str, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // 添加最后一个部分
    result.push_back(str.substr(start));
    return result;
}

bool judegeNumber(string& s) {
    // 1. 不能为空
    if (s.empty()) return false;

    // 2. 判断是否全是数字
    for (char c : s) {
        if (!isdigit(c)) return false;
    }

    // 3. 转成整数
    int num = stoi(s);

    // 4. 判断范围
    return num >= 1 && num <= 9999;
}

int main() {
    int errorCount = 0;
    map<string, string> ruleIndex;
    string tmp;
    while (getline(cin, tmp)) {
        vector<string> cmd = split(tmp, " ");
        // 关键字数量不对
        if (cmd.size() != 2 && cmd.size() != 3) {
            errorCount++;
            continue;
        }
        string operatorCmd = cmd[0];
        if (operatorCmd == "del_rule") {
            // 操作命令数量不对
            if (cmd.size() != 2) {
                errorCount++;
                continue;
            }
        
            vector<string> idPropertys = split(cmd[1], "=");
            // 数量不对
            if (idPropertys.size() != 2) {
                errorCount++;
                continue;
            }

            // 属性关键字不对
            if (idPropertys[0] != "rule_id") {
                errorCount++;
                continue;
            }
            string id = idPropertys[1];
            // 范围不对
            if (!judegeNumber(id)) {
                errorCount++;
                continue;
            }
            // 未添加
            if (ruleIndex.find(id) == ruleIndex.end()) {
                errorCount++;
                continue;
            }
            // 操作成功移除
            ruleIndex.erase(id);

        }  else if (operatorCmd == "mod_rule" || operatorCmd == "add_rule"){
            // 操作命令数量不对
            if (cmd.size() != 3) {
                errorCount++;
                continue;
            }
            vector<string> idPropertys = split(cmd[1], "=");
            vector<string> indexPropertye = split(cmd[2], "=");
            // 数量不对
            if (idPropertys.size() != 2 || indexPropertye.size() != 2) {
                errorCount++;
                continue;
            }
            // 属性关键字不对
            if (idPropertys[0] != "rule_id" || indexPropertye[0] != "rule_index") {
                errorCount++;
                continue;
            }
            string id = idPropertys[1];
            string index = indexPropertye[1];
            // 取值范围不对
            if (!judegeNumber(id) || !judegeNumber(index)) {
                errorCount++;
                continue;   
            }

            // 处理增加和修改逻辑
            if (operatorCmd == "mod_rule") {
                // 还没创建或者前后无变化
                if (ruleIndex.find(id) == ruleIndex.end() || ruleIndex[id] == index) {
                    errorCount++;
                    continue;
                }
                // 正常处理修改
                ruleIndex[id] = index;
            } else {
                // 已经创建
                if (ruleIndex.find(id) != ruleIndex.end()) {
                    errorCount++;
                    continue;
                }     
                ruleIndex[id] = index;          
            }



        //操作关键字不对      
        }  else {
            errorCount++;
        }


    }

    cout << errorCount;
    return 0;
}
