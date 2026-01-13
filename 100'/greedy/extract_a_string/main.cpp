#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;
//REVEIW 虽然要求顺序但是依然可以用哈希 不过要用两个哈希 计数的哈希用链式推进 
//REVIEW B不会重复->用哈希记录位置索引
int main() {
    string A,B;
    cin >> A >> B;
    
    map<char, int> charPos;
    // 统计B字符串各个字符的位置
    for (int i = 0; i <  B.size(); i++) {
        charPos[B[i]] = i;
    }
    
    vector<int> count(B.size(), 0);//REVIEW 表示匹配到当前位置的数量
    
    for (auto c : A) {
        // 不属于B中字符直接跳过
        if (charPos.find(c) == charPos.end()) {
            continue;
        }
        int pos = charPos[c];
        
        if (pos == 0) {
            count[0]++;
        } else if (count[pos - 1] > 0) {
            count[pos-1]--;//REVIEW 消耗前一个位置的匹配
            count[pos]++;//REVIEW 完成当前位置的匹配
        }
    }

    cout << count[B.size() -1];
    return 0;
}
