#include <iostream>
#include <vector>
#include <queue>//REVIEW 优先级队列使用queue头文件

//题意：
int main(){
  int T=0,N=0;
  std::cin >> T >> N;//疑问 两座城市为什么有三个时间？ 起始终点也算城市
  int cost = 0;
  for(int i=0;i<N+1;i++){
    int tmp = 0;
    std::cin >> tmp;
    cost += tmp;
  }
  std::vector<std::pair<int,int>> incomes(N,{0,0});
  for(int i=0;i<N;i++){
    std::cin >> incomes[i].first;
    std::cin >> incomes[i].second;
  }
  std::priority_queue<std::pair<int,int>> queue;
  int actual_days = T - cost;
  for(int i=0;i<N;i++){
    int first_day_income = incomes[i].first;
    int decli = incomes[i].second;
    queue.push({first_day_income,decli});
  }
  int result = 0;
  while(actual_days>0){
    auto top=queue.top();
    queue.pop();
    result+=top.first;
    int actual_income=top.first-top.second;
    queue.push({actual_income,top.second});
    actual_days--;
  }
  std::cout << result << std::endl;
}

// 120 100 80 60 40 20 0
// 90 80 70 60

// 120 100 90 80 80 70

