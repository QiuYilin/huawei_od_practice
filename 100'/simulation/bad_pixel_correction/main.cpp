#include <iostream>
#include <vector>

// 审题：diff = |中心元素-周围均值|
// 均值四舍五入
int average(int a, int b) {
  if (a % b < (double)b*0.5) {
    return std::floor((double)a / b);
  } else {
    return std::ceil((double)a / b);
  }
}

int main() {
  std::vector<int> input(9,0);
  for (int i = 0; i < 9; i++) {
    std::cin >> input[i];
  }
  // 疑问 计算机中如何表达四舍五入
  int around_sum = 0;
  int sum = 0;
  for (int i = 0; i < input.size(); i++) {
    if (i != 4) {
      around_sum += input[i];
    }
    sum += input[i];
  }
  int around_average = 0;
  
    around_average = average(around_sum,8);

  int diff = std::abs(input[4] - around_average);
  if (diff > 50) {
    input[4] = around_average;
  } else if (diff >= 30 && diff <= 50) {
    input[4]=average(sum,9);
  }
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        if(j!=0){
            std::cout << " ";
        }
        std::cout <<input[3*i+j];
    }    
    std::cout << std::endl;
  }
  return 0;
}