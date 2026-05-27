#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
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

void backtrack(std::vector<std::vector<string>>& result,
               std::vector<string>& path,
               std::unordered_map<string, int> indgree,
               std::unordered_map<string, bool> used, vector<string> name,
               std::unordered_map<string, std::vector<string>> dependencies) {
  if (path.size() == name.size()) {
    result.push_back(path);
    return;
  }
  for (auto it = indgree.begin(); it != indgree.end(); it++) {
    if ((*it).second == 0 && used[(*it).first] == false) {
      path.push_back((*it).first);
      used[(*it).first] = true;
      for (auto node = dependencies[(*it).first].begin();
           node != dependencies[(*it).first].end(); node++) {
        indgree[(*node)]--;
      }
      backtrack(result, path, indgree, used, name, dependencies);
      path.pop_back();
      for (auto node = dependencies[(*it).first].begin();
           node != dependencies[(*it).first].end(); node++) {
        indgree[(*node)]++;
      }
      used[(*it).first] = false;
    }
  }
}

vector<string> getAllBuid(vector<string>& name,
                          vector<vector<string>>& dependencyGraph) {
  std::unordered_map<string, int> indgree;
  std::unordered_map<string, bool> used;
  std::unordered_map<string, std::vector<string>> dependencies;
  //REVIEW 初始化
  for (const string& node : name) {
    indgree[node] = 0;
    used[node] = false;
  }
  for (int i = 0; i < dependencyGraph.size(); i++) {
    indgree[dependencyGraph[i][0]]++;
    dependencies[dependencyGraph[i][1]].push_back(dependencyGraph[i][0]);
  }
  std::vector<std::vector<string>> result;
  std::vector<string> path;
  backtrack(result, path, indgree, used, name, dependencies);
  std::vector<string> result2;
  for (int i = 0; i < result.size(); i++) {
    string path_s;
    for (int j = 0; j < result[i].size(); j++) {
      if (j != 0) {
        path_s += " ";
      }
      path_s += result[i][j];
    }
    result2.push_back(path_s);
  }

  sort(result2.begin(), result2.end());//REVIEW 排序
  return result2;
}

int main() {
  string input1;
  string input2;
  getline(cin, input1);
  getline(cin, input2);
  vector<string> name = split(input1, ",");
  vector<string> dependency = split(input2, " ");
  vector<vector<string>> dependencyGraph;
  for (int i = 0; i < dependency.size(); i++) {
    dependencyGraph.push_back(split(dependency[i], ","));
  }
  vector<string> res = getAllBuid(name, dependencyGraph);
  if (res.empty()) {
    cout << "NULL";
    return 0;
  }
  // 输出结果
  for (auto seq : res) {
    cout << seq << endl;
  }
  return 0;
}
