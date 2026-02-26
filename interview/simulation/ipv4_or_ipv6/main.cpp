#include <iostream>
#include <sstream>
#include <vector>

// 审题 IPv6由8组16进制的数字来表示
bool isIpv4Valid(std::string e) {
  // 范围0~255   不会以0开头
  if (e.empty()) {
    return false;
  }
  if (e[0] == '0' && e.size() > 1) {
    return false;
  }
  // 疑问 stoi  123abc会得到什么
  for (auto c : e) {
    if (!isdigit(c)) {
      return false;
    }
  }

  if (std::stoi(e) < 0 || std::stoi(e) > 255) {
    return false;
  }

  return true;
}

bool isIpv6Valid(std::string e) {
  // 范围0~255   不会以0开头
  if (e.empty()) {
    return false;
  }
  if (e.size()!=4) {
    return false;
  }

  for (auto c : e) {
    if (!isdigit(c)&&(std::tolower(c)-'a'<0)&&(std::tolower(c)-'a'>5)) {
      return false;
    }
  }

  return true;
}

int main() {
  std::string input;
  std::cin >> input;
  std::stringstream ss(input);
  // 通过.和:初步判断归类
  if (input.find('.') != -1) {
    // 是否是ipv4
    // 按.分隔 四个元
    std::string element;
    std::vector<std::string> input_v;
    while (std::getline(ss, element, '.')) {
      input_v.push_back(element);
    }
    if (input_v.size() != 4) {
      std::cout << "Neither" << std::endl;
      return 0;
    }
    for (int i = 0; i < 4; i++) {
      if (!isIpv4Valid(input_v[i])) {
        std::cout << "Neither" << std::endl;
        return 0;
      }
    }
    std::cout << "IPv4" << std::endl;
    return 0;
  } else {
    // 是否是ipv6
    // 按冒号分隔 八个元素
    std::string element;
    std::vector<std::string> input_v;
    while (std::getline(ss, element, ':')) {
      input_v.push_back(element);
    }
    if (input_v.size() != 8) {
      std::cout << "Neither" << std::endl;
      return 0;
    }
    for (int i = 0; i < 8; i++) {
      if (!isIpv6Valid(input_v[i])) {
        std::cout << "Neither" << std::endl;
        return 0;
      }
    }
    std::cout << "IPv8" << std::endl;
    return 0;
  }
  return 0;
}