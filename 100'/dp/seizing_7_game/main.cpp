#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
using namespace std;
//REVIEW 审题 补充X-Y>0
//REVIEW dpA[i] 从m报到i A含i的方案数
//dpB[i]=dpA[i+1] + dpA[i+2]
//dpA[i]=dpB[i+1] + dpB[i+2]

//REVIEW 利用字符串 实现两个大整数的加法
// 1. 末位对齐，从右向左
// 2. 逐位相加，进位紧跟
// 3. 双指针移，三目判断
// *4. 和求余数，进求整除
// 5. 结果反转，返回答案

//某种程度的同向双指针
string addBigNumbers(const string& num1, const string& num2) {
    string res;
    //进位
    int carry = 0;

    //末位对齐，从右向左
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    //逐位相加 同时考虑进位
    //456 + 15
    //sum = 6+5+0 =11
    //res = 10
    //carry = 1
    //sum = 5+1
    while (i >= 0 || j >= 0 || carry) {
        //指针向左位移
        int digit1 = i >= 0 ? (num1[i--] - '0') : 0;//num1当前处理位的数值 主循环判断逻辑是或 很可能两个数字长度不一样
        int digit2 = j >= 0 ? (num2[j--] - '0') : 0;//num2当前处理位的数值
        int sum = digit1 + digit2 + carry;
        res += (sum % 10 + '0');//结果的表达 对10的余数+0
        carry = sum / 10;//进位的表达：除以10
    }

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    int m;
    cin >> m;
    // i 由 i+1 i+2 累加得来，所以定义长度为m + 2
    // REVIEW 初始化逻辑
    vector<string> dpA(m + 2, "0");
    dpA[m] = "1";
    vector<string> dpB(m + 2, "0");
    for (int i = m - 1; i >= 7; i--) {
        // B得出的方案数 由 A叫 i + 1  + 叫 i+2 的方案数得来
        dpB[i] =  addBigNumbers(dpA[i + 1],dpA[i + 2]);
        // A得出的方案数 由 B叫 i + 1  + 叫 i+2 的方案数得来
        dpA[i] = addBigNumbers(dpB[i + 1],dpB[i + 2]);
    }
    cout << dpB[7];
    return 0;
}
