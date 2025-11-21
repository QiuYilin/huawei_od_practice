#include <array>
#include <vector>
#include <iostream>
#include <sstream>
//题意 相同数字有没有上限？ 没有
//数字出现频率
//频率>=4 频率=3 a.葫芦 b.三张
//频率=2 对   频率=1 单张
//难点 葫芦和三张有点麻烦
//贪心 葫芦是最大的三张 + max(剩余最大的三张中的两张,对)
bool hasThree(std::array<int,13> array){
    for(int i=0;i<array.size();i++){
        if(array[i]==3){
            return true;
        }
    }
    return false;
}

int main(){
    std::array<int,13> array{};//REVIEW array没有构造函数 不能默认初始化。
    std::string line;
    std::getline(std::cin,line);
    std::stringstream ss(line);
    int a = 0;
    while(ss>>a){
        array[a-1]++;
    }
    std::vector<int> result;
    //先挑出炸弹
    for(int i=array.size()-1;i>=0;i--){
        if(array[i]>=4){
            //疑问vector有添加多个元素的功能么
            for(int j=0;j<array[i];j++){
                result.push_back(i+1);
            }
            array[i]=0;//有必要么
        }
    }
    //再挑出葫芦和三张
    while(hasThree(array)){
        for(int i=array.size()-1;i>=0;i--){   
        if(array[i]==3){
            for(int j=0;j<3;j++){
                result.push_back(i+1);
            }
            array[i]=0;
            //REVIEW 遍历比i小的三张和倒序的所有对
            for(int j=array.size()-1;j>=0;j--){
                if(j==i){
                    continue;
                }
                if(array[j]==3||array[j]==2){
                    for(int k=0;k<2;k++){
                        result.push_back(j+1);
                    }
                    array[j]-=2;
                    break;
                }
            }
        }
    }
    }
    //挑出对
    for(int i=array.size()-1;i>=0;i--){
        if(array[i]==2){
            for(int j=0;j<2;j++){
                result.push_back(i+1);
            }
            array[i]=0;
        }
    }
    //挑出单张
    for(int i=array.size()-1;i>=0;i--){
        if(array[i]==1){
            result.push_back(i+1);
            array[i]=0;
        }
    }
    bool isFirst = true;
    for(int i=0;i<result.size();i++){
        if(!isFirst){
            std::cout << " ";
        }
        std::cout << result[i];
        isFirst = false;
    }
    std::cout << std::endl;
    return 0;
}

