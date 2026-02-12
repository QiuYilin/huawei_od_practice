// #include <algorithm>
// #include <iostream>
// #include <regex>
// #include <string>
// #include <vector>

// // REVIEW 一般stoi的01就是1
// int main() {
//   int n = 0;
//   std::cin >> n;
//   std::vector<std::string> input;
//   for (int i = 0; i < n; i++) {
//     std::string line;
//     std::getline(std::cin, line);
//     input.push_back(line);
//   }
//   //疑问 归并排序 不会影响输入顺序？
   //std::stable_sort(input.begin(), input.end(), [](std::string a, std::string b) {
//     std::regex r(
//         R"((\d+):(\d+):(\d+).(\d+))");  // review 正则表达式字符的斜杠方向同转义
//     std::smatch match_a, match_b;
//     std::regex_search(a, match_a, r);
//     std::regex_search(b, match_b, r);
//     if (std::stoi(match_a[1].str()) > std::stoi(match_b[1].str())) {
//       return true;
//     } else if (std::stoi(match_a[1].str()) < std::stoi(match_b[1].str())) {
//       return false;
//     } else {
//       if (std::stoi(match_a[2].str()) > std::stoi(match_b[2].str())) {
//         return true;
//       } else if (std::stoi(match_a[2].str()) < std::stoi(match_b[2].str())) {
//         return false;
//       } else {
//         if (std::stoi(match_a[3].str()) > std::stoi(match_b[3].str())) {
//           return true;
//         } else if (std::stoi(match_a[3].str()) < std::stoi(match_b[3].str())) {
//           return false;
//         } else {
//           if (std::stoi(match_a[4].str()) > std::stoi(match_b[4].str())) {
//             return true;
//           } else if (std::stoi(match_a[4].str()) <
//                      std::stoi(match_b[4].str())) {
//             return false;
//           } else {
//             //疑问 如何保持输入顺序
//           }
//         }
//       }
//     }
//   });
//   return 0;
// }

#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

/**
 * @brief 将时间戳字符串转换为毫秒数
 * @param timeStr 格式为 "HH:MM:SS.mmm" 的时间字符串
 * @return 以毫秒为单位的时间
 */
int parseTimestampToMilliseconds(const string &timeStr) {
    regex pattern(R"((\d+):(\d+):(\d+).(\d+))"); // 匹配 "HH:MM:SS.mmm" 格式
    smatch match;
    if (regex_search(timeStr, match, pattern)) {
        int hours = stoi(match[1]);
        int minutes = stoi(match[2]);
        int seconds = stoi(match[3]);
        int milliseconds = stoi(match[4]);
        return ((hours * 60 + minutes) * 60 + seconds) * 1000 + milliseconds;//REVIEW 换算成秒 避免繁琐比较
    }
    return 0; // 解析失败返回 0
}

int main() {
    int n;
    cin >> n;
    cin.ignore(); // 忽略换行符，防止影响 getline 读取

    vector<string> logs(n);
    for (int i = 0; i < n; i++) {
        getline(cin, logs[i]); // 读取完整日志行
    }

    // 使用稳定排序，确保相同时间戳的日志保持原顺序
    stable_sort(logs.begin(), logs.end(), [](const string &log1, const string &log2) {
        return parseTimestampToMilliseconds(log1) < parseTimestampToMilliseconds(log2);
    });//REVEIW 稳定排序的写法

    // 输出排序后的日志
    for (const string &log : logs) {
        cout << log << endl;
    }

    return 0;
}

