#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<queue>
using namespace std;

//REVIEW 贪心规律 在非空队列的头部进入了插入
int main() {
   int n;
   cin >> n;
   int res = 0;
   //去除换行符
   string s;
   getline(cin, s);
   bool is_order = true;
   int count = 0;//REVIEW 当前队列中元素的个数
   for (int i = 0; i < 2 * n; i++) {
      getline(cin, s);
      if (s.find("remove") != -1) {
            // 只在移除的时候进行调整
            if (!is_order) {
                res++;
            }
            is_order = true;
            count--;
      } else if (s.find("tail") != -1) {
        count++;
      } else {
        // 添加在头部会导致移除时乱序
        if (count) {
            is_order = false;
        }
        count++;
      } 
   }
   cout << res;
   return 0;
}
