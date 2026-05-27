#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
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

vector<string> hasSameHob(const vector<vector<string>>& nodes, int a, int b) {
  vector<string> result;
  bool head = true;
  for (int i = 1; i < nodes[a].size(); i++) {
    for (int j = 1; j < nodes[b].size(); j++) {
      //
      if (nodes[a][i] == nodes[b][j]) {
        result.push_back(nodes[a][i]);
      }
    }
  }
  return result;
}

// REVIEW id可以前后跳 可达性问题
vector<vector<string>> queryFriends(vector<vector<string>>& nodes,
                                    vector<vector<string>>& relations,
                                    string myId, int maxHop) {
  vector<vector<string>> result;
  vector<int> indgree(nodes.size(), 0);
  vector<vector<int>> graph(nodes.size());
  vector<bool> used(nodes.size(), false);
  for (int i = 0; i < relations.size(); i++) {
    int prev = stoi(relations[i][1]);
    int next = stoi(relations[i][0]);
    graph[prev].push_back(next);
    //graph[next].push_back(prev);
  }
  for (int i = 0; i < graph.size(); i++) {
    sort(graph[i].begin(), graph[i].end());
  }
  for (int i = 0; i < nodes.size(); i++) {
    sort(nodes[i].begin() + 1, nodes[i].end());
  }
  queue<int> queue;
  queue.push(stoi(myId));
  used[stoi(myId)] = true;
  while (!queue.empty() && maxHop > 0) {
    int size = queue.size();
    for (int i = 0; i < size; i++) {
      auto front = queue.front();
      queue.pop();
      for (int j = 0; j < graph[front].size(); j++) {
        if (used[graph[front][j]] == false) {
          // 如果有交集就保存
          vector<string> path;
          auto hobs = hasSameHob(nodes, stoi(myId), graph[front][j]);//REVIEW 
          if (!hobs.empty()) {
            path.push_back(to_string(graph[front][j]));
            // 疑问 怎么把一个vector拼刀vector后面
            for (int k = 0; k < hobs.size(); k++) {
              path.push_back(hobs[k]);
            }
            result.push_back(path);
          }
          used[graph[front][j]] = true;
          queue.push(graph[front][j]);
        }
      }
    }
    maxHop--;
  }

  return result;
}

int main() {
  string input1, input2, myId, maxHopStr;
  getline(cin, input1);
  getline(cin, input2);
  getline(cin, myId);
  getline(cin, maxHopStr);

  vector<vector<string>> nodes;
  vector<string> tmp;
  if (!input1.empty()) {
    tmp = split(input1, " ");
    for (int i = 0; i < tmp.size(); i++) {
      nodes.push_back(split(tmp[i], ","));
    }
  }
  vector<vector<string>> relations;
  if (!input2.empty()) {
    tmp = split(input2, " ");
    for (int i = 0; i < tmp.size(); i++) {
      relations.push_back(split(tmp[i], ","));
    }
  }

  vector<vector<string>> res =
      queryFriends(nodes, relations, myId, stoi(maxHopStr));

  // 输出结果
  for (int i = 0; i < res.size(); i++) {
    vector<string> current = res[i];
    for (int j = 0; j < current.size(); j++) {
      if (j != 0) {
        cout << ",";
      }
      cout << current[j];
    }
    cout << endl;
  }
}
