// #include <iostream>
// // 审题 分多少次 会分成几份？
// //              叶子节点数目
// // 前中后序？

// //REVIEW 分的次数=最终份数-1

// int split_time = 0;
// int leaf = 0;
// void split(const int& n) {
//   if (n < 3) {
//     leaf++;
//     return;
//   }
//   int left = n / 2;
//   int right = n - n / 2;
//   split_time++;
//   split(left);
//   split(right);
// }

// int main() {
//   int n;
//   std::cin >> n;
//   split(n);
//   std::cout << split_time << " " << leaf << std::endl;
//   return 0;
// }

#include <iostream>
#include <unordered_map>
//REVIEW 用map做记忆化
std::unordered_map<int, int> memo;

int count_leaf(int n) {
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    
    if (n < 3) {
        memo[n] = 1;
        return 1;
    }
    
    int left = n / 2;
    int right = n - n / 2;
    
    int leaf_count = count_leaf(left) + count_leaf(right);
    memo[n] = leaf_count;
    return leaf_count;
}

int main() {
    int n;
    std::cin >> n;
    
    int leaf = count_leaf(n);
    int split_time = leaf - 1;  // 根据规律：分割次数 = 叶子数 - 1
    
    std::cout << split_time << " " << leaf << std::endl;
    
    return 0;
}