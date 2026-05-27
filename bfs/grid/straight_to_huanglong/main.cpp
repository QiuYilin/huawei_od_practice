// #include <algorithm>
// #include <climits>
// #include <cmath>
// #include <iostream>
// #include <map>
// #include <queue>
// #include <sstream>
// #include <string>
// #include <utility>
// #include <vector>
// using namespace std;

// struct Point {
//   int x;
//   int y;
//   Point(int xx, int yy) : x(xx), y(yy) {}
// };

// vector<vector<int>> dir{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

// // 通用 切割函数 函数 将字符串str根据delimiter进行切割
// vector<string> split(const string& str, const string& delimiter) {
//   vector<string> result;
//   size_t start = 0;
//   size_t end = str.find(delimiter);
//   while (end != string::npos) {
//     result.push_back(str.substr(start, end - start));
//     start = end + delimiter.length();
//     end = str.find(delimiter, start);
//   }
//   // 添加最后一个部分
//   result.push_back(str.substr(start));
//   return result;
// }

// void bfs(int start_x, int start_y, const vector<vector<int>>& grid,
//          vector<vector<bool>> visited,int &path_count,int &min) {
//   queue<Point> queue;
//   if (grid[start_x][start_y] == -1) {
//     path_count=0;
//     min=0;
//     return;
//   }
//   min++;
//   queue.push({start_x,start_y});
//   visited[start_x][start_y]=true;
//   bool flag = false;
//   while(!queue.empty()){
//     auto front = queue.front();
//     queue.pop();
//     min++;
//     for(int i=0;i<dir.size();i++){
//         auto new_x = front.x+dir[i][0];
//         auto new_y = front.y+dir[i][1];
//         if(new_x>=0&&new_x<grid.size()
//            &&new_y>=0&&new_y<grid.size()
//            &&grid[new_x][new_y]!=-1&&
//            visited[new_x][new_y]==false){
//             queue.push({new_x,new_y});
//             visited[new_x][new_y]=true;
//             if(new_x==grid.size()-1&&new_y==grid.size()/2){
//                 flag=true;
//                 break;
//             }
//         }
//     }
//   }
// }

// // n大小 points哨兵位置
// vector<int> calShortestPath(int n, vector<Point>& points) {
//   vector<vector<int>> grid(n, vector<int>(n, 0));
//   for (int i = 0; i < points.size(); i++) {
//     grid[points[i].x][points[i].y] = -1;
//     for (int i = 0; i < dir.size(); i++) {
//       grid[points[i].x + dir[i][0]][points[i].y + dir[i][1]] = -1;
//     }
//   }
//   vector<vector<bool>> visited(n, vector<bool>(n, false));
//   int path_count =0;
//   int min=n*n+1;
//   bfs(0, n / 2, grid, visited,path_count,min);
// }

// int main() {
//   int n;
//   cin >> n;
//   // 吃掉换行
//   cin.ignore();
//   string line;
//   getline(cin, line);
//   vector<Point> points;
//   for (auto& s : split(line, " ")) {
//     vector<string> rowCol = split(s, ",");
//     points.push_back({stoi(rowCol[0]), stoi(rowCol[1])});
//   }

//   vector<int> res = calShortestPath(n, points);
//   cout << res[0] << " " << res[1];
//   return 0;
// }

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>
#include<climits>
#include <queue>
using namespace std;



struct Point {
   int x;
   int y;
   Point(int xx, int yy) : x(xx), y(yy) {}
};

//REVIEW BFS 特性 如果第一次到达一定是最短路径 方案数=上一个点

// 通用 切割函数 函数 将字符串str根据delimiter进行切割
vector<string> split(const string& str, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // 添加最后一个部分
    result.push_back(str.substr(start));
    return result;
}


// n大小 points哨兵位置
vector<int> calShortestPath(int n, vector<Point>& points) {
    vector<vector<int>> grid(n, vector<int>(n, 0));
    // 标记不可达位置
    for (Point& point : points) {
        int x = point.x;
        int y = point.y;
        for (int i = x - 1; i <=  x + 1; i++) {
            for (int j = y -1; j <= y + 1; j++) {
                if (i < 0 || i >= n || j < 0 || j >=n) {
                    continue;
                }
                grid[i][j] = -1;
            }
        }
    } 
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    int sx = 0, sy = n / 2;
    int ex = n - 1, ey = n / 2;
    // 特殊情况判断
    if (grid[sx][sy] == -1 || grid[ex][ey] == -1) {
        return {0, 0};
    }

    
    // dist 记录最少节点数，-1 表示未访问
    vector<vector<int>> dist(n, vector<int>(n, -1));
    // distNum 最少节点数到达次数方案数
    vector<vector<int>> distNum(n, vector<int>(n, 0));
    queue<pair<int, int>> q;
    q.push({sx, sy});
    dist[sx][sy] = 1;
    distNum[sx][sy] = 1;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int x = p.first, y = p.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            // 越界或被监控
            if (nx < 0 || nx >= n || ny < 0 || ny >= n || grid[nx][ny] == -1) {
                continue;
            }
            // 初次访问
            if (dist[nx][ny] == -1) {
                // 步数+1
                dist[nx][ny] = dist[x][y]  + 1;
                // 数量相同
               distNum[nx][ny] = distNum[x][y];
               q.push({nx, ny});
            } else if (dist[x][y] + 1 == dist[nx][ny]) {
                 distNum[nx][ny] += distNum[x][y];
            }
        }
    }
    // 不可达
    if (dist[ex][ey] == -1) {
        return {0, 0};
    }
    return {distNum[ex][ey], dist[ex][ey]};
}

int main() {
    int n;
    cin >> n;
    // 吃掉换行
    cin.ignore();
    string line;
    getline(cin, line);
    vector<Point> points;
    for (auto &s : split(line, " ")) {
        vector<string> rowCol = split(s, ",");
        points.push_back({stoi(rowCol[0]), stoi(rowCol[1])});
    }

    vector<int> res = calShortestPath(n, points);
    cout << res[0] << " " << res[1];
    return 0;
}



