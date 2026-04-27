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

//REVIEW 审题数位和

//REVIEW数位和数组，预处理减少重复运算
vector<int> digitSum;

// 预计算数位和函数
void calcDigitSum() {
    for (int i = 0; i < digitSum.size(); i++) {
        int num = i;
        int tmp = 0;
        while (num > 0) {
            tmp += num % 10;
            num /= 10;
        }
        digitSum[i] = tmp;
    }
}



int main() {
    int m,n,k;
    cin >> m >> n >> k;
    digitSum.resize(max(n, m));
    // 四个方向
    int direct[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    if (m == 0 || n ==0) {
        cout << 0;
        return 0;
    }

    calcDigitSum();
    // 访问标志， 防止重复
    set<int> visited;
    int res  = 1;
    queue<int> q;
    q.push(0);
    visited.insert(0);
    while (!q.empty()) {
        int num = q.front();
        q.pop();
        int x = num / n;
        int y = num % n;
        for (int i = 0; i < 4; i++) {
            int newX = x + direct[i][0];
            int newY = y + direct[i][1];
            int newNum = newX * n + newY;
            // 越界 和 已经访问过
            if (newX < 0 || newX >= m || newY < 0 || newY >= n || visited.count(newNum)) {
                continue;
            }
            // 数位和超过k
            if (digitSum[newX] + digitSum[newY] > k) {
                continue;
            }
            res++;
            q.push(newNum);
            visited.insert(newNum);
        }
    }

    cout << res;
    return 0;
}
