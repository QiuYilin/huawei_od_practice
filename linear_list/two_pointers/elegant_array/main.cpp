#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;

//审题 
//REVIEW 回溯所有子序列再判断 分割是列举了所有切割方案 子数组会大量重复
//滑动窗
//疑问 双指针如何覆盖所有情况？
//疑问 有效判断的方式

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    // 绝对不满足
    if (k <= 0) {
        cout << 0;
        return 0;
    }
    // 统计窗口类各个数字的数量
    map<int, int> numCountMp;
    int left = 0;
    long ans = 0;
    // 当前窗口中恰好达到k次不同元素的数量
    int valid = 0;

    for (int  right = 0; right < n; right++) {
        int x = nums[right];
        numCountMp[x] += 1;

        if (numCountMp[x] == k) {
            valid++;
        }
        //  只要窗口有效，就把以当前 right 结尾的所有满足子数组计入，然后收缩左边
        while (valid > 0) {
            ans += n - right;

            // 收缩左端
            int y = nums[left];
            numCountMp[y]--;
            if (numCountMp[y] == k - 1) {
                valid--;
            }
            left++;
        }
    }

    cout << ans << endl;
}
