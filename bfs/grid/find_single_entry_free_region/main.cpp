// #include <iostream>
// #include <queue>
// #include <string>
// #include <vector>
// std::vector<std::vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

// int bfs(int x, int y, std::vector<std::vector<std::string>> grid,
//         std::vector<std::vector<bool>>& visited) {
//   int area = 0;
//   std::queue<std::pair<int, int>> queue;
//   queue.push({x, y});
//   area++;
//   visited[x][y] = true;
//   while (!queue.empty()) {
//     auto front = queue.front();
//     queue.pop();
//     for (int i = 0; i < 4; i++) {
//       auto new_x = front.first + dir[i][0];
//       auto new_y = front.second + dir[i][1];
//       if (new_x >= 0 && new_x < grid.size() && new_y >= 0 &&
//           new_y < grid[0].size() && visited[new_x][new_y] == false &&
//           grid[new_x][new_y] == "O") {
//         if (new_x == 0 || new_x == grid.size()-1 || new_y == 0 ||
//             new_y == grid[0].size()-1) {
//           return -1;
//         } else {
//           area++;
//           queue.push({new_x, new_y});
//           visited[new_x][new_y] = true;
//         }
//       }
//     }
//   }
//   return area;
// }

// int main() {
//   int m, n;
//   std::cin >> m >> n;
//   std::vector<std::vector<std::string>> grid(m, std::vector<std::string>(n));
//   std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
//   for (int i = 0; i < m; i++) {
//     for (int j = 0; j < n; j++) {
//       std::cin >> grid[i][j];
//     }
//   }
//   std::vector<int> result(3);
//   result[0] = 0;
//   for (int i = 0; i < n - 1; i++) {
//     if (visited[0][i] == false && grid[0][i] == "O") {
//       auto area = bfs(0, i, grid, visited);
//       if (area > result[0]) {
//         result[0] = area;
//         result[1] = 0;
//         result[2] = i;
//       }
//     }
//   }
//   for (int i = 0; i < m - 1; i++) {
//     if (visited[i][n - 1] == false && grid[i][n - 1] == "O") {
//       auto area = bfs(i, n - 1, grid, visited);
//       if (area > result[0]) {
//         result[0] = area;
//         result[1] = i;
//         result[2] = n-1;
//       }
//     }
//   }
//   for (int i = n - 1; i > 0; i--) {
//     if (visited[m - 1][i] == false && grid[m - 1][i] == "O") {
//       auto area = bfs(m - 1, i, grid, visited);
//       if (area > result[0]) {
//         result[0] = area;
//         result[1] = m-1;
//         result[2] = i;
//       }
//     }
//   }
//   for (int i = m - 2; i > 0; i--) {
//     if (visited[i][0] == false && grid[i][0] == "O") {
//       auto area = bfs(i, 0, grid, visited);
//       if (area > result[0]) {
//         result[0] = area;
//         result[1] = i;
//         result[2] = 0;
//       }
//     }
//   }
//   if (result[0] == -1) {
//     std::cout << "NULL" << std::endl;
//   } else {
//     std::cout << result[1] << " " << result[2] << " " << result[0] << std::endl;
//   }
//   return 0;
// }

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

struct Region {
    int entrance_x;
    int entrance_y;
    int size;
};

// BFS返回是否单入口、区域大小、入口坐标
pair<int, int> bfs(int x, int y, vector<vector<string>>& grid,
                   vector<vector<bool>>& visited, int m, int n) {
    int area = 0;
    int entrance_count = 0;
    int entrance_x = -1, entrance_y = -1;
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    
    // 检查起始点是否为边界
    if (x == 0 || x == m-1 || y == 0 || y == n-1) {
        entrance_count++;
        entrance_x = x;
        entrance_y = y;
    }
    
    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();
        area++;
        
        for (auto& d : dir) {
            int nx = cx + d[0];
            int ny = cy + d[1];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                !visited[nx][ny] && grid[nx][ny] == "O") {
                
                // 检查是否边界
                if (nx == 0 || nx == m-1 || ny == 0 || ny == n-1) {
                    entrance_count++;
                    entrance_x = nx;
                    entrance_y = ny;
                }
                
                q.push({nx, ny});
                visited[nx][ny] = true;
            }
        }
    }
    
    // 只有恰好一个入口时才返回面积，否则返回0
    if (entrance_count == 1) {
        return {area, entrance_x * n + entrance_y}; // 用编码存储入口坐标
    } else {
        return {0, -1};
    }
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<string>> grid(m, vector<string>(n));
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    vector<Region> valid_regions;
    
    // 从边界点开始遍历
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // 只从边界点开始
            if ((i == 0 || i == m-1 || j == 0 || j == n-1) && 
                !visited[i][j] && grid[i][j] == "O") {//REVIEW 遍历边界的方式
                auto [size, entrance_code] = bfs(i, j, grid, visited, m, n);
                if (size > 0) {
                    int ex = entrance_code / n;
                    int ey = entrance_code % n;
                    valid_regions.push_back({ex, ey, size});
                }
            }
        }
    }
    
    if (valid_regions.empty()) {
        cout << "NULL" << endl;
        return 0;
    }
    
    // 找到最大区域大小
    sort(valid_regions.begin(), valid_regions.end(), 
         [](const Region& a, const Region& b) {
             return a.size > b.size;
         });
    
    int max_size = valid_regions[0].size;
    vector<Region> max_regions;
    for (auto& r : valid_regions) {
        if (r.size == max_size) {
            max_regions.push_back(r);
        } else {
            break;
        }
    }
    
    if (max_regions.size() == 1) {
        cout << max_regions[0].entrance_x << " " 
             << max_regions[0].entrance_y << " " 
             << max_regions[0].size << endl;
    } else {
        // 多个最大区域，只输出大小
        cout << max_size << endl;
    }
    
    return 0;
}