#include <iostream>

#include <vector>
#include <algorithm>
//审题 可靠性越低价格越便宜
bool isValid(std::vector<std::vector<std::pair<int,int>>> parts,int r,int total){
    int price_sum = 0;   
    for(int i=0;i<parts.size();i++){
       auto it = std::lower_bound(parts[i].begin(),parts[i].end(),r,[](std::pair<int,int> pair,int r){//REVIEW 两者顺序无所谓
         return pair.first<r;
       });
       if(it == parts[i].end()){
         return false;
       }
       else{
         price_sum+=(*it).second;
       }
    }
    return price_sum <= total;
}


int main(){
    int total;
    std::cin >> total;
    int k;
    std::cin >> k;
    int n;
    std::cin >> n;
    //检索到特定种类特定upper_bound的
    std::vector<std::vector<std::pair<int,int>>> parts(k);
    int l = 0;
    int r = 0;
    for(int i=0;i<n;i++){
      int type,reability,price;
      std::cin >> type >> reability >> price;
      r=std::max(r,reability);
      parts[type].push_back({reability,price});
    }
    int min_price = 0;
    for(int i=0;i<parts.size();i++){
      if(parts[i].empty()){//REVIEW 题目不保证没种零件都存在
        std::cout << "-1" << std::endl;
        return 0;
      }
      std::sort(parts[i].begin(),parts[i].end());
      min_price+=parts[i][0].second;
    }
    if(min_price>total){
        std::cout << "-1" << std::endl;
        return 0;
    }
    int result = 0;
    while(l<=r){
      int mid = l+(r-l)/2;
      if(isValid(parts,mid,total)){
        result = mid;
        l=mid+1;
      }
      else{
        r=mid-1;
      }
    }
    std::cout << result << std::endl;
    return 0;
}