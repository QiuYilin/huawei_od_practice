// #include <iostream>

// #include <vector>
// //审题 像是某个贪心题的二维变种
// int main(){
//   //有m列 等价与m种情况 转换为一维 然后的规律是累加不可是负数 我的办法复杂度太高
//   int n=0,m=0;
//   std::cin >> n >> m;
//   std::vector<std::vector<int>> matrix(n,std::vector<int>(m,0)); 
  
//   for(int i=0;i<n;i++){
//     for(int j=0;j<m;j++){
//       int cur = 0;
//       std::cin >> cur;
//       if(i>=1){
//         matrix[i][j]=matrix[i-1][j]+cur;
//       }
//       else{
//         matrix[i][j]=cur;
//       }
//     }
//   }
//   //疑问所有数组都是负数怎么办 答案是最大的那个负数

//   //疑问 Cn-1+Cn-2+...+Cn-n答案是什么 n+n(n-1)/2 需要用组合去考虑吗 
//   for(int i=0;i<n;i++){

//   }
//   return 0;
// }

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<climits>
using namespace std;


// kadane算法,本质就是贪心
int kadane(const vector<int>& arr) {
    int maxHere = arr[0], maxSoFar = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        maxHere = max(arr[i], maxHere + arr[i]);
        maxSoFar = max(maxSoFar, maxHere);
    }
    return maxSoFar;
}


int solve(vector<vector<int>>& grid, int n, int m) {//REVIEW 枚举方式的写法 外层是上边界 内层是下边界 如果想到组合回溯 那么强枚举等价
    int res = INT_MIN;
    // 枚举上边界
    for (int top = 0; top < n; top++) {//n次
        vector<int> colSum(m, 0);
        // 枚举下边界
        for (int bottom = top; bottom < n; bottom++) {//n-top次
            // 压缩为一维
            for (int c = 0; c < m; c++) {
                colSum[c] += grid[bottom][c];
            }
            res = max(res, kadane(colSum));
        }
    } 
    return res;
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int res = solve(grid, n, m);
    cout << res;
}
