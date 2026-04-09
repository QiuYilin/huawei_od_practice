#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
using namespace std;

int main() {
    //REVIEW CPU 每秒执行10^7~10^8  2^15*3*15使用枚举不会太耗时
    //REVIEW 对所有情况验证所有边
    int n,m;
    // 节点 边
    cin >> m >> n;
    vector<pair<int, int>> edges(n);
    for (int i = 0; i < n; i++) {
        int x , y;
        cin >> x >> y;
        edges[i] = {x, y};
    }
    // 没有边所以说明每个节点都能取红或黑
    if (n == 0) {
        cout << pow(2, m);
        return 0;
    }
    
    int res = 0;
    //REVIEW 二元值可以用二进制来代表染色情况
    //遍历所有情况
    for (int i = 0; i < (int)pow(2,m); i++) {
        // 判断是否合法
        bool flag = true;
        for (int j = 0; j < n; j++) {//遍历所有边
            int x = edges[j].first;
            int y = edges[j].second;
            // 是否相邻边同为红 
            if ((i >> (x-1) & 1) == 1 && (i >> (y-1) & 1) == 1) {
                flag = false;
                break;   
            }
        }
        if (flag) {
            res++;
        }
    }
    
    cout << res;
    return 0;
}
