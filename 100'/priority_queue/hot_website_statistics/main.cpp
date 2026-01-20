// #include <iostream>
// #include <queue>
// #include <sstream>
// #include <unordered_map>
// #include <unordered_set>
// #include <algorithm>

// class cmp {
// public:
//     bool operator()(std::pair<std::string, int> a,
//                     std::pair<std::string, int> b) {
//         std::string website_a = a.first;
//         std::string website_b = b.first;

//         int a_count = a.second;
//         int b_count = b.second;

//         // REVIEW: 优先队列需要调整比较逻辑
//         if (a_count < b_count) {
//             return true;  // b的访问次数更大，b的优先级更高
//         } else if (a_count > b_count) {
//             return false; // a的访问次数更大，a的优先级更高
//         } else {
//             // 访问次数相同，按字典序
//             // REvIEW ：字典序小的优先级应该更高
//             return website_a > website_b;
//         }
//     }
// };

// int main() {
//     std::string line;
//     // 使用map和queue，但queue只用于查询时重建
//     std::unordered_map<std::string, int> map;
    
//     while (std::getline(std::cin, line)) {
//         if (line.empty()) continue;
        
//         // REVIEW : 更好的数字判断方式
//         bool isNumber = true;
//         for (char c : line) {
//             if (!std::isdigit(c)) {
//                 isNumber = false;
//                 break;
//             }
//         }
        
//         if (isNumber) {
//             int n = std::stoi(line);
            
//             // REVIEW : 与其每次都拷贝队列 不如每次查询时重新构建
//             std::priority_queue<std::pair<std::string, int>,
//                                 std::vector<std::pair<std::string, int>>, 
//                                 cmp> pri_queue;
            
//             // 将map中的数据放入优先队列
//             for (const auto& entry : map) {
//                 pri_queue.push(entry);
//             }
            
//             // 输出结果
//             std::vector<std::string> result;
//             for (int i = 0; i < n && !pri_queue.empty(); i++) {
//                 auto top = pri_queue.top();
//                 pri_queue.pop();
//                 result.push_back(top.first);
//             }
            
//             for (size_t i = 0; i < result.size(); i++) {
//                 if (i != 0) {
//                     std::cout << ",";
//                 }
//                 std::cout << result[i];
//             }
//             std::cout << std::endl;
            
//         } else {
//             // 是URL，更新计数
//             map[line]++;
//         }
//     }
//     return 0;
// }

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>

using namespace std;

string sortURL(int n, map<string, int>& cache);

int main() {
    map<string, int> cache; // 创建一个哈希表，用于存储每个 URL 出现的次数
    string line;
    while (getline(cin, line)) { // 不断读取输入，直到没有下一行
        if (regex_match(line, regex("^\\d+$"))) { //REVIEW 正则判断
            cout << sortURL(stoi(line), cache) << endl; 
            continue;
        }
        cache[line]++;
    }
    return 0;
}

string sortURL(int n ,map<string, int>& cache) {  
    vector<pair<string, int>> list(cache.begin(), cache.end()); //REVIEW 哈希转数组

    sort(list.begin(), list.end(), [](const pair<string, int>& a, const pair<string, int>& b) { // 对列表进行排序，按照计数从大到小排序，如果计数相同则按照字典序从小到大排序
        if (a.second != b.second) {
            return a.second > b.second;
        } else {
            return a.first < b.first;
        }
    });

    string res;
    for (int i = 0; i < n && i < list.size(); i++) { // 取出前 n 个 URL，并将它们拼接成一个字符串
        res += list[i].first + ",";
    }
    if (!res.empty()) { // 如果字符串不为空，则删除最后一个逗号
        res.pop_back();
    }
    return res; // 返回拼接好的字符串
}

