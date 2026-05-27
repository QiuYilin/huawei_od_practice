#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;
// 并查集 父下标 分组长度  开始高度
vector<int> parent, sz, start;
// 指定位置是否已被激活
vector<bool> active;
//指定长度可选次数
vector<long long> lenCount;


// 通用 切割函数 函数 将字符串str根据delimiter进行切割
vector<int> split(const string& str, const string& delimiter) {
    vector<int> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(stoi(str.substr(start, end - start)));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // 添加最后一个部分
    result.push_back(stoi(str.substr(start)));
    return result;
}

//并查集寻根
int find(int x) {
    // int root = x;
    // while (parent[root] != root) root = parent[root];
    // while (parent[x] != root) {
    //     int p = parent[x];
    //     parent[x] = root;
    //     x = p;
    // }
    // return root;
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

// 结算从区间的诞生时间到当前时间 之间产生的贡献次数
void settleSegement(int root, int t) {
    long long count = (long long) start[root] - t;
    if (count > 0) {
        lenCount[sz[root]] += count;
    }
}

// 合并区间
int merge(int a, int b, int t) {
    int ra = find(a), rb = find(b);
    if (ra == rb) {
        return ra;
    }
    // 区间需要统一水平线至当前时间，
    settleSegement(ra, t);
    settleSegement(rb, t);
    if (sz[ra] < sz[rb]) {
        swap(ra, rb);
    }
    parent[rb] = ra;
    sz[ra] += sz[rb];
    start[ra] = t;
    return ra;    
}


long long getMinProcessTime(vector<int> times, int k) {
    
    int n = times.size();
    long long total = 0;
    int maxTime = 0;
    // 统计总用时 + 获取最大用时
    for (auto& x : times) {
        total += x;
        maxTime = max(maxTime, x);
    }
    
    if (total == 0 || k >= total) {
        return 0;
    }
    if (k == 0) {
        return total;
    }
    
    // 按时间大小分组
    vector<vector<int>> timeGroup(maxTime + 1);
    for (int i = 0; i < n; i++) {
        if (times[i] > 0) {
            timeGroup[times[i]].push_back(i);
        }
    }
    //father数组可以配合其他一些数组记录额外的信息
    parent.resize(n);//并查集
    sz.assign(n, 1);//以该位置为根的连续段的长度
    start.assign(n, 0);//该连续段的诞生高度
    active.assign(n, false);//标记某位置是否被激活
    lenCount.assign(n + 1, 0);//指定长度分组可选次数
    
    for (int t = maxTime; t >= 1; t--) {//从最高点开始遍历
        for (int pos : timeGroup[t]) {
            active[pos] = true;
            parent[pos] = pos;
            sz[pos] = 1;
            start[pos] = t;//初始化
            int root = pos;
            if (pos > 0 && active[pos -1]) {
                root = merge(pos, pos -1, t);
            }
            if (pos + 1 < n && active[pos + 1]) {
                root = merge(pos, pos + 1, t);
            }            
        }
    }

    for (int i = 0; i < n; i++) {
        if (active[i] && find(i) == i) {
            settleSegement(i, 0);
        }
    }
    // 贪心选取最大可减少时间
    long long sum  = 0;
    // 剩余选取次数
    long long left = k;
    for (int len = n; len >= 1 && left > 0; len--) {
        long long takeCount = min(left, lenCount[len]);
        sum += takeCount * len;
        left -= takeCount;
    }
    return total - sum;
}

int main() {
    string input;
    getline(cin, input);
    int k;
    cin >> k;
    vector<int> times = split(input, ",");
    long long res = getMinProcessTime(times, k);
    cout << res;
    return 0;
}
