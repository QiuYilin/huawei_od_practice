#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include<iterator>

using namespace std;

vector<int> readIntArray() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    return vector<int>(istream_iterator<int>(iss), {});
}

int main() {
    //REVIEW 最多选两种产品 直接枚举
    vector<int> input = readIntArray();
    int m = input[0], N = input[1], X = input[2];
    vector<int> returns = readIntArray();
    vector<int> risks = readIntArray();
    vector<int> maxInvestments = readIntArray();

    int maxReturn = 0;
    vector<int> bestInvestments(m, 0);

    for (int i = 0; i < m; i++) {
        if (risks[i] > X) continue;
        // 考虑只投资单个理财产品的情况
        int investI = min(N, maxInvestments[i]);
        int retI = investI * returns[i];
        if (retI > maxReturn) {
            maxReturn = retI;
            fill(bestInvestments.begin(), bestInvestments.end(), 0);
            bestInvestments[i] = investI;
        }
        // 考虑两个产品组合
        for (int j = i + 1; j < m; j++) {
            if (risks[i] + risks[j] > X) continue;
            
            int investI, investJ;
            // 优先投资投保率高的产品
            if (returns[i] > returns[j]) {
                investI = min(N, maxInvestments[i]);
                investJ = min(N - investI, maxInvestments[j]);
            } else {
                investJ = min(N, maxInvestments[j]);
                investI = min(N - investJ, maxInvestments[i]);
            }
            
            int retPair = investI * returns[i] + investJ * returns[j];
            if (retPair > maxReturn) {
                maxReturn = retPair;
                fill(bestInvestments.begin(), bestInvestments.end(), 0);
                bestInvestments[i] = investI;
                bestInvestments[j] = investJ;
            }
        }
    }

    for (int investment : bestInvestments) {
        cout << investment << " ";
    }
    cout << endl;

    return 0;
}

