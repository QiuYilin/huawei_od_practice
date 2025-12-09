#include <iostream>

#include <unordered_map>
#include <vector>

#include <algorithm>
//审题 拓扑排序 REVIEW 尾节点不需要分层 统计next节点是否为空即可
int main(){
  int edge_n = 0;
  std::cin >> edge_n;
  std::unordered_map<int,std::vector<int>> map;
  std::unordered_map<int,int> indgree;
  for(int i=0;i<edge_n;i++){
    int prev=0,next=0;
    std::cin >> prev >> next;
    map[prev].push_back(next);
    indgree[next]++;
    indgree[prev]+=0;
  }
  int true_node_n = indgree.size();
  std::vector<int> tmp;
  std::vector<int> start;
  std::vector<int> end;
  int node_n = 0;
  for(auto n:indgree){
    int node = n.first;
    int in_cnt = n.second;
    if(in_cnt==0){
      tmp.push_back(node);
    }
  }
  start = tmp;
  if(start.empty()){
    std::cout << "-1";
    return 0;
  }
  std::vector<int> level;
  std::vector<int> ends;
  while(!tmp.empty()){//疑问  这种写法是怎么写的
    level = tmp;
    tmp.clear();
    for(int i=0;i<level.size();i++){
      node_n++;
      auto nexts = map[level[i]];
      if(nexts.empty()){
        ends.push_back(level[i]);
      }
      for(int j=0;j<nexts.size();j++){
        indgree[nexts[j]]--;
        if(indgree[nexts[j]]==0){
          tmp.push_back(nexts[j]);
        }
      }
    }
  }
  if(node_n!=true_node_n){
    std::cout << "-1" <<std::endl;
  }
  else{
    std::sort(start.begin(),start.end());
    std::sort(ends.begin(),ends.end());
    for(int i=0;i<start.size();i++){
      if(i>0){
        std::cout << " ";
      }
      std::cout << start[i];
    }
    for(int i=0;i<ends.size();i++){
      std::cout << " ";
      std::cout << ends[i];
    }
    std::cout << std::endl;
  }
  return 0;
}