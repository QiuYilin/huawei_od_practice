#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
std::unordered_map<std::string, int> inter{{"A",14},{"J", 11}, {"Q", 12}, {"k", 13}};
std::unordered_map<int, std::string> digit2card{{14,"A"},{11,"J"},{12,"Q"},{13,"K"}};
std::vector<int> split(std::string s) {
  std::vector<int> result;
  std::stringstream ss(s);
  std::string c;
  while (std::getline(ss, c, '-')) {
    int i = 0;
    if (std::isdigit(c[0])) {
      i = std::stoi(c);
    } else if (inter.find(c) != inter.end()) {
      i = inter[c];
    }
    result.push_back(i);
  }
  return result;
}

int main() {
  std::vector<int> cards(15, 4);
  std::string line;
  std::getline(std::cin, line);
  auto cards_in_hand = split(line);
  std::getline(std::cin, line);
  auto cards_used = split(line);
  for (int i = 0; i < cards_in_hand.size(); i++) {
    cards[cards_in_hand[i]]--;
  }
  for (int i = 0; i < cards_used.size(); i++) {
    cards[cards_used[i]]--;
  }
  std::vector<int> result;
  std::vector<int> cur;
  int max_l = 0;
  int l = 0;
  for (int i = 3; i < cards.size(); i++) {
    if (cards[i] == 0) {
      cur.clear();
      l = 0;
    } else {
      l++;
      cur.push_back(i);
      if (l >= max_l) {
        max_l = l;
        result = cur;
      }
    }
  }
  if (max_l < 5) {
    std::cout << "NO-CHAIN" <<std::endl;
  }
  else{
    for(int i=0;i<max_l;i++){
      if(i>0){
        std::cout << "-";
      }
      if(digit2card.find(result[i])!=digit2card.end()){
        std::cout << digit2card[result[i]];
      }
      else{
        std::cout << result[i];
      }
    }
  }
  std::cout << std::endl;
  return 0;
}
