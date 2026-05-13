#include <bits/stdc++.h>
using namespace std;

long long x, y, cntx, cnty;

// 1-num中是否满足条件
bool check(long long num) {
    // 1-num中x的倍数的数量
    long long xCount = num / x;
    // 1-num中y的倍数的数量
    long long yCount = num / y;
    // 1-num中x * y的倍数的数量
    long long xyCount = num / (x * y);

    return max(0LL, cntx - (yCount - xyCount)) 
         + max(0LL, cnty - (xCount - xyCount)) 
         <= num - (xCount + yCount - xyCount);
}

int main() {
    cin >> x >> y >> cntx >> cnty;

    long long low = cntx + cnty;
    long long high = 1000000000LL;

    // 二分
    while (low <= high) {
        long long mid = (low + high) / 2;
        if (check(mid)) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << low;
    return 0;
}

