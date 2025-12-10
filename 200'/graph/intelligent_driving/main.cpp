#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <sstream>
#include <string>

using namespace std;

//REVIEW 

// 方向数组
const int offsets[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

//REVIEW 信息过于复杂 可以用类
struct Node {
    int x, y;       // 位置坐标
    int init;       // 到达此位置所需的最少初始油量
    int remain;     // 到达此位置时剩余可用油量
    bool flag;      // 到达此位置前有没有加过油
    
    Node(int _x = 0, int _y = 0) : x(_x), y(_y), init(0), remain(0), flag(false) {}
};

int bfs(const vector<vector<int>>& matrix, int m, int n) {
    // 起点或终点是障碍物
    if (matrix[0][0] == 0 || matrix[m-1][n-1] == 0) {
        return -1;
    }
    
    queue<Node> q;
    Node src(0, 0);
    
    // 初始化起点
    if (matrix[0][0] == -1) {
        src.init = 0;
        src.remain = 100;
        src.flag = true;
    } else {
        src.init = matrix[0][0];
        src.remain = 0;
        src.flag = false;
    }
    
    q.push(src);
    
    // REVIEW dist_init记录最小初始油量
    vector<vector<int>> dist_init(m, vector<int>(n, INT_MAX));
    // REVIEW dist_remain记录对应状态的最大剩余油量
    vector<vector<int>> dist_remain(m, vector<int>(n, 0));
    
    dist_init[0][0] = src.init;
    dist_remain[0][0] = src.remain;
    
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int newX = cur.x + offsets[i][0];
            int newY = cur.y + offsets[i][1];
            
            // 越界检查
            if (newX < 0 || newX >= m || newY < 0 || newY >= n || matrix[newX][newY] == 0) {
                continue;
            }
            
            int init = cur.init;
            int remain = cur.remain;
            bool flag = cur.flag;
            
            // 处理当前格子
            if (matrix[newX][newY] == -1) {
                // 加油站：加满油
                remain = 100;
                flag = true;
            } else {
                // 普通格子：消耗油量
                remain -= matrix[newX][newY];
            }
            
            // 油量不足的处理
            if (remain < 0) {
                if (flag) {
                    // 已经加过油，不能再补充初始油量
                    continue;
                } else {
                    // 补充初始油量
                    init -= remain;  // remain是负数，减负等于加正
                    remain = 0;
                }
            }
            
            // 初始油量不能超过100
            if (init > 100) {
                continue;
            }
            
            // 更新条件：更小的初始油量，或相同初始油量但更大的剩余油量
            if (init < dist_init[newX][newY] || 
                (init == dist_init[newX][newY] && remain > dist_remain[newX][newY])) {
                dist_init[newX][newY] = init;
                dist_remain[newX][newY] = remain;
                
                Node nxt(newX, newY);
                nxt.init = init;
                nxt.remain = remain;
                nxt.flag = flag;
                
                q.push(nxt);
            }
        }
    }
    
    if (dist_init[m-1][n-1] == INT_MAX) {
        return -1;
    } else {
        return dist_init[m-1][n-1];
    }
}

int main() {
    string line;
    
    // 读取M,N
    getline(cin, line);
    stringstream ss(line);
    string val;
    getline(ss, val, ',');
    int m = stoi(val);
    getline(ss, val, ',');
    int n = stoi(val);
    
    // 读取地图
    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        getline(cin, line);
        stringstream ss2(line);
        for (int j = 0; j < n; j++) {
            getline(ss2, val, ',');
            matrix[i][j] = stoi(val);
        }
    }
    
    cout << bfs(matrix, m, n) << endl;
    
    return 0;
}