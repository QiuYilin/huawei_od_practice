#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// 对当前选择牌进行编码，用#连接组合
string encode(vector<int> cards) {
    string encoded;
    for (auto& card : cards) {
        encoded += to_string(card);
        encoded += "#";
    }
    return encoded;
}

// 保证最终结果牌的顺序递增，构造顺序字符用于去重
void handleCard(vector<string>& path, set<string>& result) {
    // 拷贝，防止影响原路径递归回溯
    vector<string> pathCopy = path;
    // 升序保证同牌key唯一
    sort(pathCopy.begin(), pathCopy.end());
    // 构造字符串作为key
    string key;
    // 用|连接不同组合
    for (auto& card : pathCopy) {
        key += card;
        key += "|";
    }
    result.insert(key);
}

// DFS 判断剩余牌能否全部组成面子
// 参数：cnt(牌计数), path(当前面子组合), result(结果集)
void dfs(vector<int>& cnt, vector<string>& path, set<string>& result) {
    // 找到第一张还存在的牌
    int i = -1;
    for (int j = 0; j < 27; j++) {
        if (cnt[j] > 0) {
            i = j;
            break;
        }
    }

    // 全部取完，存储path
    if (i == -1) {
        handleCard(path, result);
        return;
    }

    // 尝试刻子
    if (cnt[i] >= 3) {
        cnt[i] -= 3;
        path.push_back(encode({i, i, i}));
        dfs(cnt, path, result);
        path.pop_back();
        cnt[i] += 3;
    }

    // 尝试顺子
    int suit = i / 9;
    int rank = i % 9;

    // 点数必须 <= 7
    if (rank <= 6) {
        int a = i;
        int b = i + 1;
        int c = i + 2;

        // 保证同花色
        if (b / 9 == suit && c / 9 == suit &&
            cnt[a] > 0 && cnt[b] > 0 && cnt[c] > 0) {

            cnt[a]--;
            cnt[b]--;
            cnt[c]--;
            path.push_back(encode({a, b, c}));

            dfs(cnt, path, result);

            path.pop_back();
            cnt[a]++;
            cnt[b]++;
            cnt[c]++;
        }
    }
}

int winCardCount(vector<int>& suit, vector<int>& rank) {
    // 统计牌
    vector<int> cnt(27, 0);
    for (int i = 0; i < 14; i++) {
        int id = (suit[i] - 1) * 9 + (rank[i] - 1);
        cnt[id]++;
    }

    set<string> result;
    vector<string> path;

    // 枚举将牌
    for (int i = 0; i < 27; i++) {
        if (cnt[i] >= 2) {
            cnt[i] -= 2;
            path.push_back(encode({i, i}));
            dfs(cnt, path, result);
            path.pop_back();
            cnt[i] += 2;
        }
    }

    return result.size();
}

int main() {
    vector<int> suit(14);
    vector<int> number(14);

    for (int i = 0; i < 14; i++) {
        cin >> suit[i];
    }

    for (int i = 0; i < 14; i++) {
        cin >> number[i];
    }

    int ans = winCardCount(suit, number);
    cout << ans << endl;

    return 0;
}