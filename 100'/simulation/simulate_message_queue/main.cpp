#include <vector>

#include <iostream>
#include <sstream>

#include <algorithm>
//一个发布者 若干消费者
//优先级判断 越后越优先
//思路 区间问题？ 优先满足后面的消费者 消息队列用什么存 涉及删除
    //map  pair不支持哈希
    //vector 10^6删除可以接受  但是动态删除影响迭代器 
int main(){
    std::vector<std::pair<int,int>> mes;
    std::string line;
    std::getline(std::cin,line);
    std::stringstream ss(line);
    int tmp = 0;
    std::pair<int,int> m;
    while(ss>>tmp){
        m.first=tmp;
        ss>>m.second;
        mes.push_back(m);
    }
    std::vector<std::pair<int,int>> consumers;
    std::getline(std::cin,line);
    ss = std::stringstream(line);
    std::pair<int,int> c;
    while(ss>>tmp){
        c.first=tmp;
        ss>>c.second;
        consumers.push_back(c);
    }
    std::sort(mes.begin(),mes.end(),[](std::pair<int,int> a,std::pair<int,int> b){
        if(a.first < b.first){
            return true;
        }
        else{
            return false;
        }
    });//为什么不用自定义
    std::vector<std::vector<int>> results(consumers.size(),std::vector<int>{});
    // std::vector<int> deleted_indexs;
    // for(int i=consumers.size()-1;i>=0;i--){
    //     std::vector<int> result;
    //     for(int j=0;j<mes.size();j++){
    //         //REVIEW 针对pair 每个first和end都要记得是什么 最好用临时变量
    //         if(std::find(deleted_indexs.begin(),deleted_indexs.end(),j)==deleted_indexs.end()&&mes[j].first>=consumers[i].first&&mes[j].first < consumers[i].second){
    //             result.push_back(mes[j].second);
    //             deleted_indexs.push_back(j);
    //         }
    //     }
    //     results.push_back(result);
    // }
    for(int j=0;j<mes.size();j++){//REVIEW 最外层的循环可以保证只处理一次。
        for(int i=consumers.size()-1;i>=0;i--){
            //REVIEW 针对pair 每个first和end都要记得是什么 最好用临时变量
            if(mes[j].first>=consumers[i].first&&mes[j].first < consumers[i].second){
                results[i].push_back(mes[j].second);
                break;
            }
        }
    }
    //std::reverse(results.begin(),results.end());

        for(int i=0;i<results.size();i++){
            if(results[i].empty()){
                std::cout << "-1";
            }
            else{
                for(int j=0;j<results[i].size();j++){
                if(j>0){//REVIEW 比布尔值高效
                    std::cout << " ";
                }
                std::cout << results[i][j];
                }
            }
            std::cout << std::endl;
        }
    
    return 0;
}