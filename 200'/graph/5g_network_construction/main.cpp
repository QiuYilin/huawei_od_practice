#include <climits>
#include <iostream>
#include <vector>
// 题意 最小生成树模板题+有些边已经存在
// 已经连接的权值记0
// prim
int main() {
  int node_n = 0;
  std::cin >> node_n;
  int edge_n = 0;
  std::cin >> edge_n;
  if (edge_n < node_n - 1) {//REVIEW 考虑边不足的情况
    std::cout << -1 << std::endl;
    return 0;
  }
  std::vector<std::vector<int>> grid(node_n + 1,
                                     std::vector<int>(node_n + 1, 100));
  for (int i = 0; i < edge_n; i++) {
    int x = 0, y = 0, k = 0, exist = 0;
    std::cin >> x >> y >> k >> exist;
    if (exist == 0) {
      grid[x][y] = k;
      grid[y][x] = k;
    } else {
      grid[x][y] = 0;
      grid[y][x] = 0;
    }
  }
  std::vector<int> minDist(node_n + 1, 100);//REVIEW 表示节点邻接的最小的权值
  std::vector<bool> isInTree(node_n + 1, false);
  for (int i = 1; i <= node_n - 1; i++) {
    int min = INT_MAX;
    int cur = -1;
    for (int j = 1; j <= node_n; j++) {
      if (!isInTree[j] && minDist[j] < min) {
        cur = j;
        min = minDist[j];
      }
    }
    isInTree[cur] = true;
    for (int j = 1; j <= node_n; j++) {
      if (!isInTree[j] && grid[cur][j] < minDist[j]) {
        minDist[j] = grid[cur][j];
      }
    }
  }
  int result = 0;
  for (int i = 2; i <= node_n; i++) {
    result += minDist[i];
  }
  std::cout << result << std::endl;
  return 0;
}