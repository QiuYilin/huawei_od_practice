#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <climits>
void getNextSmaller(std::vector<int> input,std::vector<int> &next_smaller){
  std::stack<int> stack;
  for(int i=0;i<input.size();i++){
    while(!stack.empty()&&input[i]>input[stack.top()]){
        next_smaller[stack.top()]=i;
        stack.pop();
    }
    stack.push(i);
  }
}

void getPrevSmaller(std::vector<int> input,std::vector<int> &prev_smaller){
  std::stack<int> stack;
  for(int i=input.size()-1;i>=0;i--){
    while(!stack.empty()&&input[i]>input[stack.top()]){
        prev_smaller[stack.top()]=i;
        stack.pop();
    }
    stack.push(i);
  }
}

int main(){
    std::vector<int> input;
    std::string e;
    while(std::cin >> e){
        input.push_back(std::stoi(e));
    }
    if(input.size()<3){
        std::cout << -1 << std::endl;
        return 0;
    }
    std::vector<int> next_smaller(input.size(),-1);
    std::vector<int> prev_smaller(input.size(),-1);
    
    getNextSmaller(input,next_smaller);
    getPrevSmaller(input,prev_smaller);

    int result = INT_MAX;
    
    for(int i=1;i<input.size()-1;i++){
        if(next_smaller[i]==-1||prev_smaller[i]==-1){
            continue;
        }
        result = std::min(result,next_smaller[i]-prev_smaller[i]);
    }

    if(result==INT_MAX){
        std::cout << -1 << std::endl;
    }
    else{
        std::cout << result << std::endl;
    }
    return 0;
}