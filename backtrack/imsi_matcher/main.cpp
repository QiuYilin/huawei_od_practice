#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
//TODO 动态规划解
bool match(std::string config,int i,std::string imsi,int j){
    if(i==config.size()&&j==imsi.size()){
        return true;
    }
    if(i==config.size()&&j!=imsi.size()){
        return false;
    }
    if(i!=config.size()&&j==imsi.size()){
        return false;
    }
    if(config[i]==imsi[j]){
        return match(config,i+1,imsi,j+1);
    }
    else if(config[i]=='*'){
        return match(config,i+1,imsi,j)||match(config,i,imsi,j+1)||match(config,i+1,imsi,j+1);
    }
    else if(config[i]=='?'){
        if(i%2==0){
            return false;
        }
        else{
            match(config,i+1,imsi,j+1);
        }
    }
    return false;
}
int main() {
    std::string configs;
    std::cin >> configs;
    std::stringstream ss(configs);
    std::vector<std::string> config;
    std::string s;
    while(std::getline(ss,s,',')){
        config.push_back(s);
    }
    std::string imsi;
    std::cin >> imsi;
    std::vector<std::string> result;
    
    for(int i=0;i<config.size();i++){
        if(match(config[i],0,imsi,0)){
            result.push_back(config[i]);
        }
    }
    std::sort(result.begin(),result.end());
    if(result.empty()){
        std::cout << "null" << std::endl;
    }
    else{
        for(int i=0;i<result.size();i++){
            std::cout << result[i];
            if(i!=result.size()-1){
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}