#include <iostream>
#include <sstream>

#include <vector>
//审题 Cn 2 判断
//子问题 怎么判断没有重复 26个字母
//穷举 2^26

int main(){
    
    std::string line;
    std::cin >> line;
    std::stringstream ss(line);
    std::string s;
    std::vector<std::pair<int,int>> inputs;
    while(std::getline(ss,s,',')){
      int e = 1<<26;
      for(int i=0;i<s.size();i++){
        e=e|(1<<(s[i]-'a'));
      }
      inputs.push_back({e,s.size()});
    }
    int result =0;
    for(int i=0;i<inputs.size()-1;i++){
        for(int j=i+1;j<inputs.size();j++){
            if((inputs[i].first&inputs[j].first)==1<<26){
                result=std::max(result,inputs[i].second*inputs[j].second);
            }
        }
    }
    std::cout << result << std::endl;
    return 0;
}
