// #include <algorithm>
// #include <iostream>
// #include <sstream>
// #include <vector>
// // 审题 和普通优先级队列有啥区别 同等级情况下
// // 如果后续有等级更高的  前面相同等级就会颠倒顺序

// int main() {
//   std::string input;
//   std::cin >> input;
//   std::string e;
//   std::vector<int> inputs;
//   std::stringstream ss(input);
//   while (std::getline(ss, e, ',')) {
//     inputs.push_back(std::stoi(e));
//   }
//   std::vector<int> indexs(inputs.size());
//   for (int i = 0; i < inputs.size(); i++) {
//     indexs[i] = i;
//   }
//   //REVIEW 离线索引数组是为了恢复输出排序前的打印顺序
//   std::sort(indexs.begin(), indexs.end(),
//             [inputs](int a, int b) {  // 疑问 有点忘了捕获列表了
//               if (inputs[a] < inputs[b]) {
//                 return false;
//               } else if (inputs[a] > inputs[b]) {
//                 return true;
//               }
//               else {
//                 int c = std::max(a, b);
//                 for (int i = c + 1; i < inputs.size(); i++) {
//                   if (inputs[i] > inputs[a]) {
//                     return a < b;
//                   }
//                 }
//                 return a > b;
//               }
//             });

//   for (int i = 0; i < indexs.size(); i++) {
//     if (i != 0) {
//       std::cout << ",";
//     }
//     std::cout << indexs[i];
//   }
//   std::cout << std::endl;
//   return 0;
// }


#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <utility>
#include <sstream>
#include <algorithm>

using namespace std;

//REVIEW 要习惯把优先队列看成参照表
// 通用 split 函数
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

int main() {
    string s;
    getline(cin, s);
    vector<string> ans = split(s, ",");
    
    int n = ans.size();
    // 使用优先队列（最大堆）来判断是否有优先级更高的
    // priority_queue 默认是最大堆（降序）
    priority_queue<char> pq;
    
    //REVIEW 同时需要两个容器 一个是保存了<值，索引>的队列  一个是只按值排名的优先队列
    //用队列模拟任务排到末尾的逻辑
    queue<pair<char, int>> lst;
    for (int i = 0; i < n; i++) {
        lst.push({ans[i][0], i});
        pq.push(ans[i][0]);
    }
    
    int index = 0;
    vector<int> res(n, -1);
    
    while (!lst.empty()) {
        pair<char, int> p1 = lst.front();
        lst.pop();
        char c = pq.top();
        
        // 当前优先级为最大值，直接输出
        if (c == p1.first) {
            res[p1.second] = index++;//REVIEW 最终表现是对应索引位置复制 index+1
            pq.pop();
        } else {
            lst.push(p1);
        }
    }
    
    // 打印输出
    for (int i = 0; i < n; i++) {
        cout << res[i];
        if (i != n - 1) {
            cout << ",";
        }
    }
    cout << endl;
    
    return 0;
}