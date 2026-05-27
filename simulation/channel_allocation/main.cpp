#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
using namespace std;


// 获取数的反转二进制表现形式
vector<int> getReversedBinaryArray(int D) {
    vector<int> bits;
    // 提取 D 的二进制位（低位到高位）
    while (D > 0) {
        bits.push_back(D % 2);
        D /= 2;
    }
    return bits;  
}

// 二进制位加法
int calculate(vector<int> num, int n) {
    int res = 0;
    for (int i = 0; i <= n; i++) {
        res += num[i] * (1 << i);
    }
    return res;
}

bool binSub(vector<int>& nums, vector<int>& subNum) {
    // 从高位开始进行减 
    for (int i = subNum.size() - 1; i >= 0; i--) {
        // 对应阶信道足够直接减去
        if (nums[i] >= subNum[i]) {
            nums[i] -= subNum[i];
            continue;
        }
        // 接下来是处理不够的情况下 优先选择从低阶补
        if (calculate(nums, i)  >= calculate(subNum, i)) {
            nums[i] -= subNum[i];
            // 向下一位借，进行转移 需要*2
            nums[i-1] += nums[i]<<1;
            // 转移后变为0
            nums[i] = 0;
        // 只能从高位借    
        } else {
            int j = i + 1;
            bool flag = false;
            while (j < subNum.size()) {
                // 有高位可借 足够覆盖所有需求的 二进制的前n最大和 位2^n-1, 
                if (nums[j] > 0) {
                    nums[j] -= 1;
                    flag =  true;
                    break;
                }
                j++;
            }
            // 说明借到高位了
            if (flag) {
                // i+1 - j-1之间之前减的值按理应该还回去 不过不还也没问题 
                // for (int k = i+1; k < j; j++) {
                //     nums[k] += subNum[k];
                // }
                return true;
            }
            // 无法满足分配了
            return false;
        }
    }
    return true;
}


int main() {
    int R;
    cin >> R;
    vector<int> nums(R+1, 0);
    for (int i = 0; i <= R; i++) {
        cin >> nums[i];
    }
    int D;
    cin >> D;
    
    int res = 0;
    vector<int> binFormat = getReversedBinaryArray(D);

    // 单独一个信道就能满足传输的情况 处理玩这个之后不必考虑 大于等于 binFormat.size() 阶的信道了
    for (int i = R; i >= binFormat.size(); i--) {
        res += nums[i];
    }
    // 保证nums尺寸不小于binformat
    if (nums.size() < binFormat.size()) {
        int diff = binFormat.size() - nums.size();
        for (int i = 0; i < diff; i++) {
            nums.push_back(0);
        }
    }
    // 使用类似于二进制减法的操作模拟求值
    while (binSub(nums, binFormat)) {
        res++;
    }
    cout << res;
    return 0;
}	
