#include <climits>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
// 岛屿问题 不同的标记策略 染色
// 变种条件 同时扩散 需要几天？bfs的结构性质

std::vector<std::vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int main() {
  std::vector<std::vector<std::string>> grid;
  std::string line;
  while (std::getline(std::cin, line)) {
    grid.push_back(std::vector<std::string>());
    std::stringstream ss(line);
    std::string state;
    while (ss >> state) {
      grid.back().push_back(state);
    }
  }
  std::queue<std::pair<int, int>> queue;
  int no_area_count = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == "YES") {
        queue.push({i, j});
      }
      else if(grid[i][j] == "NO"){
        no_area_count++;
      }
    }
  }
  int day = 0;
  while (!queue.empty()&&no_area_count>0) {
    int k = queue.size();

    for (int i = 0; i < k; i++) {
      auto top = queue.front();
      int x = top.first;
      int y = top.second;
      queue.pop();
      for (int i = 0; i < 4; i++) {
        auto new_x = x + dir[i][0];
        auto new_y = y + dir[i][1];
        if (new_x >= 0 && new_x < grid.size() && new_y >= 0 &&
            new_y < grid[0].size()) {
          if (grid[new_x][new_y] == "NO") {
              grid[new_x][new_y]="YES";
              queue.push({new_x, new_y});
              no_area_count--;
          }
        }
      }
    }
    day++;
  }
  if(no_area_count>0){
    std::cout << "-1" << std::endl;
  }
  else{
    std::cout << day << std::endl;
  }
  return 0;
}

// #include <iostream>
// #include <vector>
// using namespace std;

// /**
//  * 通用字符串拆分函数
//  * @param str 需要拆分的字符串
//  * @param delimiter 分隔符
//  * @return 拆分后的字符串数组
//  */
// vector<string> split(const string& str, const string& delimiter) {
//     vector<string> result;
//     size_t start = 0, end;
//     while ((end = str.find(delimiter, start)) != string::npos) {
//         result.push_back(str.substr(start, end - start));
//         start = end + delimiter.length();
//     }
//     result.push_back(str.substr(start));
//     return result;
// }

// int main() {
//     vector<vector<string>> grid; // 存储输入的网格数据
//     string line;

//     /**
//      * 读取输入数据，每行按空格拆分存入 grid
//      */
//     while (getline(cin, line) && !line.empty()) {
//         grid.push_back(split(line, " "));
//     }

//     int rows = grid.size(), cols = grid[0].size();
//     vector<vector<int>> queue; // 记录当前已改造的位置
//     int toConvert = 0; // 统计需要改造的位置数量

//     /**
//      * 遍历网格，初始化改造队列
//      *  - "YES" 代表已改造，加入队列
//      *  - "NO" 代表未改造，计数
//      */
//     //REVIEW 多源BFS 把起点都加入queue
//     for (int r = 0; r < rows; r++) {
//         for (int c = 0; c < cols; c++) {
//             if (grid[r][c] == "YES") queue.push_back({r, c});
//             else if (grid[r][c] == "NO") toConvert++;
//         }
//     }

//     /**
//      * 边界情况处理：
//      *  - 如果没有任何 "YES"，则无法改造，返回 -1
//      *  - 如果所有位置都是 "YES"，返回 0
//      */
//     if (queue.empty()) {
//         cout << -1 << endl;
//         return 0;
//     }
//     if (queue.size() == rows * cols) {
//         cout << 0 << endl;
//         return 0;
//     }

//     int days = 0; // 记录改造所需天数
//     vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //
//     上下左右四个方向

//     /**
//      * 广度优先遍历（BFS）模拟改造过程
//      *  - 逐天扩展，每天改造相邻的 "NO" 位置
//      *  - 直到所有 "NO" 改造完成，或无法继续改造
//      */
//     while (!queue.empty() && toConvert > 0) {
//         vector<vector<int>> newQueue; // 记录新改造的位置

//         for (auto& pos : queue) {
//             for (auto& dir : directions) {
//                 int newX = pos[0] + dir[0], newY = pos[1] + dir[1];

//                 if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
//                 grid[newX][newY] == "NO") {
//                     grid[newX][newY] = "YES";
//                     newQueue.push_back({newX, newY});
//                     toConvert--;
//                 }
//             }
//         }

//         days++;
//         queue = newQueue;
//     }

//     /**
//      * 输出最终结果：
//      *  - 如果所有 "NO" 成功改造，则返回天数
//      *  - 否则返回 -1
//      */
//     cout << (toConvert == 0 ? days : -1) << endl;
//     return 0;
// }
