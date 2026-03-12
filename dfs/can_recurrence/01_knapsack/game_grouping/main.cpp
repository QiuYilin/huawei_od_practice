#include <iostream>
#include <sstream>

#include <vector>
#include <algorithm>
#include <numeric>
//dfs(i,j)=max(dfs(i-1,j),dfs(i,j-w[i])+v[i])
int dfs(std::vector<int> score,int index,int sum){
  if(){
    
  }
}

int main(){
    std::string line;
    std::getline(std::cin,line);
    std::string e;
    std::vector<int> score;
    while(std::cin >> e){
      score.push_back(std::stoi(e));
    }
    int sum = std::accumulate(score.begin(),score.end(),0);
    int half = sum/2;
    int max_value = dfs(score,score.size()-1,half);
    return 0;
}