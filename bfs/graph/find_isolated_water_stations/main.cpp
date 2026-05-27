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
vector<int> split(const string& str, const string& delimiter) {
  vector<int> result;
  size_t start = 0;
  size_t end = str.find(delimiter);
  while (end != string::npos) {
    result.push_back(stoi(str.substr(start, end - start)));
    start = end + delimiter.length();
    end = str.find(delimiter, start);
  }
  // 添加最后一个部分
  result.push_back(stoi(str.substr(start)));
  return result;
}

// 通用 切割函数 函数 将字符串str根据delimiter进行切割
vector<string> splitStr(const string& str, const string& delimiter) {
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

vector<int> getIsolatStations(int n, vector<int>& sources,
                              vector<vector<int>>& pipes) {
  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < pipes.size(); i++) {
    graph[pipes[i][0]].push_back(pipes[i][1]);
    if (pipes[i][2] == 1) {
      graph[pipes[i][1]].push_back(pipes[i][0]);
    }
  }
  queue<int> queue;
  std::vector<bool> visited(n,false);
  for(auto i:sources){
    visited[i]=true;
    queue.push(i);
  }
  while(!queue.empty()){
    auto front = queue.front();
    queue.pop();
    for(int i=0;i<graph[front].size();i++){
        if(visited[graph[front][i]]==false){
            queue.push(graph[front][i]);
            visited[graph[front][i]]=true;
        }
    }
  }
  vector<int> result;
  for(int i=0;i<n;i++){
    if(visited[i]==false){
        result.push_back(i);
    }
  }
  return result;
}

int main() {
  int n;
  cin >> n;
  // 忽略空行
  cin.ignore();
  string input1;
  getline(cin, input1);
  vector<int> sources;
  if (!input1.empty()) {
    sources = split(input1, ",");
  }
  string input2;
  getline(cin, input2);
  vector<vector<int>> pipes;
  if (!input2.empty()) {
    vector<string> tmp = splitStr(input2, " ");
    for (int i = 0; i < tmp.size(); i++) {
      pipes.emplace_back(split(tmp[i], ","));
    }
  }

  vector<int> res = getIsolatStations(n, sources, pipes);

  // 输出结果
  for (int i = 0; i < res.size(); i++) {
    if (i != 0) {
      cout << ",";
    }
    cout << res[i];
  }
  return 0;
}
