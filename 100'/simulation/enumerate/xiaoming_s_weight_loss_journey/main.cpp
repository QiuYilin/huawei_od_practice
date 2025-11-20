#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
using namespace std;

// 快速求出对应数字1个位置
vector<int> countOnesAndPositions(int n) {
    vector<int> positions;
    int index = 0;
    while (n) {
        if (n & 1) positions.push_back(index);
        n >>= 1;
        index++;
    }
    return  positions;
}

int main() {
    int n, t, k;
    cin >> n >> t >> k;
    vector<int> ans(n);
    for (int i = 0; i < n ;i++) {
        cin >> ans[i];
    }
    int res = 0;
    //REVIEW 10*2^10 < 2^23 可以枚举
    for (int i = 1; i < pow(2, n); i++) {
        // 这个方案选择的运动的位置
       vector<int> pos =  countOnesAndPositions(i);
       if (pos.size() != k) {
            continue;
       }
       int sum = 0;
       for (int j = 0; j < k; j++) {
          sum += ans[pos[j]];
       }
       if (sum == t){
         res++;
       }
    }
    cout << res;
    return 0;
}

