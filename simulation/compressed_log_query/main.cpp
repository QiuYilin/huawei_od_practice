#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;

// 通用 切割函数 函数 将字符串str根据delimiter进行切割
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

// 判断闰年
bool isLeap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

// 每月天数
int daysInMonth(int y, int m) {
    static int d[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && isLeap(y)) return 29;
    return d[m];
}

// 加一分钟
string addOneMinute(const string &t) {
    int y = stoi(t.substr(0,4));
    int mo = stoi(t.substr(4,2));
    int d = stoi(t.substr(6,2));
    int h = stoi(t.substr(8,2));
    int mi = stoi(t.substr(10,2));
    
    mi++;
    if (mi == 60) {
        mi = 0;
        h++;
        if (h == 24) {
            h = 0;
            d++;
            if (d > daysInMonth(y, mo)) {
                d = 1;
                mo++;
                if (mo > 12) {
                    mo = 1;
                    y++;
                }
            }
        }
    }

    char buf[20];
    sprintf(buf, "%04d%02d%02d%02d%02d", y, mo, d, h, mi);//REVIEW 用printf格式化字符串
    return string(buf);
}


int main() {
    // 处理输入
    string startEnd;
    int n;
    cin >> startEnd;
    vector<string> tmp = split(startEnd, ",");
    string start = tmp[0], end = tmp[1];
    cin >> n;
    vector<vector<string>> records(n);//REVIEW 根据题意，记录是起始时间
    for (int i = 0; i < n; i++) {
        string input;
        cin >> input;
        records[i] = split(input, ",");
    }
    // 存储结果
    vector<vector<string>> ans;
    
    // 查询有交集区间
    for (int i = 0; i < n; i++) {
        string currentStart = records[i][0];//REVIEW 这里字符串能直接比较
        string currentEnd = records[i][1];
        string currentKpi = records[i][2];
        // 升序,后面不会存在交集
        if (currentStart > end) {
            break;
        }
        if (currentStart <= end && currentEnd >= start) {//REVIEW 交集公式
            ans.push_back({max(currentStart, start), min(currentEnd, end), currentKpi});
        }
    }
    // 查询不到记录
    if (ans.empty()) {
        cout << -1;
        return 0;
    }

    // 重叠区间 输出结果
    bool first = true;
    for (auto &r : ans) {
        string cur = r[0];
        string e = r[1];
        string k = r[2];
        while (cur <= e) {
            if (!first) cout << endl;
            cout << cur << "," << k;
            first = false;
            cur = addOneMinute(cur);//REVIEW 展开时间
        }
    }

    return 0;
}
