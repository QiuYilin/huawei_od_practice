// 4 5 6 
// 5          6 4
// 5 7 0
// 5 7        6 4 0
// 5 7 1      
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <deque>
int main(){
    //TODO 预处理
    std::string s;
    std::vector<int> input1;
    std::vector<int> input2;
    std::getline(std::cin,s);
    std::stringstream ss(s);
    std::string m;
    std::string result;
    while(std::getline(ss,m,',')){
        input1.push_back(std::stoi(m));
    }
    std::getline(std::cin,s);
    ss = std::stringstream(s);
    while(std::getline(ss,m,',')){
        input2.push_back(std::stoi(m));
    }   
    std::deque<int> teacher_que;
    int j = 0;
    for(int i =0;i<input2.size();i++){
        //①如果左右两端都没有需要的元素
        if(teacher_que.empty()||(teacher_que.front()!=input2[i]
           &&teacher_que.back()!=input2[i])){
            while(j<input1.size()&&input1[j]!=input2[i]){
                teacher_que.push_back(input1[j]);
                j++;
            }
            if(j==input1.size()){
                result = "NO";
                break;
            }
            //REVIEW1.要搞清楚当前j是什么，每次pop都要考虑容器容量
            else if(teacher_que.empty()){
                result+="L";
                j++;    
            }
            else{
                result+="R";
                j++;       
            }
        }
        //②左边有想要的元素
        else if(teacher_que.front()==input2[i]){
            result+="L";
            teacher_que.pop_front();
        }
        //③右边有想要的元素
        else{
            result+="R";
            teacher_que.pop_back();
        }
    }
    std::cout << result << std::endl;
    return 0;
}