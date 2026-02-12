#include <vector>
#include <string>

#include <iostream>
#include <sstream>

#include <algorithm>
//思路：
// 0 1
// 4 5 6 7

//①1 1 3 2 4
//②2 2 4 3
//③4 4
//④8 8

int main(){
    std::vector<int> array1;
    std::vector<int> array2;
    std::string input;
    std::getline(std::cin,input);
    
    auto start = input.find('[');
    auto end = input.find(']');
    if(!input.empty()){
        input = input.substr(start+1,end-start-1);//REVIEW 处理[]形式的输入
    }
    std::stringstream ss(input);
    std::string s;
    std::vector<std::vector<int>> result;
    while(std::getline(ss,s,',')){
        int v = std::stoi(s);
        if(v<4){
            array1.push_back(v);
        }
        else{
            array2.push_back(v);
        }
    }
    std::sort(array1.begin(),array1.end());
    std::sort(array2.begin(),array2.end());
    // for(auto n:array1){
    //     std::cout << n;
    // }
    // std::cout << std::endl;
    // for(auto n:array2){
    //     std::cout << n;
    // }
    //std::cout << std::endl;
    int number = 0;
    std::cin >> number;

    if(number==8){
        if(array1.size()==4&&array2.size()==4){
            result.push_back({0,1,2,3,4,5,6,7});
        }
    }
    else if(number==4){
        if(array1.size()==4){
            result.push_back(array1);
        }
        if(array2.size()==4){
            result.push_back(array2);
        }
    }
    else if(number==1){
        if(array1.size()==1||array2.size()==1){
            if(array1.size()==1){
                result.push_back(array1);
            }
            if(array2.size()==1){
                result.push_back(array2);
            }
        }
        else if(array1.size()==3||array2.size()==3){
            if(array1.size()==3){
                for(int i=0;i<3;i++){
                    result.push_back({array1[i]});
                }
            }
            if(array2.size()==3){
                for(int i=0;i<3;i++){
                    result.push_back({array2[i]});
                }
            }
        }
        else if(array1.size()==2||array2.size()==2){
            if(array1.size()==2){
                for(int i=0;i<2;i++){
                    result.push_back({array1[i]});
                }
            }
            if(array2.size()==2){
                for(int i=0;i<2;i++){
                    result.push_back({array2[i]});
                }
            }
        }
        else if(array1.size()==4||array2.size()==4){
            if(array1.size()==4){
                for(int i=0;i<4;i++){
                    result.push_back({array1[i]});
                }
            }
            if(array2.size()==4){
                for(int i=0;i<4;i++){
                    result.push_back({array2[i]});
                }
            }
        }
    }
    else if(number==2){//TODO 取2不需要排列算法
        if(array1.size()==2||array2.size()==2){
            if(array1.size()==2){
                result.push_back(array1);
            }
            if(array2.size()==2){
                result.push_back(array2);
            }
        }
        else if(array1.size()==4||array2.size()==4){
            if(array1.size()==4){//TODO 这里两个数组放到一个数组里更好
                std::vector<int> vec(2,0);
                for(int i=0;i<3;i++){
                    vec[0]=array1[i];
                    for(int j=i+1;j<4;j++){
                        vec[1]=array1[j];
                        result.push_back(vec);
                    }
                }
            }
            if(array2.size()==4){
                std::vector<int> vec(2,0);
                for(int i=0;i<3;i++){
                    vec[0]=array2[i];
                    for(int j=i+1;j<4;j++){
                        vec[1]=array2[j];
                        result.push_back(vec);
                    }
                }
            }
        }
        else if(array1.size()==3||array2.size()==3){
            if(array1.size()==3){
                std::vector<int> vec(2,0);
                for(int i=0;i<2;i++){
                    vec[0]=array1[i];
                    for(int j=i+1;j<3;j++){
                        vec[1]=array1[j];
                        result.push_back(vec);
                    }
                }
            }
            if(array2.size()==3){
                std::vector<int> vec(2,0);
                for(int i=0;i<2;i++){
                    vec[0]=array2[i];
                    for(int j=i+1;j<3;j++){
                        vec[1]=array2[j];
                        result.push_back(vec);
                    }
                }
            }
        }
    }
    std::cout << "[";
    bool isfirst = true;
    for(int i=0;i<result.size();i++){
        if(!isfirst){
            std::cout<<", ";
        }
        std::cout << "[";
        bool isfirst2 = true;
        for(int j=0;j<result[i].size();j++){
            if(!isfirst2){
                std::cout<<", ";//REVIEW 注意输出是否带空格
            }
            std::cout << result[i][j];
            isfirst2 =false;
        }
        std::cout << "]";
        isfirst = false;
    }
    std::cout << "]" << std::endl;
}

