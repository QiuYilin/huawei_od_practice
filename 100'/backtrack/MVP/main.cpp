#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
using namespace std;

bool cmp(int x , int y) {
    return x > y;
}

bool backtrack(int index, vector<int> & buckets, int subSum, vector<int> ans) {
    if (index == ans.size()) {
        for (int i = 0; i < buckets.size(); i++) {
            if (buckets[i] != subSum) {
                return false;
            }
        }
        return true;
    }

    for (int i = 0; i < buckets.size(); i++) {
         // 剪枝 防止重复运算
        if (i > 0 && buckets[i] == buckets[i - 1]) {
            continue;
        }
       
        if (buckets[i] + ans[index] > subSum) {
            continue;
        }
        // 递归
        buckets[i] += ans[index];
        if (backtrack(index + 1, buckets, subSum, ans)) {
            return true;
        }
        // 回溯
        buckets[i] -= ans[index];
        
    }
    return false;
}

bool canPartition(vector<int> ans, int n, int sum) {
    //不能整除说明当前假设mvp人数下，肯定不成立
    if (sum % n) {
        return false;
    }
    // 为每个人得到的分数
    int subSum = sum / n;
    
    int size = ans.size();
    // 分数不能进行分割，所以肯定不成立
    if (ans[0] > subSum) {
        return false;
    }
  
    int beginIndex = 0;
    // 预处理数据，减少数据量，提高算法执行效率
    while (beginIndex < size && ans[beginIndex] == subSum) {
        n--;
        beginIndex++;
    }

    if (n == 0) {
        return true;
    }         

    vector<int> buckets(n, 0);
    return backtrack(beginIndex,buckets, subSum, ans);
}





int main() {
    int n ;
    cin >> n;
    vector<int> ans(n);
    // 所有得分
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> ans[i];
        sum += ans[i];
    }
    // 将分数进行逆序排序
    sort(ans.begin(), ans.end(), cmp);
    // 从大到小枚举获取MVP的人数， 大小范围为 1 - m
    while (n != 1) {
        if (canPartition(ans, n, sum)) {
            break;
        }
        n--;
    }
    cout << sum / n;
    return 0;
}
