#include <cstdio>
#include <ctime>
#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<map>
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
    map<string, int> card_to_number = {
        {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7},
        {"8", 8}, {"9", 9}, {"10", 10}, {"J", 11}, {"Q", 12},
        {"K", 13}, {"A", 14}, {"2", 16}
    };//REVIEW 用map简化
    string s = "";
    getline(cin, s);
    vector<string> cards = split(s, " ");
    sort(cards.begin(), cards.end(), [&card_to_number](const string& a, const string& b) {
        return card_to_number[a] < card_to_number[b];
    });//排序

    vector<vector<string>> res;
    vector<string> tmp;
    tmp.push_back(cards[0]);
    res.push_back(tmp);

    //REVIEW 规律：遍历排序后的卡组，如果和tmp中最后一张能衔接就加入顺子 否则另起一个顺子
    for (int i = 1; i < cards.size(); i++) {
        bool is_match = false;
        for (auto &tmp : res) {
            // 优先选择之前顺子连接
            if (card_to_number[cards[i]] - card_to_number[tmp.back()] == 1) {
                is_match = true;
                tmp.push_back(cards[i]);
                break;
            }
        }
        // 作为新顺子的起始牌
        if (!is_match) {
            vector<string> newItem;
            newItem.push_back(cards[i]);
            res.push_back(newItem);
        }
    }

    bool is_match = false;
    for (int i = 0; i < res.size(); i++) {
        if (res[i].size() >= 5) {
            is_match = true;
            for (int j = 0; j < res[i].size(); j++) {
                if (j != 0) {
                    cout <<" ";
                }
                cout << res[i][j];                
            }
            cout << endl;
        }
    }

    if (!is_match) {
        cout << "No" << endl;
    }
    return 0;
}
