#include <iostream>
#include <string>

int main(){
    //疑问 kmp的复杂度
    //k 0~n n/k是整数
    //用正则会怎么样
    //kmp find找到匹配的第一个位置
    //本体 拼接起来 去掉头尾
    //a bcabcabcab c  3
    int n;
    std::cin >> n;
    std::string s(n,'0');//REVIEW 和vector不同 string必须明确字符
    for(int i=0;i<n;i++){
      std::cin >> s[i];
    }
    auto ss = s+s;
    auto index = ss.find(s,1);
    for(int i=0;i<index;i++){
        if(i!=0){
            std::cout << " ";
        }
        std::cout << s[i];
    }
    std::cout << std::endl;
    return 0;
}