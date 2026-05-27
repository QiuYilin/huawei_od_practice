#include <cwctype>
#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
using namespace std; 

// 通用 切割函数 函数 将字符串str根据delimiter进行切割
vector<long> split(const string& str, const string& delimiter) {//REVIEW 内存管理用long long更好
    vector<long> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(stol(str.substr(start, end - start)));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // 添加最后一个部分
    result.push_back(stol(str.substr(start)));
    return result;
}

// 向上对齐
long  alignUp(long  x, long  align) {
    return (x + align - 1) / align * align;//REVIEW 向上取整*align
}

//REVIEW 环形缓冲区有两种状态 writeIndex >= readIndex（未绕回）和  writeIndex < readIndex（已绕回）
int getWriteIndex(long capacity, long align, long readIndex, long writeIndex, long pktSize) {
    // 当前已使用空间
    long used = (writeIndex - readIndex + capacity) % capacity;
    // 剩余空间
    long freeSpace = capacity - used;
    
    // 考虑到writeIndex本身不对齐，获取真正写入位置
    long start = alignUp(writeIndex, align);

    long end = start + pktSize;

    // 实际占用空间 write -> start 需要 padding + 数据本身
    long need = end - writeIndex;

    if (need > freeSpace) {
        return -1;
    }

    return end % capacity;
}

int main() {
    string input;
    getline(cin, input);

    vector<long> nums = split(input, ",");
    int res = getWriteIndex(nums[0], nums[1], nums[2], nums[3], nums[4]);
    cout << res;
    return 0;

}
