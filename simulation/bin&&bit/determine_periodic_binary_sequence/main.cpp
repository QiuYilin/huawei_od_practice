#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;

int getEqualBinDistance(int n) {
    // 二进制1的数量
    int count = 0;
    // 二进制位
    int index = 0;//当前索引
    int distance = -1;//等距二进制数1的距离
    // 上一个1的位置
    int last = -1;
    while (n > 0) {
        // 最末尾二进制值
        int value = n & 1;
        if (value == 1) {
            count++;
            if (last != -1) {
                if (distance == -1) {
                    distance = index - last - 1;
                } else {
                    // 不是等距
                    if (index - last-1 != distance) {
                        return -1;
                    }
                }
            }
            last = index;
        }
        index++;
        n >>= 1;
    }
    // 1数量小于3
    if (count < 3) {
        return  -1;
    }
    return distance;
}


int main() {
    int n;
    cin >> n;
    int res = getEqualBinDistance(n);
    cout << res;
}
