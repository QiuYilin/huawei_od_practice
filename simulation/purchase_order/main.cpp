#include <iostream>

#include <vector>

#include <algorithm>
#include <cmath>
//审批判断
//单价高于100元的商品需要单独处理
//单价<=100的相同商品可以合并一个PO
//<100 数量>=100 可以打9折

//PR转PO

//要不要先写逻辑图
int main(){
    //数据结构 
    //①multi_map?   高价物品不能合并 存在同id
    //②二维数组
    int n = 0;
    std::cin >> n;
    std::vector<std::vector<int>> pos;//这里能直接定义成3个元素的vec吗
    for(int i=0;i<n;i++){
        int state = 0;
        std::vector<int> pr(3,0);
        std::cin >> pr[0] >> pr[1] >> pr[2] >> state;
        if(state == 0){
            pos.push_back(pr);
        }
    }
    std::sort(pos.begin(),pos.end(),[](const std::vector<int> &a,const std::vector<int> &b){
        if(a[0]<b[0]){
            return true;
        }
        else if(a[0]>b[0]){
            return false;
        }
        else{
            if(a[1]>b[1]){
                return true;
            }
            else{
                return false;
            }
        }
    });
    std::vector<std::vector<int>> result;
    for(int i=0;i<pos.size();i++){
        if(pos[i][2]>100){
            result.push_back(pos[i]);
        }
        else{
            if(!result.empty()&&result.back()[0]==pos[i][0]){
                result.back()[1]+=pos[i][1];
                //result.back()[2]+=pos[i][2];
            }
            else{
                result.push_back(pos[i]);
            }
        }
    }
    for(int j=0;j<result.size();j++){
        if(result[j][1]>=100&&result[j][2]<=100){//REVIEW 题目有问题
            //REVIEW 子问题 向上取整 cmath头文件
            result[j][2]=std::ceil(result[j][2]*0.9);
        }
        bool isFirst = true;
        for(int k=0;k<3;k++){
            if(!isFirst){
                std::cout << " ";
            }
            std::cout << result[j][k];
            isFirst = false;
        }
        std::cout << std::endl;
    }
    return 0;
}