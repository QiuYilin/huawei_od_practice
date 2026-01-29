题目描述
找到它是个小游戏，你需要在一个矩阵中找到给定的单词

假设给定单词HELLOWORLD，在矩阵中只要能找HELLOWORLD就算通过

注意区分英文字母大小写，并且你只能上下左右行走，不能走回头路

输入描述
输入第一行包含两个整数N M (0 < N, M < 21)

分别表示N行M列的矩阵

第二行是长度不超过100的单词W

在整个矩阵中给定单词W只会出现一次

从第3行到第N+2是只包含大小写英文字母的长度为M的字符串矩阵

输出描述
如果能在矩阵中连成给定的单词，则输出给定单词首字母在矩阵中的位置为第几行第几列 否则输出 NO

示例1
输入
5 5
HELLOWORLD
CPUCY
EKLQH
CHELL
LROWO
DGRBC
输出
3 2
示例2
输入
5 5
Helloworld
CPUCh
wolle
orldO
EKLQo
PGRBC

输出
NO