#include <iostream>
void dfs(int &result,int res_p,int res_c,int last){
  if(last*res_p>res_c){
    return;
  }
  if((last+3+last+3*(res_p)) * res_p < res_c*2){//每次都多分三个的情况
    return;
  }
  if(res_p==0&&res_c==0){
    result++;
    return;
  }
  if(res_p<=0||res_c<=0){
    return;
  }
  for(int i=0;i<=3;i++){
   dfs(result,res_p-1,res_c-last-i,last+i);//REVIEW last+i表示上次分配的月饼
  }
}

int main(){
  int m,n;
  std::cin >> m >> n;
  int result = 0;
  //REVIEW 从递增考虑比递减简单
  for(int i=1;i<=n/m;i++){
    dfs(result,m-1,n-i,i);
  }
  std::cout << result << std::endl;
  return 0;
}