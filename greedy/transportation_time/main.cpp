#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include <iomanip> 
using namespace std;

int main() {
    int m,n;
    cin >> m >> n;
    //REVIEW 以第一辆车出发作为时间起点
    double res = 0;
    for (int i = 0; i < m; i++) {
        double speed;
        cin >> speed;
        // (n / speed + i) 以自己速度到终点的时间 + 出发时间
        res = max(res, n / speed + i);
    }

    // 最后一台车的时间
    res = res - (m - 1);
    
    auto formatOutput = [](double num) {
        ostringstream oss;
        oss << fixed << setprecision(3) << num;  //REVIEW 借助sstream
        string result = oss.str();

        //REVIEW 去掉多余的.00等
        result.erase(result.find_last_not_of('0') + 1, string::npos);
        if (result.back() == '.') result.pop_back(); // 去掉末尾的点

        return result;
    };

    cout << formatOutput(res) << endl; 
    
    return 0;
}
