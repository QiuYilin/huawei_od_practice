// #include <iostream>
// #include <set>  //set的排序是字母顺序?
// #include <sstream>
// #include <string>
// #include <vector>

// using namespace std;
// // 关键字等于单词
// // 前缀

// vector<string> findpPrefixKeywords(vector<string>& commands, string prefix) {
//   vector<vector<string>> commands_v(commands.size());
//   for (int i = 0; i < commands.size(); i++) {
//     std::stringstream ss(commands[i]);
//     std::string command;
//     while (ss >> command) {
//       commands_v[i].push_back(command);
//     }
//   }
//   stringstream s2(prefix);

//   s2>>prefix;

//   set<string> result;
//   if (prefix == "") {
//     for (int i = 0; i < commands_v.size(); i++) {
//       if (!commands_v[i].empty()) {
//         result.insert(commands_v[i][0]);
//       }
//     }
//   } else {
//     for (int i = 0; i < commands_v.size(); i++) {
//       if (!commands_v[i].empty()&&commands_v[i][0]==prefix) {
//         if(commands_v[i].size()>=2){
//             result.insert(commands_v[i][1]);
//         }
//       }
//     }
//   }
//   return vector<string>(result.begin(),result.end());
// }

// int main() {
//   string prefix;
//   getline(cin, prefix);
//   vector<string> commands;
//   string input;
//   while (getline(cin, input)) {
//     commands.push_back(input);
//   }

//   vector<string> res = findpPrefixKeywords(commands, prefix);
//   // 输出结果
//   for (int i = 0; i < res.size(); i++) {
//     if (i != 0) {
//       cout << " ";
//     }
//     cout << res[i];
//   }
//   return 0;
// }

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;


// 去除字符串首尾空格
string trim(const string& str) {
    // 找到第一个不是空格的位置
    int left = 0;
    while (left < str.size() && str[left] == ' ') {
        left++;
    }

    // 如果全是空格
    if (left == str.size()) {
        return "";
    }

    // 找到最后一个不是空格的位置
    int right = str.size() - 1;
    while (right >= 0 && str[right] == ' ') {
        right--;
    }

    // 截取中间部分
    return str.substr(left, right - left + 1);
}


vector<string> findpPrefixKeywords(vector<string> &commands, string prefix) {
    prefix = trim(prefix);

    vector<string> key;
    for (auto& command : commands) {
        // 优先去除首尾空格
        string s = trim(command);
        // 不能进行匹配或者匹配之后无后续关键字
        if (s.size() <= prefix.size()) {
            continue;
        }
        // 判断是否能匹配
        if (s.substr(0, prefix.size()) != prefix) {
            continue;
        }
        // 找关键字
        string remainng = s.substr(prefix.size());
        // 去除首尾空格
        remainng = trim(remainng);
        // 找到首个空格位置
        size_t  pos = remainng.find(' ');
        string word = (pos == string::npos) ? remainng : (remainng.substr(0, pos));
        if (!word.empty()) {
            key.push_back(word);
        }
    }
    if (key.empty()) {
        return {};
    }
    // 排序去重
    sort(key.begin(), key.end());
    vector<string> res;
    res.push_back(key[0]);
    for (int i = 1; i < key.size(); i++) {
        if (key[i] != key[i-1]) {
            res.push_back(key[i]);
        }
    }
    return res;
}

int main() {
    string prefix;
    getline(cin, prefix);
    vector<string> commands;
    string input;
    while (getline(cin, input)) {
        commands.push_back(input);
    }

    vector<string> res = findpPrefixKeywords(commands, prefix);
    // 输出结果
    for (int i = 0; i < res.size(); i++) {
        if (i != 0) {
            cout << " ";
        }
        cout << res[i];
    }
    return 0; 
}



