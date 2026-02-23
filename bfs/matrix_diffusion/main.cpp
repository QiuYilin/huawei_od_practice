#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
int main() {
  std::string input;
  std::cin >> input;
  std::stringstream ss(input);
  std::vector<int> input_v;
  std::string e;
  while (std::getline(ss, e, ',')) {
    input_v.push_back(std::stoi(e));
  }
  int n = input_v[0];
  int m = input_v[1];
  std::vector<std::pair<int, int>> start_coors;
  start_coors.push_back({input_v[2], input_v[3]});
  start_coors.push_back({input_v[4], input_v[5]});
  std::vector<std::vector<int>> grid(n, std::vector<int>(m, 0));
  int time = -1;
  std::queue<std::pair<int, int>> queue;
  for (int i = 0; i < start_coors.size(); i++) {
    queue.push(start_coors[i]);
    grid[start_coors[i].first][start_coors[i].second] = 1;
  }
  std::vector<std::vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
  while (!queue.empty()) {//判断条件用queue.empty()还是count是有区别的  count=0比queue.empty()先发生
    time++;
    int k = queue.size();
    for (int i = 0; i < k; i++) {//
      auto front = queue.front();
      queue.pop();
      for (int j = 0; j < 4; j++) {//每层添加一次就是一次
        auto new_x = front.first + dir[j][0];
        auto new_y = front.second + dir[j][1];
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m &&
            grid[new_x][new_y] == 0) {
          grid[new_x][new_y] = 1;
          queue.push({new_x, new_y});
        }
      }
    }
  }

  std::cout << time<< std::endl;
          
  return 0;
}