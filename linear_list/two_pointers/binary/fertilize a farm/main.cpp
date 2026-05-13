#include <iostream>
#include <vector>
bool isValid(std::vector<int> fields, int k, int target) {
  int count = 0;
  for (int i = 0; i < fields.size(); i++) {
    count += std::ceil((float)fields[i] / k);
  }
  return count<=target;
}

int main() {
  int m, n;
  std::cin >> m >> n;
  std::vector<int> fields(m);
  for (int i = 0; i < m; i++) {
    std::cin >> fields[i];
  }
  int l = 1;
  int r = std::pow(10, 9);
  if (m > n) {
    std::cout << "-1" << std::endl;
  }
  while (l < r) {
    int mid = l + (r - l) / 2;
    if (isValid(fields, mid, n)) {
      r=mid;
    }
    else{
      l=mid+1;
    }
  }
  std::cout << l << std::endl;
  return 0;
}