// #include <iostream>
// #include <string>

// int main() {
//   std::string a;
//   int b;
//   std::cin >> a >> b;

//   if (a.size() == 0 || a.size() > 10000) {
//     std::cout << -1 << std::endl;
//     return 0;
//   }

//   for (char c : a) {
//     if (!std::isalnum(static_cast<unsigned char>(c))) {
//       std::cout << -1 << std::endl;
//       return 0;
//     }
//   }
//   if (b < 1 || b > 99) {
//     std::cout << -1 << std::endl;
//     return 0;
//   }

//   int slow = 0;

//   int result = -1;

//   while (slow < a.size()) {
//     while (slow < a.size() && !std::isdigit(a[slow])) {
//       slow++;
//     }
//     if (slow >= a.size()) {
//       break;
//     }

//     int fast = slow;

//     while (fast < a.size() && std::isdigit(a[fast])) {
//       fast++;
//     }

//     // REVIEW int 21亿的size为 10位 不能使用stoi 字符长度可能超出范围
//     // int value = std::stoi(a.substr(slow, fast - slow));

//     int value = 0;
//     for (int k = slow; k < fast; k++) {
//       value = value * 10 + (a[k] - '0');
//       if (value > 999) {
//         result = -1;
//         std::cout << -1 << std::endl;
//         return 0;
//       }  // 提前退出，避免溢出
//     }

//     if (value < 0 || value > 999) {
//       result = -1;
//       break;
//     } else {
//       if (value % b == 0) {
//         result = std::max(result, value);
//       }
//     }

//     slow = fast;
//   }

//   std::cout << result << std::endl;

//   return 0;
// }

// 正则方式
#include <iostream>
#include <regex>
#include <string>

int main() {
  std::string input;
  int div;
  std::cin >> input >> div;
  for (auto c : input) {
    if (!isalnum(c)) {
      std::cout << "-1" << std::endl;
      return 0;
    }
  }
  if (input.size() < 1 || input.size() > 10000) {
    std::cout << "-1" << std::endl;
    return 0;
  }
  if (div < 1 || div > 99) {
    std::cout << "-1" << std::endl;
    return 0;
  }

  std::regex r(R"(\d+)");//REVIEW 注意斜杠方向
  std::sregex_iterator begin(input.begin(), input.end(), r);
  std::sregex_iterator end;  // REVIEW 默认贪婪
  int result = -1;
  for (auto it = begin; it != end; it++) {
    std::string value = it->str();
    int value_i = 0;
    for (int i = 0; i < value.size(); i++) {
      value_i = 10 * value_i + value[i] - '0';//REVIEW 是=
      if (value_i > 999) {
        std::cout << "-1" << std::endl;
        return 0;
      }
    }
    if(value_i%div==0){
      result = std::max(result,value_i);
    }
  }
  std::cout << result << std::endl;
  return 0;
}