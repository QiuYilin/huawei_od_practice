#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <map>
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

string featureExtraction(vector<string>& docs) {
  // 有几个片段包含 最小出现次数
  std::vector<int> count(26);
  std::vector<int> min(26,INT_MAX);
  for (int i = 0; i < 26; i++) {
    //std::cout << "al " << to_string('a'+i) << std::endl;
    for (int j = 0; j < docs.size(); j++) {     
      int appear = std::count(docs[j].begin(), docs[j].end(), 'a' + i);
      if (appear > 0) {
        count[i]++;
        min[i] = std::min(min[i], appear);
      }
    }
  }
  string result;
  for (int i = 0; i < 26; i++) {
    if (count[i] == docs.size()) {
      for (int j = 0; j < min[i]; j++) {
        result.push_back('a' + i);
      }
    }
  }
  return result;
}

int main() {
  string input;
  getline(cin, input);
  vector<string> docs = split(input, " ");
  string res = featureExtraction(docs);
  cout << res;
  return 0;
}
