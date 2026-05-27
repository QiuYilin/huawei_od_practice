#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
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

bool isValid(string word){
  if(word.size()>50){
    return false;
  }
  for(auto c:word){
    if(!isalnum(c)&&c!='_'){
        return false;
    }
  }
  return true;
}
// review 出现顺序
vector<string> findAnomalyLogs(vector<string>& records) {
  // 日志标识由大小写字母、数字和下划线组成，长度不超过
  // 50。日志数量范围为[1,10000] 正则怎么表示？
  unordered_map<string, std::pair<int, int>> map;//REVIEW 可以拆成两个map
  for (int i = 0; i < records.size(); i++) {
    if (isValid(records[i])) {
      if(map.find(records[i])==map.end()){//REVIEW 首次出现
        map[records[i]].first = i;
      }
      map[records[i]].second++;
    }
  }
  std::vector<std::pair<string, std::pair<int, int>>> vec;
  for (auto it = map.begin(); it != map.end(); it++) {
    int count = (*it).second.second;
    if (count >= 3) {
      vec.push_back(*it);
    }
  }
  sort(vec.begin(), vec.end(),
       [](std::pair<string, std::pair<int, int>> a,
          std::pair<string, std::pair<int, int>> b) {
         int count_a = a.second.second;
         int count_b = b.second.second;
         int index_a = a.second.first;
         int index_b = b.second.first;
         if (count_a > count_b) {
           return true;
         } else if (count_a == count_b) {
           return index_a < index_b ? true : false;
         } else {
           return false;
         }
       });
  std::vector<string> result;
  for (auto e : vec) {
    result.push_back(e.first);
  }
  return result;
}

int main() {
  string input;
  getline(cin, input);
  vector<string> records = split(input, " ");

  vector<string> ans = findAnomalyLogs(records);
  // 输出结果
  if (ans.empty()) {
    cout << "NONE";
    return 0;
  }
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i];
    if (i != ans.size() - 1) {
      cout << " ";
    }
  }
  return 0;
}
