题目描述
公司用一个字符串来表示员工的出勤信息

absent：缺勤
late：迟到
leaveearly：早退
present：正常上班
现需根据员工出勤信息，判断本次是否能获得出勤奖，能获得出勤奖的条件如下：

缺勤不超过一次；
没有连续的迟到/早退；
任意连续7次考勤，缺勤/迟到/早退不超过3次。
输入描述
用户的考勤数据字符串

记录条数 >= 1；
输入字符串长度 < 10000；
不存在非法输入；
如：

2
present
present absent present present leaveearly present absent

输出描述
根据考勤数据字符串，如果能得到考勤奖，输出”true”；否则输出”false”，
对于输入示例的结果应为：

true false

示例1
输入
2
present
present present

输出
true true

说明

无

示例2
输入
2
present
present absent present present leaveearly present absent

输出
true false

说明

