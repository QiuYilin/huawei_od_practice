#include <iostream>
#include <sstream>

#include <vector>

#include <climits>
//REVIEW  字节越右越高

int main(){
    int n;//REVIEW 无符号8位 用int很宽裕
    std::cin >> n;
    std::vector<std::pair<int,int>> input;
    std::cin.ignore();//REVIEW cin之后跟getline要忽略回车
    for(int i=0;i<n;i++){
        std::string line;
        std::getline(std::cin,line);
        std::stringstream ss(line);
        int  t=0;
        int  m=0;
        ss>>t>>m;
        input.push_back({t,m});
    }
    int res_time = INT_MAX;//REVIEW 需要climits头文件
    for(int j=0;j<n;j++){
        int actual_m = 0;
        int m = input[j].second;
        if(m>=128){
            int mant = m&0b1111;
            int exp = (m&0b01110000)>>4;
            actual_m = (mant|0x10)<<(exp+3);
        }
        else{
            actual_m = m;
        }
        res_time = std::min(res_time,input[j].first+actual_m);
    }
    std::cout << res_time;
    return 0;
}
