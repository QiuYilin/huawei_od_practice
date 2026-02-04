#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

// 0 1 2 3 4 5 6 7
// √
//   √            √
//     √       √

// 审题 多源BFS
int main() {
  int n, k;
  std::cin >> n >> k;
  std::vector<bool> started(n, false);
  std::map<int, std::vector<int>>
      starts;  // REVIEW map是树是基于比较的查找 所以是按键排序的
  int time = INT_MAX;
  for (int i = 0; i < k; i++) {
    int t, p;
    std::cin >> t >> p;
    starts[t].push_back(p);
    time = std::min(t, time);
  }  // REVIEW 可以用min_element简化
  std::queue<int> queue;
  auto first_engs = starts[time];
  int count = n;  // REVIEW count会变化 n不会
  for (auto e : first_engs) {
    count--;
    queue.push(e);
    started[e] = true;
  }

  if (count == 0) {
    std::vector<int> last_engines;
    while (!queue.empty()) {
      last_engines.push_back(queue.front());
      queue.pop();
    }
    std::sort(last_engines.begin(), last_engines.end());

    std::cout << last_engines.size() << std::endl;
    for (size_t i = 0; i < last_engines.size(); i++) {
      if (i != 0) std::cout << " ";
      std::cout << last_engines[i];
    }
    std::cout << std::endl;
    return 0;  // 直接结束程序
  }
  // 疑问 时刻在何时+1
  //while (!queue.empty() && count > 0) {
  while (count > 0) {
    // 此时queue中的发动机都是上个时刻启动过的
    int level_n = queue.size();
    time++;
    std::vector<int> level;
    // 关联启动
    for (int i = 0; i < level_n; i++) {
      auto front = queue.front();
      queue.pop();
      int left = (front - 1 + n) % n;  //REVIEW 环形数组的表达法
      int right = (front + 1) % n;
      if (started[left] == false) {
        queue.push(left);
        started[left] = true;
        level.push_back(left);
        count--;
      }
      if (started[right] == false) {
        queue.push(right);
        started[right] = true;
        level.push_back(right);
        count--;
      }
    }
    // 当前时刻有发动机要启动
    for (auto e : starts[time]) {
      if (started[e] == false) {
        queue.push(e);
        started[e] = true;
        count--;
        level.push_back(e);
      }
    }
    if (count == 0) {
      std::sort(level.begin(),level.end());//REVIEW 答案要求有序
      std::cout << level.size() << " " << std::endl;
      for (int i = 0; i < level.size(); i++) {
        if (i != 0) {
          std::cout << " ";
        }
        std::cout << level[i];
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
