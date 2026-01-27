#include <iostream>
#include <regex>

int main(){
    std::string s;
    std::cin >> s;
    //REVIEW .是字符不是量词
    std::string pattern;
    std::cin >> pattern;
    // auto i = pattern.find(']');//疑问 find找不到返回什么
    // if(i!=-1){
    //     pattern.insert(pattern.begin()+i,'.');//疑问  为什么insert用迭代器
    // }
    std::smatch result;
    bool flag = std::regex_search(s,result,std::regex(pattern));//REVIEW 存疑 s迭代器无效
    if(flag==false){
        std::cout << "-1" << std::endl;
    }
    else{
        std::cout << result.position() << std::endl;
    }
    return 0;
}