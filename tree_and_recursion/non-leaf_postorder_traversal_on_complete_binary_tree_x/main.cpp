// #include <iostream>
// //审题: 完全二叉树 后续遍历 不输出叶子
// int main(){
//     //预处理 怎么构造树？
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
//REVIEW 不需要构建二叉树 而是利用完全二叉树的性质
bool dfs(vector<string> &ans, int n, int pos, vector<string>& res) {
    if (pos >= n) {
        return false;
    }
    // 左节点的下标为 2 * pos  + 1
    bool left = dfs(ans, n, 2 * pos + 1, res);
    // 右节点的下标为 2 * pos + 2
    bool right = dfs(ans, n, 2 * (pos + 1), res);
    // 说明不是叶子节点
    if (left || right) {
        res.push_back(ans[pos]);
    }
    return true;
}


int main() {
    string input;
    getline(cin, input);

    vector<string> ans = split(input, " ");
    vector<string> res;
    int n = ans.size();
    if (n == 1) {
        cout << ans[0];
        return 0;
    }
    dfs(ans, n, 0, res);

    // 输出结果
    for (int i = 0; i < res.size(); i++) {
        cout << res[i];
        if (i != res.size() -1) {
            cout << " ";
        }
    }

    return 0;
}


