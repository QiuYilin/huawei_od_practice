// #include <iostream>
// #include <vector>
// #include <regex>
// //审题 单词中不包括元音字符 将单词首尾字符进行对换
// int main(){
//     std::vector<std::string> words;
//     std::string w;
//     while(std::cin >> w){
//         words.push_back(w);
//     } 
//     for(int i=0;i<words.size();i++){
//         std::regex pattern("[aeiouAEIOU]");
//         //std::regex_replace(words[i],pattern,"*");//REVIEW  regex_replace的返回不是bool
//         std::smatch matchs;
//         std::regex_search(words[i],matchs,pattern);
//     }
//     return 0;
// }

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<list>
#include<queue>
#include<map>
#include<set>
#include <regex>
using namespace std;

// 通用 split 函数
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

int main() {
    string s;
    getline(cin, s);

    // 正则表达式匹配小写元音字母
    regex pattern("[aeiouAEIOU]");
    vector<string> ans = split(s, " ");
    int n = ans.size();
    for (int i = 0; i < n; i++) {
        string tmp = ans[i];
        // 包含元音字母 替换
        if (regex_search(tmp, pattern)) {
            tmp = regex_replace(tmp, pattern, "*");
        // 不包含交换首尾字符    
        } else {
            swap(tmp[0], tmp[tmp.size() - 1]);//REVIEW 注意用swap简化
        }
        ans[i] = tmp;
    }

    // 输出
    for (int i = 0; i < n; i++) {
        cout << ans[i];
        if (i != n-1) {
            cout << " ";
        }
    }
    return 0;
}
