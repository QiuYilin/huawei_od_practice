#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<list>
#include<queue>
#include<set>
using namespace std;


// 通用 split 函数
vector<string> split(const string& str, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // 添加最后一个部分
    result.push_back(str.substr(start));
    return result;
}

int main() {
    string s;
    // 处理输入
    getline(cin ,s);
    vector<string> ansStr = split(s, " ");
    int n = ansStr.size();
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        ans[i] = stoi(ansStr[i]);
    }
    
    //REVIEW 类似dp的前缀后缀处理
    // 记录第i个山峰左边(不包括i)最高峰
    vector<int> left(n, 0);
    for (int i = 1; i < n; i++) {
        left[i] = max(left[i-1], ans[i-1]);
    }
    // 记录第i个山峰右边(不包括i)最高峰
    vector<int> right(n, 0);
    for (int i = n-2; i >= 0; i--) {
        right[i] = max(right[i+1], ans[i+1]);
    }
    
    vector<int> waterLine(n, 0);
    //REVIEW 计算每个位置的水位线高度
    //水位线高度 = 山峰高度 + 能存储的水的高度
    //REVIEW 贪心规律 左边第一个水位线高但是山比水位线低 右边同理 中间都能保持同个水位线
    set<int> waterLineSet;
    for (int i = 1; i < n - 1; i++) {
        // 当前位置可以存储的水
        int water = max(0,  min(left[i], right[i]) - ans[i]);
        if (water != 0) {
            waterLine[i] = water + ans[i];
            waterLineSet.insert(waterLine[i]);
        }
    }
    
    // 左边界 右边界 存储量
    vector<int> res = {0, 0, 0};
    // 枚举所有水位线，分别找到左边，右边第一个水位线大于等于位置。找到两个边界
    for (int line : waterLineSet) {
        int l = 0;
        // 找到左侧第一个水位线大于等于line且山高度小于line的
        while (waterLine[l] < line || ans[l] >= line) {
            l++;
        }
        
        int r = n - 1;
       // 找到右边第一个水位线大于等于line且山高度小于line的
        while (waterLine[r] < line || ans[r] >= line) {
            r--;
        }

        int sum = 0;
        // 存储的水数量求和
        for (int i = l; i <= r; i++) {
            sum += max(0, line - ans[i]);
        }

        if (sum > res[2]) {
            res[0] = l - 1;
            res[1] = r + 1;
            res[2] = sum;
        } else if (sum == res[2]) {
            int currLen = r - l + 1;
            int lastLen = res[1] - res[0] + 1;
            if (currLen < lastLen) {
                res[0] = l - 1;
                res[1] = r + 1;
            }
        }
    }
     
    if (res[2] == 0) {
        cout << "0";
    } else {
        cout << res[0] << " " << res[1] << ":" << res[2];
    }

    return 0;
}
