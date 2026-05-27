#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int controlInstruct(string& instruct) {
  vector<pair<string, int>> commands(instruct.size() / 2);
  for (int i = 0; i < instruct.size() / 2; i++) {
    commands[i].first = instruct[2 * i];
    commands[i].second = instruct[2 * i + 1] - '0';
  }

  int result = 0;
  for (int i = 0; i < commands.size(); i++) {
    auto c = commands[i].first;
    auto index = commands[i].second;
    if (c == "L") {
      result = result | (1 << index);
    } else if (c == "D") {
      result = result & (~(1 << index));
    } else {
      if ((result & (1 << index)) == 0) {
        result = result | (1 << index);
      } else {
        result = result & (~(1 << index));
      }
    }
  }
  return result;
}

int main() {
  string input;
  getline(cin, input);
  int res = controlInstruct(input);
  cout << res;
  return 0;
}
