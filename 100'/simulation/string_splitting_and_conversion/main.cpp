#include <iostream>
#include <string>
#include <vector>
#include <sstream>
int countUpper(std::string s){
    int count = 0;
    for(auto c:s){
        if(std::isupper(c)){
            count++;
        }
    }
    return count;
}
int countLower(std::string s){
    int count = 0;
    for(auto c:s){
        if(std::islower(c)){
            count++;
        }
    }
    return count;
}
int main(){
    int k = 0;
    std::cin >> k;
    std::cin.ignore();
    std::string input;
    std::string first_w;
    std::getline(std::cin,first_w,'-');
    std::string s;
    std::vector<std::string> result;
    result.push_back(first_w);
    std::getline(std::cin,s);//自定义getline会忽略回车
    std::stringstream ss(s);
    while(std::getline(ss,s,'-')){
        input+=s;
    }
    for(int i=0;i<input.size();i+=k){
        auto sub_s = input.substr(i,std::min(k,(int)input.size()-i));//int应该写在哪
        if(countLower(sub_s)>countUpper(sub_s)){
            for(auto &c:sub_s){
                c=std::tolower(c);
            }
        }
        else if(countLower(sub_s)<countUpper(sub_s)){
            for(auto &c:sub_s){
                c=std::toupper(c);
            }
        }
        result.push_back(sub_s);
    }
    for(int i=0;i<result.size();i++){
        if(i>0){
            std::cout << "-";
        }
        std::cout << result[i];
    }
    std::cout << std::endl;
    return 0;
}