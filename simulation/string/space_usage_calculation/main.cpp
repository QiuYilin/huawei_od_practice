#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    // 读取全部输入
    string allInput, line;
    while (getline(cin, line)) {
        if (!allInput.empty()) allInput += " ";
        allInput += line;
    }

    // 按空格分割所有token
    vector<string> tokens;
    istringstream iss(allInput);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        cout << endl;
        return 0;
    }

    // 第一个token是目标目录
    string targetDir = tokens[0];
    // 去除目标目录末尾的斜杠（保留根目录"/"的情况）
    while (targetDir.size() > 1 && targetDir.back() == '/') {
        targetDir.pop_back();
    }

    // 剩余token前半部分是文件路径，后半部分是文件大小
    int totalTokens = tokens.size() - 1;
    if (totalTokens <= 0 || totalTokens % 2 != 0) {
        cout << endl;
        return 0;
    }
    int fileCount = totalTokens / 2;

    vector<string> filePaths(fileCount);
    vector<long long> fileSizes(fileCount);
    for (int i = 0; i < fileCount; i++) {
        filePaths[i] = tokens[1 + i];
        fileSizes[i] = stoll(tokens[1 + fileCount + i]);
    }

    // 构造匹配前缀: targetDir + "/"
    string prefix = targetDir + "/";

    // 统计每个一级子项的空间占用
    map<string, long long> subItemSize;
    bool found = false;

    for (int i = 0; i < fileCount; i++) {
        const string& path = filePaths[i];
        // 检查文件是否在目标目录下
        if (path.substr(0, prefix.size()) == prefix) {
            found = true;
            // 提取一级子项名称：从prefix结束位置到下一个'/'或字符串末尾
            size_t start = prefix.size();
            size_t end = path.find('/', start);
            string subItem;
            if (end == string::npos) {
                subItem = path.substr(start);
            } else {
                subItem = path.substr(start, end - start);
            }
            if (!subItem.empty()) {
                subItemSize[subItem] += fileSizes[i];
            }
        }
    }

    // 目标目录不存在于文件系统中
    if (!found) {
        cout << endl;
        return 0;
    }

    // 找出最大空间占用值
    long long maxSize = 0;
    for (const auto& p : subItemSize) {
        if (p.second > maxSize) {
            maxSize = p.second;
        }
    }

    // 收集所有等于最大值的子项（map本身已按key升序排列）
    vector<string> result;
    for (const auto& p : subItemSize) {
        if (p.second == maxSize) {
            result.push_back(p.first);
        }
    }

    // 输出结果
    for (size_t i = 0; i < result.size(); i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;

    return 0;
}
