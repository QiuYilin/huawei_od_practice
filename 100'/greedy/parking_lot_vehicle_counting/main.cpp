//没考虑同辆车多次进出
#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<map>
#include<set>
using namespace std;


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


// 将时间转换为int 统一以分钟表示
int parseTime(string& time) {
    vector<int> tmp  = split(time, ":");
    int res = 0;
    res = tmp[1] + tmp[0] * 60;
    return res;
}

// 计算每辆车的花费
int cost(int begin, int end) {
   if (end - begin < 30) {
       return 0;
    }
    string freeTimeBeginStr = "11:30";
    string freeTimeEndStr = "13:30";
    int freeTimeBegin =  parseTime(freeTimeBeginStr);
    int freeTimeEnd = parseTime(freeTimeEndStr);
    
    // 8个小时是考友回忆的，实际可能不是8个小时，考的时候根据题目描述来更改
    int maxTime = 8 * 60;
    // 到达停车收费最长时间停止收费
    end = min(end, begin + maxTime);

    // 收费时间
    int chargeTime = end - begin;
    
    // 忽略免费时间段 和免费时间有交集 
    if (begin <= freeTimeEnd && end >= freeTimeBegin ) {
        // 跨免费时间的时长
        chargeTime -= min(freeTimeEnd, end) - max(freeTimeBegin, begin);
    }
    return (chargeTime + 29) / 30; 
}


int main() {
    int n;
    cin >> n;
    string time, card, direct;
    set<string> monthlyPaymentCard;
    for (int i = 0; i <  n; i++) {
        string card;
        cin >> card;
        monthlyPaymentCard.insert(card);
    }

    // 记录非包月车的进出时间
    map<string, pair<int, int>> mp;//REVIEW 用map<string, pair<int, int>>记录
    while (cin >> time >> card >> direct) {//REVIEW 不使用geline也行
        if (time == "") {
            break;
        }
        // 忽略包月车
        if (monthlyPaymentCard.count(card)) {
            continue;
        }
        int timeMimute = parseTime(time);
        if (direct == "enter") {
            mp[card].first = timeMimute;
        } else {
            mp[card].second = timeMimute;
        }
    }


    int res = 0;
    for (auto p : mp) {
        int start = p.second.first;
        int end = p.second.second;
        // 计算每辆车的花费
        res += cost(start, end);
    }

    cout << res;
}
