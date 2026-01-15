#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

std::string intToHex(int num) {//REVIEW 十进制转十六进制的方法也可以借助stringstream
    std::stringstream ss;
    ss << std::hex << std::uppercase << num;
    std::string result = ss.str();
    if (result.length() < 2) {
        result = "0" + result;
    }
    return result;
}

int main() {
    unsigned long long input;  // REVIEW 使用unsigned long long以支持大数
    std::cin >> input;
    
    std::string result;
    
    if (input == 0) {
        result = "00";
    } else {
        while (input > 0) {
            // 取低7位
            unsigned char byte = input & 0b1111111;//REVIEW 使用位操作 避免使用辗转相除等繁琐的转换
            
            // 右移7位，准备处理下一个字节
            input >>= 7;
            
            // 如果还有后续字节，设置最高位为1
            if (input > 0) {
                byte |= 0x80;  // 设置最高位为1
            }
            // 否则最高位保持为0（默认）
            
            // 将字节转换为16进制并添加到结果中
            result += intToHex(byte);
        }
    }
    
    std::cout << result << std::endl;
    return 0;
}