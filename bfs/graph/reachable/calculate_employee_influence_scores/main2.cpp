#include <iostream>
#include <sstream>

#include <vector>
#include <queue>

int main(){
    int n;
    std::cin >> n;
    std::cin.ignore();
    std::vector<std::vector<int>> graph(n,std::vector<int>());
    for(int i=0;i<n;i++){
      std::string line;
      std::getline(std::cin,line);
      std::stringstream ss(line);
      std::string e;
      while(ss>>e){
        if(e=="*"){
          break;
        }
        graph[i].push_back(std::stoi(e));
      }
    }
    std::queue<int> queue;
    std::vector<int> result(n);
    for(int i=0;i<n;i++){
      if(graph[i].empty()){
        result[i]=0;
      }
      else{
        std::vector<bool> visited(n,false);
        queue.push(i);
        visited[i]=true;
        int count = 0;
        while(!queue.empty()){
          auto front = queue.front();
          queue.pop();
          for(int j=0;j<graph[front].size();j++){
            if(visited[graph[front][j]]==false){
              queue.push(graph[front][j]);
              count++;
              visited[graph[front][j]]=true;
            }
          }
        }
        result[i]=count;
      }
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