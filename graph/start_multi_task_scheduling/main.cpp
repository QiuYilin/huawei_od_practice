#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <algorithm>

// 审题 拓扑排序带排序

// 通用split函数
std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // 添加最后一个部分
    result.push_back(str.substr(start));
    return result;
}

int main() {
  std::string line;
  std::getline(std::cin, line);
  auto relationships = split(line," ");
  for(auto r:relationships){

  }
  std::unordered_map<char, std::vector<char>> map;
  std::vector<int> indgree(26, 0);  // 入度得是刚刚好的现有节点
  std::unordered_set<char> nodes;
  bool isPrev = false;
  char next, prev;
  for(auto r:relationships){
    auto rr = split(r,"->");
    auto prev = rr[1];
    auto next = rr[0];
    indgree[next.c_str()[0]-'A']++;
    nodes.insert(next.c_str()[0]);
    nodes.insert(prev.c_str()[0]);
    map[prev.c_str()[0]].push_back(next.c_str()[0]);
  }
  // for (int i = 0; i < line.size(); i++) {
  //   if (std::isalpha(line[i])) {
  //     nodes.insert(line[i]);
  //     if (isPrev) {
  //       prev = line[i];
  //       indgree[next - 'A']++;
  //       map[prev].push_back(next);
  //       isPrev = false;
  //     } else {
  //       next = line[i];
  //       isPrev = true;
  //     }
  //   }
  // }
  std::queue<char> queue;
  for (int i = 0; i < indgree.size(); i++) {
    if (indgree[i] == 0 && nodes.find('A' + i) != nodes.end()) {
      queue.push('A' + i);  // 初始是字母序
    }
  }
  std::vector<char> result;  // 疑问String是否比char好
  while (!queue.empty()) {
    //REVIEW 此时queue中内容是同一层的
    int size = queue.size();
    std::vector<char> level;
    for (int j = 0; j < size; j++) {
      auto root = queue.front();
      queue.pop();
      
      result.push_back(root);
      auto nexts = map[root];
      for (int i = 0; i < nexts.size(); i++) {
        indgree[nexts[i] - 'A']--;
        if (indgree[nexts[i] - 'A'] == 0 &&
          nodes.find(nexts[i]) != nodes.end()) {
          level.push_back(nexts[i]);
        }
      }
    }
    std::sort(level.begin(),level.end());
    for(auto c: level){
      queue.push(c);
    }
  }
  for (int i = 0; i < result.size(); i++) {
    if (i > 0) {
      std::cout << " ";
    }
    std::cout << result[i];
  }
  std::cout << std::endl;
  return 0;
}



// #include <cstdio>
// #include<iostream>
// #include<vector>
// #include<string>
// #include <utility> 
// #include <sstream>
// #include<algorithm> 
// #include<map>
// using namespace std;

// // 通用split函数
// vector<string> split(const string& str, const string& delimiter) {
//     vector<string> result;
//     size_t start = 0;
//     size_t end = str.find(delimiter);
//     while (end != string::npos) {
//         result.push_back(str.substr(start, end - start));
//         start = end + delimiter.length();
//         end = str.find(delimiter, start);
//     }
//     // 添加最后一个部分
//     result.push_back(str.substr(start));
//     return result;
// }

// int main() {
//     string input;
//     getline(cin, input);
//     vector<string> relations = split(input, " ");
//     // 记录 依赖key 的其它任务应映射
//     map<string, vector<string>> depends;
//     // 记录指定任务所依赖的数量
//     map<string, int> dependCount;
    
//     int n = relations.size();
//     for (int i = 0; i < n; i++) {
//         vector<string> tmp = split(relations[i], "->");
//         string depend = tmp[0];
//         string depended = tmp[1];
//         dependCount[depend] += 1;
//         //REVIEW 要保证这个键存在 操作是+0
//         dependCount[depended] += 0;
//         depends[depended].push_back(depend);
//     }

//     vector<string> res;
    
//     vector<string> tmp;
//     for (auto p : dependCount) {
//         string taskId = p.first;
//         int count = p.second;
//         // 可以直接执行的
//         if (count == 0) {
//             tmp.push_back(taskId);
//         }
//     }

//     while (!tmp.empty()) {//REVIEW 涉及到排序 使用vec存储单层的vec
//         vector<string> newTmp;
//         // 按照字母进行排序
//         sort(tmp.begin(), tmp.end());
//         for (auto id : tmp) {
//             res.push_back(id);
//             // 更新被依赖任务的状态
//             for (string depend : depends[id]) {
//                 dependCount[depend]--;
//                 // 依赖服务全部启动完成之后 就能正常启动
//                 if (dependCount[depend] == 0) {
//                     newTmp.push_back(depend);
//                 }
//             }
//         }
//         tmp = newTmp;
//     }
    
//     // 按顺序输出
//     for (int i = 0; i < res.size(); i++) {
//         cout << res[i];
//         if (i != res.size() - 1) {
//             cout << " ";
//         }
//     }
//     return 0;
// }
