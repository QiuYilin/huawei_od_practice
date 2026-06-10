#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
#include<stack>
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

vector<int> StatPortRates(vector<int>& portRates) {
  vector<int> result(portRates.size(),0);
  stack<int> stack;
  for(int i=0;i<portRates.size();i++){
    while(!stack.empty()&&portRates[i]>portRates[stack.top()]){
        result[stack.top()]=i-stack.top();
        stack.pop();
    }
    stack.push(i);
  }
  return result;
}

int main() {
    string input;
    getline(cin, input);
    vector<int> portRates = split(input, ",");

    vector<int> ratesStat = StatPortRates(portRates);
    // 输出结果
    int n = ratesStat.size();
    for (int i = 0; i < n; i++) {
        cout << ratesStat[i];
        if (i != n - 1) {
            cout << ",";
        }
    }
    return 0;
}


