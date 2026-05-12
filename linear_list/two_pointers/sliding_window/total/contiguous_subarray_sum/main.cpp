#include <iostream>
#include <vector>

int main() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> input(n);

  for (int i = 0; i < n; i++) {
    std::cin >> input[i];
  }

  int result = 0;
  int l = 0;
  int sum = 0;
  for (int r = 0; r < n; r++) {
    sum += input[r];
    while (sum >= k) {
      result += n - r;
      sum -= input[l];
      l++;
    }
  }
  std::cout << result << std::endl;
  return 0;
}