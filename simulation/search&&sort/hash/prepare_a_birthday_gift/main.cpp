#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm> 
#include<cmath>
#include<map>

using namespace std;

// 通用切割函数
vector<string> split(const string& str, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start));
    return result;
}

class Solution {
public:
    // 力扣风格的函数：统计生日月份等于给定月份的人数
    int countBirthdays(int month, const vector<string>& names, const vector<string>& birthdays) {
       map<string,int> map;
       int count = 0;
       for(int i=0;i<names.size();i++){
         auto start_index = birthdays[i].find_first_of('/');
         auto end_index = birthdays[i].find_last_of('/');
         string m = birthdays[i].substr(start_index+1,end_index-start_index-1);
         map[names[i]]=stoi(m);
       }
       for(auto it = map.begin();it!=map.end();it++){
         if((*it).second==month){
           count++;
         }
       }
       return count;
    }
};

int main() {
    int month;
    string name;
    string birthday;
    
    cin >> month;
    cin.ignore();  // 忽略换行符
    getline(cin, name);
    getline(cin, birthday);

    vector<string> names = split(name, " ");
    vector<string> birthdays = split(birthday, " ");
    
    // 调用力扣风格的函数
    Solution solution;
    int result = solution.countBirthdays(month, names, birthdays);
    
    cout << result << endl;
    
    return 0;
}