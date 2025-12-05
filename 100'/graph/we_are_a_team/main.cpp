#include <iostream>
#include <vector>
// 审题 收到消息之前是team还是后面是team也判断为team
int find(std::vector<int>& father, int u) {
  if (u == father[u]) {
    return u;
  } else {
    father[u] = find(father, father[u]);
    return father[u];
  }
}

bool isSame(std::vector<int>& father, int u, int v) {
  u = find(father, u);
  v = find(father, v);
  if (u == v) {
    return true;
  } else {
    return false;
  }
}

void join(std::vector<int>& father, int u, int v) {
  u = find(father, u);
  v = find(father, v);
  if (u == v) {
    return;
  } else {
    father[v] = u;
    return;
  }
}

int main() {
  int n = 0, m = 0;
  std::cin >> n >> m;
  if(n<1||n>=100000||m<1||m>=100000){//REVIEW 范围是[1,100000)
    std::cout << "NULL" << std::endl;
    return 0;
  }
  std::vector<int> father(n + 1, 0);
  for (int i = 0; i < n + 1; i++) {
    father[i] = i;
  }
  for (int i = 0; i < m; i++) {
    int x = 0, y = 0, k = 0;
    std::cin >> x >> y >> k;
    if (x < 1 || x > n || y < 1 || y > n||(k!=0&&k!=1)) {
      std::cout << "da pian zi" << std::endl;
    } else {
      if (k == 0) {
        join(father, x, y);
      } else {
        if(isSame(father,x,y)){
          std::cout << "we are a team" << std::endl;
        }
        else{
          std::cout << "we are not a team" << std::endl;
        }
      }
    }
  }
  return 0;
}