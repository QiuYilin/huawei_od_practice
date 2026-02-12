#include <iostream>

#include <vector>
#include <set>
//审题 并查集返回集合根
int find(std::vector<int> &father,int u){//找到最终的根
  if(father[u]==u){
    return u;
  }
  else{
    father[u]=find(father,father[u]);
    return father[u];
  }
}

void join(std::vector<int> &father,int u,int v){
  u = find(father,u);
  v = find(father,v);
  if(u==v){
    return;
  }
  else{
    // if(v<u){//疑问 这样做的好处是什么
    //     father[u]=v;
    // }
    // else{
    //     father[v]=u;
    // }
    father[v]=u;
  }
}
int main(){
  int node_n = 0;
  std::cin >> node_n;
  std::vector<std::vector<int>> grid(node_n,std::vector<int>(node_n,0));
  for(int i=0;i<node_n;i++){
    for(int j=0;j<node_n;j++){
      std::cin >> grid[i][j];
    }
  }
  std::vector<int> father(node_n,0);
  for(int i=0;i<node_n;i++){
    father[i]=i;
  }
  for(int i=0;i<node_n;i++){
    for(int j=0;j<i;j++){//REVIEW 双向需要都统计
      if(grid[i][j]==1){
        join(father,i,j);
      }
    }
  }
  std::set<int> roots;
  for(int i=0;i<node_n;i++){
    roots.insert(find(father,i));//REVIEW 判断根时要用find
  }
  std::cout << roots.size() << std::endl;
  return 0;
}