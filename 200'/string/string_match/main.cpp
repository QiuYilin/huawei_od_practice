#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// REVIEW 正则问题 可以不从有限自动机开始推 可以直接用现成的

int main() {
  std::vector<std::string> inputs;
  std::string line;
  std::getline(std::cin, line);
  std::stringstream ss(line);
  std::string s;
  while (ss >> s) {
    inputs.push_back(s);
  }
  std::string pattern;
  std::cin >> pattern;
  std::string new_pattern;
  for (int i = 0; i < pattern.size(); i++) {
    if (pattern[i]=='*') {
      new_pattern+=".*";
    }
    else{
      new_pattern+=pattern[i];
    }
  }

  std::regex p(new_pattern);
  std::vector<int> result;
  for(int i=0;i<inputs.size();i++){
    if(std::regex_match(inputs[i],p)){
      result.push_back(i);
    }
  }
  if(result.empty()){
    std::cout << "-1" <<std::endl;
  }
  else{
    for(int i=0;i<result.size();i++){
      if(i>0){
        std::cout << ",";
      }
      std::cout << result[i];
    }
    std::cout << std::endl;
  }
  return 0;
}
