#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<regex>
using namespace std;

//REVIEW 遍历多次正则可能没有指针遍历一次快

int main() {
	string input;
	getline(cin, input);
	// 正则替换优先选择替换 10* - 26*
    // REVIEW 不追求一次性表达 而是遍历所有情况
	for (int i = 26; i >= 1; i--) {
		string regexStr = to_string(i);
		if (i > 9) {
			regexStr += "\\*";
		}
		regex pattern(regexStr);
		string replaceChar =  string(1, 'a' + i -1);
		input = regex_replace(input, pattern, replaceChar);
	}
	cout << input;
	return 0;
}
