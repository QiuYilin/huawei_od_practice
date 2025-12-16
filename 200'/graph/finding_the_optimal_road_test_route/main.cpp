#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int main() {
    int row, col;
    cin >> row >> col;
    
    // 网格信号值（节点权重）
    vector<vector<int>> graph(row, vector<int>(col, 0));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> graph[i][j];
        }
    }
    
    int n = row * col;  // 总节点数
    int start = 0;      // 起点 (0,0)
    int end = n - 1;    // 终点 (row-1,col-1)
    
    // dist数组：存储从源点到每个节点的最大瓶颈值
    vector<int> dist(n, -1);
    
    // visited数组：记录顶点是否被访问过
    vector<bool> visited(n, false);
    
    // 方向数组：上下左右
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    dist[start] = graph[0][0];  // 起始点的最大瓶颈值就是自身值

    for (int i = 0; i < n; i++) {  // 主循环：遍历所有节点
        
        int maxVal = -1;
        int cur = -1;
        
        // 1、选择距离源点最近（瓶颈值最大）且未访问过的节点
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && dist[v] > maxVal) {  // 注意：这里是 >，寻找最大值
                maxVal = dist[v];
                cur = v;
            }
        }
        
        // 如果找不到有效节点，说明剩下的节点都不可达
        if (cur == -1 || dist[cur] == -1) break;
        
        visited[cur] = true;  // 2、标记该节点已被访问
        
        // 如果是终点，可以提前结束
        if (cur == end) {
            break;
        }
        
        // 3、更新非访问节点到源点的最大瓶颈值
        int x = cur / col;
        int y = cur % col;
        
        for (int d = 0; d < 4; ++d) {
            int nextX = x + dirs[d][0];
            int nextY = y + dirs[d][1];
            
            // 检查边界
            if (nextX < 0 || nextX >= row || nextY < 0 || nextY >= col) {
                continue;
            }
            
            int neighbor = nextX * col + nextY;
            
            // 如果邻居节点未被访问
            if (!visited[neighbor]) {
                // 计算从当前节点到邻居节点的路径瓶颈值
                int newDist = min(dist[cur], graph[nextX][nextY]);
                
                // 如果找到更大的瓶颈值，更新
                if (newDist > dist[neighbor]) {
                    dist[neighbor] = newDist;
                }
            }
        }
    }

    if (dist[end] == -1) cout << 0 << endl;  // 不能到达终点
    else cout << dist[end] << endl;          // 到达终点的最大瓶颈值

    return 0;
}