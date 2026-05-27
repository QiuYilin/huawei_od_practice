#include <algorithm>
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

string resolutionSort(string& input) {
  stringstream ss(input);
  string r;
  std::vector<std::vector<int>> result;
  while (ss >> r) {
    stringstream r_s(r);
    string w, h;
    getline(r_s, w, 'x');
    getline(r_s, h, 'x');
    int w_i = stoi(w);
    int h_i = stoi(h);
    int c = 0;
    if (w_i >= 3840 && h_i >= 2160) {
      c = 3;
    } else if (w_i >= 2560 && h_i >= 1440) {
      c = 2;
    } else if (w_i >= 1920 && h_i >= 1080) {
      c = 1;
    } else {
      c = 0;
    }
    result.push_back({w_i, h_i, c});
  }
  sort(result.begin(), result.end(), [](vector<int> a, vector<int> b) {
    int w_a = a[0];
    int w_b = b[0];
    int h_a = a[1];
    int h_b = b[1];
    int c_a = a[2];
    int c_b = b[2];
    int area_a = w_a*h_a;
    int area_b = w_b*h_b;
    if (c_a > c_b) {
      return true;
    } else if (c_a==c_b) {
      if(area_a>area_b){
        return true;
      }
      else if(area_a==area_b){
        return w_a>w_b? true:false;
      }else{
        return false;
      }
    } else {
      return false;
    }
  });
  std::string result_s;
  for(int i=0;i<result.size();i++){
    if(i!=0){
        result_s+=" ";
    }
    result_s+=to_string(result[i][0]);
    result_s+="x";
    result_s+=to_string(result[i][1]);
  }
  return result_s;
}

int main() {
  string input;
  getline(cin, input);
  string res = resolutionSort(input);
  cout << res;
  return 0;
}
