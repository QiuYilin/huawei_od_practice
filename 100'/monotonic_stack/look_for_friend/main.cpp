#include <iostream>
#include <vector>
#include <stack>
int main(){
    int n;
    std::cin >> n;
    std::vector<int> input(n);
    for(int i=0;i<n;i++){
      std::cin >> input[i];
    }
    std::stack<int> s;
    std::vector<int> result(n,0);
    for(int i=0;i<n;i++){
      while(!s.empty()&&input[i]>input[s.top()]){
        result[s.top()]=i;
        s.pop();
      }
      s.push(i);
    }
    for(int i=0;i<result.size();i++){
        if(i!=0){
          std::cout << " ";
        }
        std::cout << result[i];
    }
    std::cout << std::endl;
    return 0;
}