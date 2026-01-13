#include <iostream>

#include <vector>
//审题 斜边的距离也是1

//f(x,y)=min(f(x-1,y)+1,f(x,y-1)+1,f(x-1,y-1)+1(如果成立))
int main() { 
    std::string input1;
    std::cin>>input1;
    std::string input2;
    std::cin>>input2;
    int m=input1.size();
    int n=input2.size();
    std::vector<std::vector<int>> dp(n+1,std::vector<int>(m+1));
    //初始化
    for(int i=0;i<n+1;i++){
        dp[i][0]=i;
    }
    for(int j=0;j<m+1;j++){
        dp[0][j]=j;
    }
    for(int i=1;i<n+1;i++){
        for(int j=1;j<m+1;j++){
            int select0 = dp[i-1][j]+1;//dp[0,1]+1
            int select1 = dp[i][j-1]+1;//dp[1,0]+1
            dp[i][j]=std::min(select0,select1);
            if(input1[j-1]==input2[i-1]){
                int select2 = dp[i-1][j-1]+1;
                dp[i][j]=std::min(dp[i][j],select2);
            }
        }
    }
    std::cout << dp[n][m]<<std::endl;
    return 0; 
}