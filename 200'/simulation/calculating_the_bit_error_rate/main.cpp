#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<list>
#include<queue>
#include<map>
#include<set>
using namespace std;

// 解析字符串
list<pair<char, int>> splitStr(string s) {
    list<pair<char, int>> res;
    string num = "";
    for (char c : s) {
        if ('0'<= c  && c <= '9') {
            num += c;
        } else {
            res.push_back({c, stoi(num)});
            num = "";
        }
    }
    return res;
}

int main() {
    string s1,s2;
    getline(cin, s1);
    getline(cin,s2);

    list<pair<char, int>> list1 = splitStr(s1);//REVIEW 用链表更适合保存
    list<pair<char, int>> list2 = splitStr(s2);
    
    int diff = 0;//REVIEW  不同和相同单独计数
    int same = 0;
    while (!list1.empty()) {
        pair<char, int> p1 = list1.front();
        list1.pop_front();
        pair<char, int> p2 = list2.front();
        list2.pop_front();
        // 本次比较的数量
        int compareNum = min(p1.second, p2.second);
        
        if (p1.first == p2.first) {//REVIEW  每次比较对只有两种情况 字母相同和不同
            same += compareNum;
        } else {
            diff += compareNum;
        }
        //REVIEW 多余数量重新插入下次再进行比较
        if (p1.second > compareNum) {
            list1.push_front({p1.first, p1.second - compareNum});
        }

        if (p2.second > compareNum) {
            list2.push_front({p2.first, p2.second - compareNum});
        }
    }
    cout << to_string(diff) + "/" + to_string(diff + same);
  
    return 0;
}
