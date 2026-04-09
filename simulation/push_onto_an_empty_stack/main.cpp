#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<stack>
using namespace std;

int main() {
    vector<int> ans;//REVIEW 用vec结构
    int tmp;
    while (cin >> tmp) {
        ans.push_back(tmp); 
    }

    int n = ans.size();
    //REVIEW 用stk和pos模拟栈
    vector<int> stk(n,0);
    int pos = 0;
    for (int i = 0; i < n; i++) {
        long sum = ans[i];//REVIEW 数据量很大
        long tmp = sum;
        
        // 递归进行压栈判断
        while (pos > 0 && tmp >=0) {
            int j = pos - 1;
            for (; j >=0; j--) {
                tmp -= stk[j];
                if (tmp <= 0) {
                    break;
                }
            }
            // 满足条件，更新元素
            if (tmp == 0) {
                sum = 2 * sum;
                pos = j;
                tmp = sum;
            } else {
                break;
            }
        }

        stk[pos++] = sum;
    }
    
    for (int i = pos -1; i >=0;i--) {
        cout << stk[i] << " ";
    }
    return 0;
}
