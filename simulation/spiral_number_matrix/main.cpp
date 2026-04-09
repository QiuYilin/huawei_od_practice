#include <iostream>
#include <vector>
#include <sstream>

int main() {
    int n, m;
    std::cin >> n >> m; // 读取 n 和 m
    int cols = (n + m - 1) / m; // REVIEW 计算列数 向上取整

    std::vector<std::vector<int>> matrix(m, std::vector<int>(cols)); // 定义矩阵
    int num = 1, top = 0, bottom = m - 1, left = 0, right = cols - 1;//REVIEW 四边界法

    while (num <= n) {//REVIEW 比起用圈数 用num放到循环里更完整
        for (int i = left; i <= right && num <= n; i++) matrix[top][i] = num++; // 从左到右
        top++;
        for (int i = top; i <= bottom && num <= n; i++) matrix[i][right] = num++; // 从上到下
        right--;
        for (int i = right; i >= left && num <= n; i--) matrix[bottom][i] = num++; // 从右到左
        bottom--;
        for (int i = bottom; i >= top && num <= n; i--) matrix[i][left] = num++; // 从下到上
        left++;
    }

    std::ostringstream output;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                output << '*';
            } else {
                output << matrix[i][j];
            }
            if (j < cols - 1) output << ' '; // 避免末尾多余空格
        }
        output << '\n'; // 换行
    }
    
    std::cout << output.str(); // 一次性输出，提高性能
    return 0;
}

