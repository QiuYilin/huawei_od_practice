#include <iostream>
#include <vector>
#include <string>
#include <deque>
using namespace std;

// 方向：上、下、左、右
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int main() {
    string operations;
    getline(cin, operations);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<char>> grid(n, vector<char>(m));
    int start_x = -1, start_y = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'H') {
                start_x = i;
                start_y = j;
            }
        }
    }
    
    //REVIEW 用deque来表示蛇身体
    deque<pair<int, int>> snake;
    snake.push_front({start_x, start_y});
    
    int dir = 2; // 初始方向：左（0:上,1:下,2:左,3:右）
    int length = 1;
    
    for (char op : operations) {
        if (op == ' ') continue;
        
        if (op == 'G') {
            // 当前蛇头位置
            int hx = snake.front().first;
            int hy = snake.front().second;
            
            // 计算下一步蛇头位置
            int nx = hx + dx[dir];
            int ny = hy + dy[dir];
            
            // 1. 边界碰撞检测
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                cout << length << endl;
                return 0;
            }
            
            // 2. 判断是否会吃到食物（用于后续碰撞判断）
            bool willEatFood = (grid[nx][ny] == 'F');
            
            // 3. 自身碰撞检测：允许覆盖“即将消失的蛇尾”
            pair<int, int> currentTail = snake.back(); // 当前蛇尾
            bool collision = false;
            
            for (const auto& seg : snake) {
                if (seg.first == nx && seg.second == ny) {
                    // 如果是蛇尾，并且不吃食物 → 合法（尾巴下一帧就没了）
                    if (!willEatFood && seg == currentTail) {
                        continue; // 不算碰撞
                    }
                    collision = true;
                    break;
                }
            }
            
            if (collision) {
                cout << length << endl;
                return 0;
            }
            
            // 4. 执行移动：新头加入 front
            snake.push_front({nx, ny});
            
            // 5. 处理食物
            if (willEatFood) {
                length++;
                grid[nx][ny] = 'E'; // 食物被吃掉，变为空地
            } else {
                // 没吃食物，移除蛇尾
                snake.pop_back();
            }
            
        } else {
            // 改变方向
            switch (op) {
                case 'U': dir = 0; break; // 上
                case 'D': dir = 1; break; // 下
                case 'L': dir = 2; break; // 左
                case 'R': dir = 3; break; // 右
            }
        }
    }
    
    // 所有操作完成，输出最终长度
    cout << length << endl;
    return 0;
}