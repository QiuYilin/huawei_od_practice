#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
struct record{
    int idx = 0;
    int id=0;
    int time=0;
    int distance=0;
    std::string actualDeviceNumber{};
    std::string registeredDeviceNumber{};
};

int main(){
    int n =0;
    std::cin >> n;
    std::cin.ignore(); //①文本输入时需要。
    std::vector<record> records;
    std::string l;
    std::set<int> result_index;//③已知数组情况下，使用索引set可以方便去重同时不需要自定义哈希。
    //④一对多数据结构，不需要删除操作，使用map<int,vector>
    //⑤子问题，这里数据量不大用n^2
    std::map<int,std::vector<record>> map;
    for(int i=0;i<n;i++){
        std::getline(std::cin,l);
        std::stringstream ss(l);
        std::vector<std::string> r;
        std::string s;
        while(std::getline(ss,s,',')){
            r.push_back(s);
        }
        record rr;
        rr.idx = i;
        rr.id=std::stoi(r[0]);
        rr.time =std::stoi(r[1]);
        rr.distance=std::stoi(r[2]);
        rr.actualDeviceNumber=r[3];
        rr.registeredDeviceNumber=r[4];
        records.push_back(rr);
        map[rr.id].push_back(rr);
    }

    for(int i=0;i<records.size();i++){
        if(records[i].actualDeviceNumber!=records[i].registeredDeviceNumber){
            result_index.insert(i);
        }
        for(int j=0;j<map[records[i].id].size();j++){
            if(std::abs(records[i].time-map[records[i].id][j].time)<60
            &&std::abs(records[i].distance-map[records[i].id][j].distance)>5){   
                result_index.insert(map[records[i].id][j].idx);
                result_index.insert(i);
            }
        }
    }
    if(result_index.empty()){
        std::cout << "null" << std::endl;
    }
    else {
        bool isFirst = true;//②x,x,x格式输出技巧
        for (int index : result_index) {
            if (!isFirst) {
                std::cout << ";";
            }
            std::cout << records[index].id << "," << records[index].time 
                    << "," << records[index].distance << "," << records[index].actualDeviceNumber
                    << "," << records[index].registeredDeviceNumber;
            isFirst = false;
        }
        std::cout << std::endl;
    }
    return 0;
}