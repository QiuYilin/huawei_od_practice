#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
//审题 多源BFS
int main(){
    int n,k;
    std::cin >> n >> k;
    std::vector<bool> started(n,false);
    std::unordered_map<int,std::vector<int>> starts;//疑问 如何保持索引顺序
    int time = INT_MAX;
    for(int i=0;i<k;i++){
        int t,p;
        std::cin >> t >> p;
        starts[t].push_back(p);
        time = std::min(t,time);
    }
    //疑问 map能排序吗
    // std::sort(starts.begin(),starts.end(),[](std::pair<int,std::vector<int>> a,std::pair<int,std::vector<int>> b){
    //     return a.first<b.first;
    // });
    std::queue<int> queue;
    auto first_engs = starts[time];
    //queue.push(first_engs.begin(),first_engs.end());疑问有没有便捷方法
    for(auto e:first_engs){
      n--;
      queue.push(e);
      started[e]=true;
    }
    while(!queue.empty()&&n>0){
      int level_n = queue.size();
      time++;
      auto level = queue;
      for(int i=0;i<level_n;i++){
        auto front = queue.front();
        queue.pop();
        if(front-1>=0&&started[front-1]==false){
          queue.push(front-1);
          started[front-1]=true;
          n--;
        }
        if(front+1<n&&started[front+1]==false){
          queue.push(front+1);
          started[front+1]=true;
          n--;
        }
      }
      for(auto e:starts[time]){
        if(started[e]==false){
          queue.push(e);
          started[e]=true;
          n--;
          level.push(e);
        }
      }
      if(n==0){
         std::cout << time;
         while(!level.empty()){
            std::cout << level.front();
            level.pop();
         }
         std::cout << std::endl;
      }
    }

    return 0;
}