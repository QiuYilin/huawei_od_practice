#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
//子问题① 移动
//子问题② 查找
//子问题③ 插入
//子问题④ 替换
//子问题⑤ 删除
//思路：翻译成string基本操作
int main(){
    //预处理
    int n = 0;
    std::string s;
    std::cin >> n;
    //std::cin >> s;
    std::cin.ignore();
    std::getline(std::cin,s);
    std::vector<std::pair<std::string,std::string>> commands;//用pair存指令
    for(int i=0;i<n;i++){
        std::string com;
        std::string value;
        std::cin >> com >> value;
        commands.push_back({com,value});
    }
    int start = 0;
    for(int i=0;i<n;i++){
        std::string com = commands[i].first;
        std::string val = commands[i].second;
        if(com=="FORWARD"){//REVIEW 这种判断尤其要注意拼写 最好是复制粘贴
            start = std::min((int)s.size(),start+std::stoi(val));//REVIEW1 min在头文件algorithm中 考虑到符号问题 必须使用同类型的整型
        }
        else if(com=="BACKWARD"){
            start = std::max(0,start-std::stoi(val));
        }
        else if(com=="SEARCH-FORWARD"){
            auto pos = s.find(val);
            if(pos != std::string::npos){//REVIEW2 npos在string作用域
                start = pos;
            }
        }
        else if(com=="SEARCH-BACKWARD"){
            auto pos = s.rfind(val,start);//REVIEW3 逆向查找有rfind
            if(pos != std::string::npos){
                start = pos;
            }
        }
        else if(com=="INSERT"){
            s.insert(start,val);//REVIEW string的方法都不使用迭代器
            start +=val.size();
        }
        else if(com =="REPLACE"){
            if(start+val.size()<=s.size()){
                s.replace(start,val.size(),val);
            }
            else{
                s.replace(start,s.size()-start,val);
            }
        }
        else if(com =="DELETE"){
            if(start+std::stoi(val)<=s.size()){
              s.erase(start,std::stoi(val));
            }
            else{
              s.erase(start,s.size()-start);
            }
        }
    }
    std::cout << s << std::endl;
    return 0;
}