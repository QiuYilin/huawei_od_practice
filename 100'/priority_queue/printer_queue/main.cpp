#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
// 审题
// 疑问 如果存在两个优先级一样的文件，则选择最早进入队列的那个文件。
// 优先队列能保证这个吗
// 疑问 cmp哪里写错了
class cmp {
 public:
  bool operator()(std::pair<int, int> a, std::pair<int, int> b) {
    int num_a = a.first;
    int num_b = b.first;
    if (num_a > num_b) {
      return false;
    } else if(num_a < num_b){
      return true;
    }
    else{//REVIEW  优先级队列本身无法表示push顺序 需要借助索引
      int index_a=a.second;
      int index_b=b.second;
      if(index_a>index_b){
        return true;
      }
      else{
        return false;
      }
    }
  }
};

int main() {
  std::vector<std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp>> printers(5);
  int n;
  std::cin >> n;
  std::cin.ignore();
  int file_id =1;
  for(int i=0;i<n;i++){
    std::string line;
    std::getline(std::cin,line);

    std::stringstream ss(line);
    std::string word;
    std::vector<std::string> command;
    while(ss>>word){
      command.push_back(word);
    }
    if(command[0]=="IN"){
      int printer_index = std::stoi(command[1].c_str())-1;
      printers[printer_index].push({std::stoi(command[2].c_str()),file_id});//REVIEW 不能用i 有OUT
      file_id++;
    }
    else{
      int printer_index =std::stoi(command[1].c_str())-1;
      if(printers[printer_index].empty()){
        std::cout << "NULL" << std::endl;
      }
      else{
        auto result = printers[printer_index].top().second;
        printers[printer_index].pop();
        std::cout << result << std::endl;
      }
    }
  }
  return 0;
}