#include <iostream>

#include <vector>
#include <list>
#include <queue>

#include <algorithm>
//城市安全度的最大最小值
//安全度K
//图论 0~N-1 存在路径 所有路径？
//求出所有路径 再取最大最小值？ 复杂度分析 为什么用二分
bool isValid(std::vector<std::list<int>> graph,int k,int mid,std::vector<int> safety){
  //REVIEW 步数可以用visited数组表示
  if(safety[0]<mid || safety[graph.size()-1]<mid){
    return false;
  }//REVIEW 特殊情况优先处理比较省事
  std::queue<int> queue;
  std::vector<bool> visited(graph.size(),false);
  queue.push(0);
  visited[0]=true;
  int count = 1;
  while(!queue.empty()){
    int size = queue.size();
    if(count>k){
      return false;
    }
    for(int i=0;i<size;i++){
      auto front = queue.front();
      queue.pop();
      if(front==graph.size()-1){
          return true;//review 判断在这
      }
      for(auto l:graph[front]){
        if(visited[l]==false&&safety[l]>=mid){
          queue.push(l);
          visited[l]=true;
        }
      }
    }
    count++;
  }
  return false;
}

int main(){
  int n,k;
  std::cin >> n >> k;
  std::vector<int> safety(n);

  for(int i=0;i<n;i++){
    std::cin >> safety[i];
  }

  std::vector<std::list<int>> graph(n);

  int m =0;
  std::cin >> m;
  for(int i=0;i<m;i++){
    int prev,next;
    std::cin >> prev >> next;
    graph[prev].push_back(next);
    graph[next].push_back(prev);//疑问 双向的这么表示？
  }

  int l=0;
  int r=*std::max_element(safety.begin(),safety.end());

  int result = -1;

  while(l<=r){
    int mid = l+(r-l)/2;
    if(isValid(graph,k,mid,safety)){
      result = mid;
      l=mid+1;
    }
    else{
      r=mid-1;
    }
  }
  std::cout << result << std::endl;
  return 0;
}