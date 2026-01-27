#include <iostream>
#include <sstream>
#include <vector>

int main() {
  // 合法性检查
  std::string input;
  std::cin >> input;
  std::vector<int> ipv4;
  std::stringstream ss(input);
  std::string e;
  while (std::getline(ss, e, '#')) {
    // stoi对于乱码的处理
    for (int i = 0; i < e.size(); i++) {
      if (!std::isdigit(e[i])) {
        std::cout << "invalid IP" << std::endl;
        return 0;
      }
    }
    ipv4.push_back(std::stoi(e));
  }
  if (ipv4.size() != 4) {
    std::cout << "invalid IP" << std::endl;
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    if (i == 0) {
      if (ipv4[i] < 0 || ipv4[i] > 128) {
        std::cout << "invalid IP" << std::endl;
        return 0;
      }
    } else {
      if (ipv4[i] < 0 || ipv4[i] > 255) {
        std::cout << "invalid IP" << std::endl;
        return 0;
      }
    }
  }
  long long result = 0;
  for(int i=0;i<4;i++){
    result = (result<<8)|ipv4[i];
  }
  std::cout << result << std::endl;
  return 0;
}