// #include <iostream>
// #include <sstream>

// #include <vector>

// #include <deque>

// #include <climits>

// bool isValid( std::deque<int>  queue){
//   int cur = INT_MIN;
//   while(!queue.empty()){
//     if(queue.back()<cur){
//       return false;
//     }
//     cur=queue.back();
//     queue.pop_back();
//   }
//   return true;
// }

// int main(){
//   std::string input;
//   std::cin >> input;
//   std::stringstream ss(input);
//   std::vector<int> input_v;
//   std::string e;
//   while(std::getline(ss,e,',')){
//     input_v.push_back(std::stoi(e));
//   }
//   int l=0;
//   std::deque<int> queue;
//   int length =0;
//   int start =0;
//   for(int r=0;r<input_v.size();r++){
//     queue.push_back(input_v[r]);
//     while(!isValid(queue)){
//       queue.pop_front();
//       l++;
//     }
//     int cur_length = r-l+1;
//     if(cur_length>length){
//       length=cur_length;
//       start=l;
//     }
//   }
//   std::cout << length <<"," <<start <<std::endl;
//   return 0;
// }

//REVIEW 可以不用滑动窗
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> split(const string& str, char delimiter) {
    vector<int> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        result.push_back(stoi(token));
    }
    return result;
}

vector<int> findLongLanterns(vector<int>& nums) {
    if (nums.empty()) {
        return {0, 0};
    }
    
    int left = 0;           // 窗口左边界
    int bestLen = 0;        // 最长长度
    int bestBegin = 0;      // 最长起始位置
    
    for (int right = 0; right < nums.size(); right++) {
        // 当窗口不满足非递增条件时，移动左边界
        // 条件：新加入的元素比前一个元素大（违反非递增）
        if (right > 0 && nums[right] > nums[right - 1]) {
            left = right;   // 窗口重置到当前位置
        }
        
        // 计算当前窗口长度
        int curLen = right - left + 1;
        
        // 更新最优解（严格大于才更新，保证取最左边的起始位置）
        if (curLen > bestLen) {
            bestLen = curLen;
            bestBegin = left;
        }
    }
    
    return {bestLen, bestBegin};
}

int main() {
    string input;
    getline(cin, input);
    
    vector<int> nums = split(input, ',');
    vector<int> result = findLongLanterns(nums);
    
    cout << result[0] << "," << result[1] << endl;
    
    return 0;
}