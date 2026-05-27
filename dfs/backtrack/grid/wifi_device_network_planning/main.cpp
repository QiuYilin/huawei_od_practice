// 输入网格
//     ↓
// 给每个 '.' 空地编号 (0 ~ to t-1)
//     ↓
// buildAP(): 枚举所有可放置AP的位置（每个 '.' 格子）
//    每个AP记录: dots(覆盖的空地编号) + cells(占用的格子坐标)
//     ↓
// 建立反向索引 pointToAP[空地] = 能覆盖它的AP列表
//     ↓
// dfs(0) 回溯搜索:
//     ├── 剪枝: usedCnt >= ans 则返回
//     ├── 全部覆盖? → 更新ans
//     ├── 下界剪枝: usedCnt + ceil(剩余/9) >= ans 则返回
//     ├── selectPoint(): 选最难覆盖的空地（可用AP最少）
//     ├── 收集候选AP并排序（优先覆盖多的）
//     └── 对每个候选AP: 放置 → 递归 → 回溯
//     ↓
// 返回 ans (或 -1 表示无解)

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cstring>
#include<climits>
#include<map>
using namespace std;

// ==================== 常量定义 ====================
const int MAXN = 50;    // 网格最大尺寸（题目要求不超过50）
const int MAXP = 2500;  // 最大空地数量（50×50=2500）

// ==================== 全局变量 ====================
int n, m;               // 网格的行数(n)、列数(m)
string g[MAXN];         // 存储原始网格，g[i][j] 表示第i行第j列的字符

int id[MAXN][MAXN];     // 给每个 '.' 空地分配唯一编号，-1表示不是空地
int tot = 0;            // 空地总数

// AP结构体：描述一个候选的AP放置方案
struct AP {
    vector<int> dots;                 // 这个AP能覆盖哪些空地的编号
    vector<pair<int,int>> cells;      // 这个AP的3x3区域会占用哪些格子（坐标对）
};

vector<AP> apList;      // 所有候选AP的列表（每个 '.' 格子都可以作为AP中心）

// pointToAP[空地编号] = 能覆盖该空地的所有AP在apList中的索引列表
vector<vector<int>> pointToAP;

bool covered[MAXP];     // covered[i] = true 表示编号为i的空地已经被覆盖
bool used[MAXN][MAXN];  // used[i][j] = true 表示格子(i,j)已被某个AP的3x3区域占用

int ans;                // 最终答案：最少需要多少个AP

// 3x3区域的偏移量（包括自身及周围8个方向）
int dx[9] = {-1,-1,-1, 0,0,0, 1,1,1};
int dy[9] = {-1,0,1, -1,0,1, -1,0,1};

// ==================== 辅助函数 ====================

// 判断坐标(x,y)是否在网格范围内
bool in(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

// ==================== 预处理：构建所有候选AP ====================
// 遍历每个格子，如果是空地('.')，则尝试以它为中心放置一个AP
// 记录这个AP会覆盖哪些空地(dots)和占用哪些格子(cells)
void buildAP() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] != '.') continue;  // 只能在空地放AP
            
            AP ap;  // 创建一个新的AP对象
            
            // 遍历3x3区域的9个格子
            for (int k = 0; k < 9; k++) {
                int x = i + dx[k], y = j + dy[k];
                if (!in(x, y)) continue;   // 超出边界则跳过
                
                ap.cells.push_back({x, y}); // 记录这个格子被AP占用
                
                if (g[x][y] == '.') {
                    // 如果该格子是空地，则记录这个空地可以被此AP覆盖
                    ap.dots.push_back(id[x][y]);
                }
            }
            
            apList.push_back(ap);  // 将当前AP加入候选列表
        }
    }
}

// ==================== 统计剩余未覆盖的空地数量 ====================
int remain() {
    int cnt = 0;
    for (int i = 0; i < tot; i++) {
        if (!covered[i]) cnt++;
    }
    return cnt;
}

// ==================== 启发式选择：找出最难覆盖的空地 ====================
// 遍历所有未被覆盖的空地，统计每个空地当前有多少个可用的AP能覆盖它
// 返回可用AP数量最少的空地编号（最难覆盖的）
// 如果某个空地没有可用AP，返回-1（表示无解）
int selectPoint() {
    int best = -1, bestCnt = 1e9;
    
    for (int i = 0; i < tot; i++) {
        if (covered[i]) continue;  // 已覆盖的空地跳过
        
        int cnt = 0;  // 统计能覆盖空地i的、且当前可用的AP数量
        
        // 遍历所有能覆盖空地i的AP
        for (int ap : pointToAP[i]) {
            bool ok = true;
            // 检查这个AP的3x3区域是否与已放置的AP冲突
            for (auto &c : apList[ap].cells) {
                if (used[c.first][c.second]) {
                    ok = false;  // 有格子已被占用，此AP不可用
                    break;
                }
            }
            if (ok) cnt++;
        }
        
        // 如果没有可用AP能覆盖这个空地，则无解
        if (cnt == 0) return -1;
        
        // 选择可用AP数量最少的空地（最难覆盖的优先处理）
        if (cnt < bestCnt) {
            bestCnt = cnt;
            best = i;
        }
    }
    
    return best;
}

// ==================== DFS回溯搜索 ====================
// usedCnt: 当前已放置的AP数量
void dfs(int usedCnt) {
    // 剪枝1：如果当前AP数量已经不小于已知最优解，则无需继续
    if (usedCnt >= ans) return;
    
    // 检查是否所有空地都已被覆盖
    bool all = true;
    for (int i = 0; i < tot; i++) {
        if (!covered[i]) {
            all = false;
            break;
        }
    }
    
    if (all) {
        // 所有空地都覆盖了，更新最优解
        ans = usedCnt;
        return;
    }
    
    // 剪枝2：下界剪枝
    // 每个AP最多覆盖9个空地，理论上至少还需要 ceil(剩余空地/9) 个AP
    int lb = (remain() + 8) / 9;  // 向上取整
    if (usedCnt + lb >= ans) return;
    
    // 选择最难覆盖的空地（可用AP最少的）
    int p = selectPoint();
    if (p == -1) return;  // 无解
    
    // 收集所有能覆盖空地p且当前可用的AP
    vector<int> cand;
    for (int ap : pointToAP[p]) {
        bool ok = true;
        // 检查该AP的3x3区域是否与已放置AP冲突
        for (auto &c : apList[ap].cells) {
            if (used[c.first][c.second]) {
                ok = false;
                break;
            }
        }
        if (ok) cand.push_back(ap);
    }
    
    // 启发式排序：优先尝试能覆盖更多空地的AP（贪心策略）
    sort(cand.begin(), cand.end(),
         [&](int a, int b) {
             return apList[a].dots.size() > apList[b].dots.size();
         });
    
    // 遍历每个候选AP进行尝试
    for (int ap : cand) {
        vector<pair<int,int>> oldCells;  // 记录本次新增的占用格子
        vector<int> oldDots;             // 记录本次新覆盖的空地
        
        // 放置AP：标记占用的格子
        for (auto &c : apList[ap].cells) {
            if (!used[c.first][c.second]) {
                used[c.first][c.second] = true;
                oldCells.push_back(c);
            }
        }
        
        // 放置AP：标记新覆盖的空地
        for (int d : apList[ap].dots) {
            if (!covered[d]) {
                covered[d] = true;
                oldDots.push_back(d);
            }
        }
        
        // 递归搜索
        dfs(usedCnt + 1);
        
        // 回溯：恢复现场
        for (auto &c : oldCells) {
            used[c.first][c.second] = false;
        }
        for (int d : oldDots) {
            covered[d] = false;
        }
    }
}

// ==================== 主求解函数 ====================
// 输入：grid - 原始网格（vector<string>）
// 输出：最少AP数量，无法覆盖则返回-1
int solve(vector<string>& grid) {
    // 1. 初始化全局变量
    n = grid.size();
    m = grid[0].size();
    
    // 将grid复制到全局字符数组g中
    for (int i = 0; i < n; i++) {
        g[i] = grid[i];
    }
    
    // 重置数组
    memset(id, -1, sizeof(id));
    memset(covered, 0, sizeof(covered));
    memset(used, 0, sizeof(used));
    
    tot = 0;
    apList.clear();
    pointToAP.clear();
    
    // 2. 给所有空地('.')分配唯一编号
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '.') {
                id[i][j] = tot++;
            }
        }
    }
    
    // 如果没有空地，直接返回0
    if (tot == 0) return 0;
    
    // 3. 构建候选AP列表
    pointToAP.resize(tot);
    buildAP();  // 生成 apList
    
    // 4. 建立反向索引：空地编号 -> 能覆盖它的AP列表
    for (int i = 0; i < (int)apList.size(); i++) {
        for (int d : apList[i].dots) {
            pointToAP[d].push_back(i);
        }
    }
    
    // 5. DFS搜索最优解
    ans = INT_MAX;
    dfs(0);
    
    // 6. 返回结果（如果ans未被更新，说明无解，返回-1）
    return (ans == INT_MAX ? -1 : ans);
}

// ==================== 主函数 ====================
int main() {
    // 读取输入
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    
    // 调用求解函数并输出结果
    cout << solve(grid) << endl;
    
    return 0;
}