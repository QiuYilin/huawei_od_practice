#include <vector>
#include <unordered_map>
#include <iostream>
int main(){
    std::vector<unsigned int> input;
    int c =0;
    int b =0;
    std::cin >> c;
    std::cin >> b;
    for(int i=0;i<10;i++){
        unsigned int n = 0;
        std::cin >> n;
        input.push_back(n);
    }
    std::unordered_map<unsigned int,int> map;
    for(auto n:input){
       //REVIEW 取特定字节的基本操作是与+位移
       //REVIEW 位操作的优先级很低 + > >> >&
       unsigned int type = (((n&0xFF000000)>>24) + ((n&0x00FF0000)>>16) + ((n&0x0000FF00)>>8) + (n&0x000000FF))%b;
       if(type<c){
         map[type]++;
       }
    }
    int result = 0;
 
        for(auto it : map){
            if(it.second>result){
                result = it.second;
            }
        }
    std::cout << result << std::endl;
    return 0;
}