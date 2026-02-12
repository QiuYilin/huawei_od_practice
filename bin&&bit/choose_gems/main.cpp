 #include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
using namespace std;

//REVIEW x颗宝石的属性值之积>=y
//Cn x n! 2^n
//计算量<2^23就能用二进制枚举取代回溯
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> ans(n);
    for (int i = 0; i < n ;i++) {
        cin >> ans[i];
    }

    int res = 0;
    // 数据量比较小直接采用二进制枚举方式
    for (int i = 1; i < pow(2, n); i++) {
        // 这个方案选择的运动的位置
       vector<int> pos =  countOnesAndPositions(i);
       if (pos.size() != x) {
            continue;
        }
       long long  sum = 1L;
       for (int j = 0; j < x; j++) {
          sum *= ans[pos[j]];
       }
       if (sum >= y){
         res++;
       }
    }
    cout << res;
    return 0;
}


