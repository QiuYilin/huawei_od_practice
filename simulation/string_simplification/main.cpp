    #include <iostream>
    #include <string>
    #include <vector>
    #include <set>
    #include <algorithm>

    using namespace std;

    int main() {
        string input;
        getline(cin, input);

        string output = "";
        // 记录所有等效关系 set会自动进行字典序的排序
        vector<set<char>> equivalenceSets;//REVIEW:等效关系可能有数组
        bool insideParentheses = false;

        // 遍历输入字符串
        for (char c : input) {
            if (c == '(') {
                insideParentheses = true;
                equivalenceSets.push_back(set<char>());
            } else if (c == ')') {
                insideParentheses = false;
                if (equivalenceSets.back().empty()) equivalenceSets.pop_back();
            } else {
                if (!insideParentheses) {
                    output += c;
                } else {
                    equivalenceSets.back().insert(c);
                }
            }
        }

        // REVIEW 合并操作
        bool merged = true;
        while (merged) {
            merged = false;
            for (size_t i = 0; i < equivalenceSets.size(); ++i) {
                for (size_t j = i + 1; j < equivalenceSets.size(); ++j) {
                    bool canMerge = false;
                    for (char c = 'a'; c <= 'z'; ++c) {
                        char upper = toupper(c);
                        // 考虑大小写
                        if ((equivalenceSets[i].count(c) || equivalenceSets[i].count(upper)) && 
                            (equivalenceSets[j].count(c) || equivalenceSets[j].count(upper))) {
                            canMerge = true;
                            break;
                        }
                    }
                    if (canMerge) {
                        equivalenceSets[i].insert(equivalenceSets[j].begin(), equivalenceSets[j].end());
                        equivalenceSets.erase(equivalenceSets.begin() + j);
                        merged = true;
                        break;
                    }
                }
                if (merged) break;
            }
        }

        // 替换字符为等价集合中的字典序最小字符
        for (const set<char>& set : equivalenceSets) {
            char smallestChar = *set.begin();
            for (char& c : output) {
                if (set.count(c)) c = smallestChar;
            }
        }

        cout << (output.empty() ? "0" : output) << endl;

        return 0;
    }

