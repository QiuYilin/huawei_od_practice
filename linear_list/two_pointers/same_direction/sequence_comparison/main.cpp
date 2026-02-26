#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> aScores(n),bScores(n);
    for (int i = 0; i < n; i++) {
        cin >> aScores[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> bScores[i];
    }
    sort(aScores.begin(), aScores.end());
    sort(bScores.begin(), bScores.end());

    int leftA = 0, rightA = n - 1;
    int leftB = 0, rightB = n - 1;
    int res = 0;

    while (leftB <= rightB) {
        // 最大值相比，a > b 则直接比
        if (aScores[rightA] > bScores[rightB]) {
            rightA--;
            rightB--;
            res += 1;
        // 最大值相比， a < b，无论如何都要输，选择损失最小数
        } else if (aScores[rightA] < bScores[rightB]) {
            rightB--;
            leftA++;
            res -=1;
        } else {
            // 相等情况下 ，a最小值大于b最小值，先考虑左指针移动
            if (aScores[leftA] > bScores[leftB]) {
                res+=1;
                leftA++;
                leftB++;
            // 相等情况下，a的最小值小于b的最小值。 使用a的最小值和b的最大值对抗
            }else {
                // a [1 1 1] b[1 1 1] 考虑这个情况  
                if (bScores[rightB] > aScores[leftA]) {
                    res -=1;
                }
                leftA++;
                rightB--;
            }
        }
    }

    cout << res;
    return 0;
}


