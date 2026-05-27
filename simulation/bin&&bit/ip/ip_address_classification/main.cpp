#include <cctype>
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

// 判断是否只包含数字字符
bool judge(string& str) {
    for (auto&c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}


// 解析ip返回对应long值，不合法返回-1
long parseIp(string ip) {
    vector<string> ipPart = split(ip, ".");
    if (ipPart.size() != 4) {
        return -1;
    }
    long res = 0;
    for (int i = 0; i < 4; i++) {
        string cur = ipPart[i];
        if (cur.empty() || cur.size() > 3 || !judge(cur)) {
            return -1;
        }
        long value = stol(cur);
        // 超过限制
        if (value > 255) {
            return -1;
        }
        res = (res << 8) + value;
    }
    return res;
}

string ipClassify(string& ip) {//REVIEW 先计算更好
    // 映射出每个分类起始和结束范围
    map<string, pair<long, long>> mp;
    mp["R"] = {parseIp("0.0.0.0"), parseIp("0.255.255.255")};
    mp["A"] = {parseIp("1.0.0.0"), parseIp("126.255.255.255")};
    mp["L"] = {parseIp("127.0.0.0"), parseIp("127.255.255.255")};
    mp["B"] = {parseIp("128.0.0.0"), parseIp("191.255.255.255")};
    mp["C"] = {parseIp("192.0.0.0"), parseIp("223.255.255.255")};
    mp["D"] = {parseIp("224.0.0.0"), parseIp("239.255.255.255")};
    mp["E"] = {parseIp("240.0.0.0"), parseIp("255.255.255.255")};

    long ipValue = parseIp(ip);
    if (ipValue == -1) {
        return "F";
    }
    // 判断所属类型
    for (auto& [key, range] : mp) {
        if (range.first <= ipValue && range.second >= ipValue) {
            return key;
        }
    }
    return "F";
}

int main() {
    string ip;
    getline(cin, ip);
    string res = ipClassify(ip);
    cout << res;
    return 0;
}


