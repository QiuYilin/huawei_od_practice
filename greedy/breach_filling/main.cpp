#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std;


//REVIEW 规律 对于每个缺陷 优先取=need的木材 其次大于need的最短 其次最接近
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


int main() {
    int m,n;
    string str1,str2;
    cin >> n >> str1 >> m >> str2;
    vector<int> hight = split(str1, ",");
    vector<int> woods = split(str2, ",");
    
    // 记录需要填充的溃口及高度
    vector<int> need;
    for (int i  = 1; i < n -1; i++) {
        int diff = hight[0] - hight[i];
        if (diff > 0) {
            need.push_back(diff);
           
        }
    }

    // 统计各个木材数量
    vector<int> count(17,0);
    for (auto &height : woods) {
        count[height]++;
    }
    
    // 记录木材耗费
    int sum = 0;

    for (int i = 0; i < need.size(); i++) {
        int needHight = need[i];

        // 使用贪心，优先从选取大于等于needHight，如果不存在选择小于needHight
        bool flag = false;
        for (int j = needHight; j < 17; j++) {
            if (count[j] > 0) {
                count[j]--;
                sum += j;
                flag = true;
                break;
            }
        }

    
        for (int j = needHight -1 ; j > 0 && !flag; j--) {
            if (count[j] > 0) {
                count[j]--;
                sum += j;
                flag = true;
                break;
            }
        }
        // 说明所有木材都被使用了
        if (!flag) {
            break;
        }
    }

    cout << sum;
    return 0;
}
