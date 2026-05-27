#include <iostream>
#include <queue>
#include <regex>
#include <unordered_map>

class Compare {
 public:
  bool operator()(std::pair<std::string, int> a,
                  std::pair<std::string, int> b) {
    if (a.second < b.second) {
      return false;
    } else if (a.second == b.second) {
      if (a.first > b.first) {
        return false;
      } else {
        return true;
      }
    } else {
      return true;
    }
  }
};

int main(){
  std::string e;
  std::unordered_map<std::string, int> map;
  std::regex r(R"([0-9]+)");
  while (std::cin >> e) {
    // 子问题判断url
    if (std::regex_match(e, r)) {
      // 输出
      int k = std::stoi(e);
      std::priority_queue<std::pair<std::string, int>,
                          std::vector<std::pair<std::string, int>>, Compare>
          queue;
      for (auto p = map.begin(); p != map.end(); p++) {
        if (queue.size() < k) {
          queue.push(*p);
        } else {
          if ((*p).second >= queue.top().second) {
            queue.push(*p);
            queue.pop();
          }
        }
      }
      std::vector<std::string> result;
      while (!queue.empty()) {
          result.push_back(queue.top().first);
          queue.pop();
      }
      std::reverse(result.begin(),result.end());
      for(int i=0;i<result.size();i++){
        if(i==0){
            std::cout << result[i];
        }
        else{
            std::cout << "," << result[i];
        }
      }
      std::cout << std::endl;
    } else {
      map[e]++;
    }
  }
  return 0;
}

// #include <iostream>
// #include <vector>
// #include <map>
// #include <algorithm>
// #include <regex>

// using namespace std;

// string sortURL(int n, map<string, int>& cache);

// int main() {
//     map<string, int> cache; // 创建一个哈希表，用于存储每个 URL 出现的次数
//     string line;
//     while (getline(cin, line)) { // 不断读取输入，直到没有下一行
//         if (regex_match(line, regex("^\\d+$"))) { //REVIEW 正则判断
//             cout << sortURL(stoi(line), cache) << endl; 
//             continue;
//         }
//         cache[line]++;
//     }
//     return 0;
// }

// string sortURL(int n ,map<string, int>& cache) {  
//     vector<pair<string, int>> list(cache.begin(), cache.end()); //REVIEW 哈希转数组

//     sort(list.begin(), list.end(), [](const pair<string, int>& a, const pair<string, int>& b) { // 对列表进行排序，按照计数从大到小排序，如果计数相同则按照字典序从小到大排序
//         if (a.second != b.second) {
//             return a.second > b.second;
//         } else {
//             return a.first < b.first;
//         }
//     });

//     string res;
//     for (int i = 0; i < n && i < list.size(); i++) { // 取出前 n 个 URL，并将它们拼接成一个字符串
//         res += list[i].first + ",";
//     }
//     if (!res.empty()) { // 如果字符串不为空，则删除最后一个逗号
//         res.pop_back();
//     }
//     return res; // 返回拼接好的字符串
// }

