//REVIEW 题目的意思是当前第N个元素的前M个元素

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
#include<set>
#include<climits>
using namespace std;


int positionValue(int m , int n) {
    // 小于情况就是n
    if (n <= m) {
        return n;
    }
    vector<int> num(n + 1);//REVIEW 整体保存就不用维护单独的m个元素了
    // 初始化
    for (int i = 1; i <= m; i++) {
        num[i] = i;
    }
    // 数据量小->递推
    for (int i = m + 1; i <= n; i++) {
        int mx = INT_MIN, mn = INT_MAX;
        set<int> s;
        bool dupFlag = false;
        for (int j = i - m; j < i; j++) {//REVIEW 没有单独做成函数而已
            if (s.count(num[j])) {
                dupFlag = true;
            }
            s.insert(num[j]);

            mx = max(mx, num[j]);
            mn = min(mn, num[j]);
        }
        if (dupFlag) {
            num[i] = mx + mn;
        } else {
            num[i] = mx - mn;
        }
    }
    return num[n];
}

int main() {
    int m, n;
    scanf("%d,%d", &m, &n);
    int res = positionValue(m, n);
    cout << res;
    return 0;
}

