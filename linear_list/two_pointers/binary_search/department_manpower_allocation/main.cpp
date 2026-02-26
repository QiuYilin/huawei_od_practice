// #include <iostream>
// #include <algorithm>

// #include <vector>
// #include <cmath>
// bool isValid(std::vector<int> coors,int mid,int k){
//   auto it = coors.begin();
//   int count = 1;
//   while(it != coors.end()&&count <=k){
//     auto next  = std::lower_bound(it+1,coors.end(),*it+mid);
//     if(next!=coors.end()){
//         count++;
//     }
//     it=next;
//   }
//   return count == k;
// }


// int main(){
//     int n;
//     std::cin >> n;
//     std::vector<int> coors(n);
//     for(int i=0;i<n;i++){
//       std::cin >> coors[i];
//     }
//     int k;
//     std::cin >> k;

//     std::sort(coors.begin(),coors.end());
//     int l=1;
//     int r=coors[coors.size()-1]-coors[0];
//     //找最大的满足条件的距离
//     int result = 0;
//     while(l<r){//[). l=r时代表了什么
//       int mid = l+(r-l+1)/2;
//       if(isValid(coors,mid,k)){
//          l=mid;
//       }
//       else{
//          r=mid-1;
//       }
//     }
//     std::cout << l << std::endl;
//     return 0;
// }


#include <iostream>
#include <algorithm>
#include <vector>

// bool isValid(std::vector<int>& coors, int mid, int k) {
//     int count = 1;
//     auto it = coors.begin();
    
//     while (count < k) {
//         auto next = std::lower_bound(it + 1, coors.end(), *it + mid);
//         if (next == coors.end()) {
//             break;
//         }
//         count++;
//         it = next;
//     }
//     return count >= k;
// }
bool isValid(std::vector<int> coors,int mid,int k){
  auto it = coors.begin();
  int count = 1;
  //while(it != coors.end()&&count <=k){
  while(it != coors.end()&&count < k){
    auto next  = std::lower_bound(it+1,coors.end(),*it+mid);
    if(next!=coors.end()){
        count++;
    }
    it=next;
  }
  return count == k;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> coors(n);
    for (int i = 0; i < n; i++) {
        std::cin >> coors[i];
    }
    int k;
    std::cin >> k;

    std::sort(coors.begin(), coors.end());
    int l = 1;
    int r = coors.back() - coors[0];
    int result = 0;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (isValid(coors, mid, k)) {
            result =mid;
            l = mid+1;      
        } else {
            r = mid-1;  
        }
    }
    std::cout << result << std::endl;  // l == r，是最大值
    return 0;
}