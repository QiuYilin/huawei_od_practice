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

//kruskas方式

// #include <algorithm>
// #include <functional>
// #include <iostream>
// #include <numeric>
// #include <vector>

// struct Edge {
//   int l = 0;
//   int r = 0;
//   int v = 0;
// };

// int main() {
//   int k, e;
//   std::cin >> k >> e;
//   if (e < k - 1) {
//     std::cout << "-1" << std::endl;
//     return 0;
//   }
//   std::vector<Edge> edges;
//   for (int i = 0; i < e; i++) {
//     int l, r, v, b;
//     std::cin >> l >> r >> v >> b;
//     if (b == 1) {
//       edges.push_back({l, r, 0});
//     } else {
//       edges.push_back({l, r, v});
//     }
//   }
//   std::sort(edges.begin(), edges.end(),
//             [](Edge a, Edge b) { return a.v < b.v ? true : false; });

//   int count = 0;

//   std::vector<int> father(k+1);//REVIEW 节点从1开始

//   std::iota(father.begin(), father.end(), 0);//REVIEW 节点从1开始

//   std::function<int(int)> find = [&](int u) -> int {
//     if (father[u] == u) {
//       return u;
//     } else {
//       father[u] = find(father[u]);
//       return father[u];
//     }
//   };  
//   int result = 0;
//   for (int i = 0; i < e; i++) {
//     if (count == k-1) {
//       break;
//     }
//     int l=edges[i].l;
//     int r=edges[i].r;
//     auto l_f=find(l);
//     auto r_f=find(r);
//     if(l_f!=r_f){//REVIEW isSame 用了find
//       count++;
//       result +=edges[i].v;
//       father[l_f]=r_f;
//     }
//   }
//   if(count != k-1){
//     std::cout << -1 << std::endl;
//   }
//   else{
//     std::cout << result << std::endl;
//   }
//   return 0;
// }