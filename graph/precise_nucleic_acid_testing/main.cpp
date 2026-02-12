// #include <algorithm>
// #include <iostream>
// #include <sstream>
// #include <vector>
// // 并查集模板题
// int find(std::vector<int>& father, const int u) {
//   if (u == father[u]) {
//     return u;
//   } else {
//     father[u] = find(father, father[u]);
//     return father[u];
//   }
// }

// bool isSame(std::vector<int>& father, int u, int v) {
//   u = find(father, u);
//   v = find(father, v);
//   if (u == v) {
//     return true;
//   } else {
//     return false;
//   }
// }

// void join(std::vector<int>& father, int u, int v) {
//   u = find(father, u);
//   v = find(father, v);
//   if (u == v) {
//     return;
//   } else {
//     father[v] = u;
//   }
// }

// int main() {
//   int n = 0;
//   std::cin >> n;
//   std::cin.ignore();
//   std::string line;  //REVIEW 病人的英文是patient
//   std::getline(std::cin, line);
//   std::vector<int> roots;
//   std::string root;
//   std::stringstream ss(line);
//   while (std::getline(ss, root, ',')) {
//     roots.push_back(std::stoi(root));
//   }
//   std::vector<std::vector<int>> grid(n, std::vector<int>());
//   for (int i = 0; i < n; i++) {
//     std::getline(std::cin, line);
//     ss = std::stringstream(line);
//     std::string p;
//     while (std::getline(ss, p, ',')) {
//       grid[i].push_back(std::stoi(p));
//     }
//   }  // 疑问这里写得臃肿了点

//   std::vector<int> father(n, 0);
//   for (int i = 0; i < n; i++) {
//     father[i] = i;
//   }
//   for (int i = 0; i < n; i++) {
//     for (int j = 0; j < n; j++) {
//       if (grid[i][j] == 1) {
//         join(father, i, j);
//       }
//     }
//   }
//   int result = 0;
//   for (int i = 0; i < n; i++) {
//     if (std::find(roots.begin(), roots.end(), i) != roots.end()) {
//       continue;
//     } 
//     else {
//       for (int j = 0; j < roots.size(); j++) {
//         if (isSame(father, roots[j], i)) {
//           result++;
//           break;
//         }
//       }
//     }
//     // for(int j=0;j<roots.size();j++){
//     //   if(i==roots[j]){
//     //     break;
//     //   }
//     //   else{
//     //     if(isSame(father,roots[j],i)){
//     //       result++;
//     //       break;
//     //     }
//     //   }
//     // } 疑问能总结出什么
//   }
//   std::cout << result << std::endl;
//   return 0;
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
using namespace std;

//REVIEW 可以借鉴的函数 输入是字符串和分割符 输出是数组
//利用find和substr函数
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

// 找到组中的代表人
int find(int a, vector<int> &ans) {
    if (ans[a] != a) {
        ans[a] = find(ans[a], ans);
    } 
    return ans[a]; 
}

//REVIEW min操作非必要
void merge(int a, int b, vector<int> &ans) {
    int rootA = find(a, ans);
    int rootB = find(b, ans);
    int newRoot = min(rootA, rootB);
    ans[rootA] = newRoot;
    ans[rootB] = newRoot;
}


int main() {
    int n;
    cin >> n;
    
    string confirm;
    // 忽略换行符
    cin.ignore();
    getline(cin, confirm);
    if (confirm.empty()) {
        cout << 0;
        return 0;
    }
    vector<int> confirmId = split(confirm, ",");
    vector<vector<int>> grid(n);
    for (int i = 0; i < n; i++) {
        string tmp;
        getline(cin, tmp);
        grid[i] = split(tmp, ",");
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j =0; j < i; j++) {//REVIEW 遍历一半对角线
            // 合并两个组
            if (grid[i][j] == 1) {
                merge(i, j, ans);
            }
        }
    }
    
    int res = 0;
    set<int> s;
    // 使用集合存储所有根
    for (int i = 0; i < confirmId.size(); i++) {
        s.insert(find(confirmId[i], ans));
    }
    
    for (int i = 0; i < n; i++) {
        // 处于密切接触组
        if (s.find(find(i, ans)) != s.end()) {//REVIEW 为什么要嵌套find
            res++;
        }
    }
    // 减去病例人数
    res -= confirmId.size();
    cout << res;
    return 0;
}
