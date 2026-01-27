// #include <iostream>
// //怎么用更高效的方法表示 256进制？
// //REVIEW 什么是离线算法？

// int main(){
//     return 0;
// }

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<queue>
using namespace std;

//整体排序技巧 离线双排序

struct IPRange{
    long start;
    long end;
    string city;
    IPRange(long start, long end, string city): start(start), end(end), city(city){}
};


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


//REVIEW 将ip 转换为 long
long parseIP(string &ip) {
    vector<string> ipBlock = split(ip, ".");
    long res  = 0;
    for (int i = 0; i < 4; i++) {
        res = (res << 8) | stol(ipBlock[i]);
    }
    return res;
}

// 自定义排序
bool cmp(IPRange i1, IPRange i2) {
    return i1.start < i2.start;
}



int main() {
    string cityIP;
    getline(cin, cityIP);
    string searchIPInput;
    getline(cin, searchIPInput);
    vector<string> cityList = split(cityIP, ";");
    int n = cityList.size();

    vector<IPRange> cityIPItems;
    // 解析输入
    for (int i = 0; i < n; i++) {
        string cityIPItem = cityList[i];
        vector<string> cityAndIp = split(cityIPItem, "=");
        string cityName = cityAndIp[0];
        vector<string> ipStartAndEnd = split(cityAndIp[1], ",");
        long start = parseIP(ipStartAndEnd[0]);
        long end = parseIP(ipStartAndEnd[1]);
        cityIPItems.push_back({start, end, cityName});
    }
    //REVIEW 依据起始IP段 给城市排序 为什么不要求稳定 也不要求段大小
    sort(cityIPItems.begin(), cityIPItems.end(), cmp);
    
    vector<string> searchIp = split(searchIPInput, ",");
    int m = searchIp.size();
    vector<long> searchLongValue(m);
    for (int i = 0; i < m; i++) {
        searchLongValue[i] = parseIP(searchIp[i]);
    }
    //REVIEW 离线算法 - 既要依据查询顺序又要借助排序优化
    vector<int> qindex(m, 0);
    for (int i = 0; i < m; i++) {
        qindex[i] = i;
    }
    // REVIEW qindex 将待查询IP根据查询ip进行排序
    sort(qindex.begin(), qindex.end(), [&](int i, int j) -> bool {
        return searchLongValue[i] < searchLongValue[j];
    });

    priority_queue<vector<long>> pq;//REVIEW 优先级队列至少需要容器的模板参数

    vector<string> res(searchLongValue.size(), "");
    int i = 0;
    //REVIEW 
    for (auto qi : qindex) {
        while (i < n && cityIPItems[i].start <= searchLongValue[qi]) {
            long l = cityIPItems[i].end - cityIPItems[i].start +1;
            pq.push({-l, -cityIPItems[i].start, cityIPItems[i].end, i});//REVIEW 隐藏比较 段长 起始IP vector可以直接比较
            i++;
        }
        while (!pq.empty() && pq.top()[2] < searchLongValue[qi]) {
            pq.pop();
        }
        if (!pq.empty()) {
            res[qi] = cityIPItems[pq.top()[3]].city;
        }
    }

    for (int i = 0; i < m; i++) {
        cout << res[i];
        if (i != m - 1) {
            cout << ",";
        }
    }
    return 0;
}

