// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <climits>
// //审题：要给出具体组合->回溯->全排列
// //01背包？ 给不出具体序列
// //剪枝操作
// void backtrack(std::vector<int> input,std::vector<std::vector<int>> &result,std::vector<int> &path,std::vector<bool> &visited){
//   if(path.size()==input.size()){//疑问 要把升降写在回溯中吗
//     result.push_back(path);
//     return;
//   }
//   for(int i=0;i<input.size();i++){
//     if(visited[i]==true){
//       continue;
//     }
//     path.push_back(input[i]);
//     visited[i]=true;
//     backtrack(input,result,path,visited);
//     path.pop_back();
//     visited[i]=false;
//   }
// }
// int main(){
//   int height = 0,n=0;
//   std::cin >> height >> n;
//   std::vector<int> input(n,0);
//   for(int i=0;i<n;i++){
//     std::cin >> input[i];
//   }
//   std::vector<std::vector<int>> result;
//   std::vector<int> path;
//   std::vector<bool> visited(n,false); //REVIEW 全排列只需要关注枝去重
//   std::sort(input.begin(), input.end(), std::greater<int>());//REVIEW 大值优先
//   backtrack(input,result,path,visited);
  
//   std::vector<int> sums;
//   for(int i=0;i<result.size();i++){
//     int sum = 0;
//     for(int j=0;j<result[i].size();j++){
//       if(j%2==0){
//         sum+=result[i][j];
//       }
//       else{
//         sum-=result[i][j];
//       }
//     }
//     sums.push_back(sum);
//   }
//   int d_min = INT_MAX;
//   int index = -1;
//   for(int i=0;i<sums.size();i++){
//     if(sums[i]>height){
//       continue;
//     }
//     else if(sums[i]==height){
//       index = i;
//       break;
//     }
//     else{
//       int d = height-sums[i];
//       if(d<d_min){
//         index = i;
//         d_min=d;
//       }
//     }
//   }
//   for(int i=0;i<result[index].size();i++){
//     if(i>0){
//       std::cout << " "; 
//     }
//     std::cout << result[index][i];
//   }
//   std::cout << std::endl;
//   return 0;
// }

// #include<iostream>
// #include<vector>
// #include<string>
// #include <utility> 
// #include <sstream>
// #include<algorithm>
// #include<list>
// #include<queue>
// #include<map>
// #include<set>
// using namespace std;

// //REVIEW 先排序简化 组合回溯的时间复杂度是C n n/2+1 只需要去上升的所以是2^11 如果理解成排列会变成23!  

// bool cmp(int x, int y) {
//     return x > y;
// }
// // 整体序列和
// int totalSum;
// vector<int> res;
// int minDiff;
// int m,n;

// // 递归回溯枚举 选取exceptCount的数
// void DFS(vector<int>& ans, int index , int currentSum, int count, int exceptCount, int& visited) {
//     if (count > exceptCount) {
//         return;
//     }
//     if (exceptCount == count) {
//         // 净增楼层
//         int diff = currentSum - (totalSum - currentSum);
//        // 上升超过m的不考虑
//        if (diff > m) {
//           return;
//        }
       
//        // 找最小差距
//        diff = abs(diff - m);
//        if (diff < minDiff) {
//            res.clear();
//            minDiff = diff;
//            res.push_back(visited);   
//        } else if (diff == minDiff) {
//           res.push_back(visited);
//        }
//        return;
//     }

//     for (int i = index; i < n; i++) {
//         int num = ans[i];
//         int nextCurrentSum = currentSum + num;
//         // 剪枝 最终会超过m层
//         if (nextCurrentSum - (totalSum - nextCurrentSum) > m) {
//             continue;
//         }
//         // 递归回溯
//         visited |= 1 << (n - i -1);
//         DFS(ans, i + 1, nextCurrentSum, count + 1, exceptCount, visited);
//         visited &= ~(1 << (n - i - 1));
//     }
// }

// // 交叉构建结果集
// vector<int> buildArr(vector<int>& ans, int num) {
//     vector<bool> visted(n, false);
//     for (int i = 0; i < n; i++) {
//         visted[i] = 1 & (num >> (n-1-i));
//     }
//     vector<int> s(n);
//     int pos = 0;
//     for (int i = 0; i < n; i++) {
//         if (visted[i]) {
//             s[pos] = ans[i];
//             pos += 2; 
//         }       
//     }
//     pos = 1;
//     for (int i = 0; i < n; i++) {
//         if (!visted[i]) {
//             s[pos] = ans[i];
//             pos += 2; 
//         }       
//     }
//     return s;
// }

// // 在所有mask生成的数组中，找出字典序最大的
// vector<int> findBestArray(vector<int>& ans) {
//     vector<int> best;

//     for (const int& mask : res) {
//         vector<int> curr = buildArr(ans, mask);
//         if (best.empty() || curr > best) {
//             best = curr;
//         }
//     }
//     return best;
// }

// int main() {
//     cin >> m >> n;
//     vector<int> ans(n);
//     int sum = 0;
//     for (int i = 0; i < n; i++) {
//         cin >> ans[i];
//         sum += ans[i];
//     }
//     // 
//     totalSum = sum;
//     minDiff = sum + m;
//     // 从大到小排序
//     sort(ans.begin(), ans.end(), cmp);
//     // 向上取整 向上的数量
//     int exceptUpCount = (n + 1) / 2;

//     int status = 0;
//     DFS(ans, 0, 0, 0, exceptUpCount, status);

//     vector<int>anwser =  findBestArray(ans);
//     for (int i = 0; i < n; i++) {
//         cout << anwser[i];
//         if (i != n-1) {
//             cout << " ";
//         }
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
using namespace std;

bool cmp(int x, int y) {
    return x > y;
}

int totalSum;
vector<vector<bool>> result; //REVIEW 结果以是否被选中来表示 否则只取出了上升阶梯而不知道哪些需要下降
int minDiff;
int m, n;

// 递归回溯枚举选取exceptCount个数
void DFS(vector<int>& ans, int index, int currentSum, int selectedCount, int targetCount, vector<bool>& path) {
    if (selectedCount > targetCount) {
        return;
    }
    if (targetCount == selectedCount) {
        // 计算上升的净增量
        int diff = currentSum - (totalSum - currentSum);
        // 上升超过m的不考虑
        if (diff > m) {
            return;
        }
        
        // 计算与目标m的差距
        diff = abs(diff - m);//REVIEW 只保存最优路径
        if (diff < minDiff) {
            result.clear();
            minDiff = diff;
            result.push_back(path);
        } else if (diff == minDiff) {
            result.push_back(path);
        }
        return;
    }

    for (int i = index; i < n; i++) {
        int nextCurrentSum = currentSum + ans[i];
        // 剪枝：最终上升量超过m
        if (nextCurrentSum - (totalSum - nextCurrentSum) > m) {
            continue;
        }
        
        // 选择当前数字
        path[i] = true;
        DFS(ans, i + 1, nextCurrentSum, selectedCount + 1, targetCount, path);
        path[i] = false; // 回溯
    }
}

// 根据选择模式构建交叉数组
vector<int> buildArr(vector<int>& ans, vector<bool>& pattern) {
    vector<int> result(n);
    
    // 被选中的数字放在偶数位置(0,2,4...)
    int evenPos = 0;
    for (int i = 0; i < n; i++) {
        if (pattern[i]) {
            result[evenPos] = ans[i];
            evenPos += 2;
        }
    }
    
    // 未被选中的数字放在奇数位置(1,3,5...)
    int oddPos = 1;
    for (int i = 0; i < n; i++) {
        if (!pattern[i]) {
            result[oddPos] = ans[i];
            oddPos += 2;
        }
    }
    
    return result;
}

// 在所有模式生成的数组中，找出字典序最大的
vector<int> findBestArray(vector<int>& ans) {
    vector<int> bestArray;
    
    for (auto& pattern : result) {
        vector<int> currentArray = buildArr(ans, pattern);
        if (bestArray.empty() || currentArray > bestArray) {
            bestArray = currentArray;
        }
    }
    
    return bestArray;
}

int main() {
    cin >> m >> n;
    vector<int> ans(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> ans[i];
        sum += ans[i];
    }
    
    totalSum = sum;
    minDiff = sum + m; // 初始化为一个大数
    
    // 从大到小排序
    sort(ans.begin(), ans.end(), cmp);
    
    // 需要选中的数字个数（放在偶数位置）
    int targetCount = (n + 1) / 2;
    
    // 初始化选择状态数组
    vector<bool> path(n, false);
    
    // 深度优先搜索所有可能的组合
    DFS(ans, 0, 0, 0, targetCount, path);
    
    // 找到最佳排列
    vector<int> answer = findBestArray(ans);
    
    // 输出结果
    for (int i = 0; i < n; i++) {
        cout << answer[i];
        if (i != n-1) {
            cout << " ";
        }
    }
    
    return 0;
}

