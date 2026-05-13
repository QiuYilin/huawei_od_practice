#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

const double EPS = 1e-10;


// 判断是否存在长度 >= L 的子数组，使平均值 >= mid
// 返回是否存在，同时更新起点和长度
bool check(const vector<double> &nums, int L, double mid, int &best_start, int &best_len) {
    int N = nums.size();
    vector<double> prefix(N + 1, 0.0);
    for (int i = 0; i < N; ++i)
        prefix[i + 1] = prefix[i] + nums[i] - mid;  // nums[i]-mid

    double min_prefix = 0.0;
    int min_idx = 0;

    best_len = N+1;
    bool found = false;

    for (int r = L; r <= N; ++r) {
        // 左端点范围 [0, r-L]
        if (prefix[r] - min_prefix >= -EPS) {  // 子数组平均 >= mid
            int curr_len = r - min_idx;
            if (!found || curr_len < best_len || (curr_len == best_len && min_idx < best_start)) {
                best_start = min_idx;
                best_len = curr_len;
            }
            found = true;
        }

        // 更新最小前缀，只考虑长度 ≥ L 的子数组
        if (prefix[r - L + 1] < min_prefix) {
            min_prefix = prefix[r - L + 1];
            min_idx = r - L + 1;
        }
    }

    return found;
}

int main() {
    int N, L;
    cin >> N >> L;
    vector<double> nums(N);
    for (int i = 0; i < N; ++i) {
        double x;
        cin >> x;
        nums[i] = log(x);  // 转换为对数
    }
    
    
    double low = nums[0], high = nums[0];  
    // 确定二分边界
    for (double& num : nums) {
        low = min(low, num);
        high = max(high, num);
    }


    int best_start = 0, best_len = L;
    // 枚举最大子数组平均值 
    while (high - low > EPS) {
        double mid = (low + high) / 2.0;
        int tmp_start, tmp_len;
        // 更新获得的最佳子数组位置，并更新 枚举边界
        if (check(nums, L, mid, tmp_start, tmp_len)) {
            low = mid;
            best_start = tmp_start;
            best_len = tmp_len;
        } else {
            high = mid;
        }
    }

    cout << best_start << " " << best_len << endl;
    return 0;
}

