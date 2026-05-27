#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <sstream>

using namespace std;

struct TreeNode {
    string val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string x) : val(x), left(nullptr), right(nullptr) {}
};

// 字符串分割函数
vector<string> split(const string& str, char delimiter) {
    vector<string> result;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}

// 层序建树
TreeNode* buildTree(const vector<string>& arr) {
    if (arr.empty() || arr[0] == "#") return nullptr;
    
    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;
    q.push(root);
    
    int idx = 1;
    while (!q.empty() && idx < arr.size()) {
        TreeNode* cur = q.front();
        q.pop();
        
        // 左孩子
        if (idx < arr.size() && arr[idx] != "#") {
            cur->left = new TreeNode(arr[idx]);
            q.push(cur->left);
        }
        idx++;
        
        // 右孩子
        if (idx < arr.size() && arr[idx] != "#") {
            cur->right = new TreeNode(arr[idx]);
            q.push(cur->right);
        }
        idx++;
    }
    return root;
}

//REVIEW 思路 枚举所有字数的序列化形式
class Solution {
private:
    unordered_map<string, int> serialCount;  // 序列化字符串 -> 出现次数
    unordered_map<string, int> serialNodeCount;  //REVIEW 用于查询节点个数
    unordered_map<string, int> firstOrder;  // 序列化字符串 -> 首次出现的顺序
    int orderId = 0;
    
    string serialize(TreeNode* root) {
        if (!root) return "#";
        
        // 前序遍历序列化
        string left = serialize(root->left);
        string right = serialize(root->right);
        
        // 格式: val,left,right
        return root->val + "," + left + "," + right;
    }
    
    //后序遍历 有返回值 返回 子树的序列 和 节点数
    pair<string, int> dfs(TreeNode* root) {
        if (!root) return {"#", 0};
        
        auto left = dfs(root->left);
        auto right = dfs(root->right);
        
        string serial = root->val + "," + left.first + "," + right.first;
        int nodeCount = 1 + left.second + right.second;
        
        // 记录首次出现的顺序
        if (serialCount.find(serial) == serialCount.end()) {
            firstOrder[serial] = orderId++;
        }
        
        serialCount[serial]++;
        serialNodeCount[serial] = nodeCount;
        
        return {serial, nodeCount};
    }
    
public:
    vector<string> findDuplicateSubtrees(TreeNode* root) {
        if (!root) return {};
        
        dfs(root);
        
        // 收集所有重复的子树（出现次数 >= 2）
        vector<string> duplicates;
        for (auto& [serial, count] : serialCount) {
            if (count >= 2) {
                duplicates.push_back(serial);
            }
        }
        
        // 排序规则：
        // 1. 节点数多的优先（降序）
        // 2. 节点数相同时，首次出现顺序小的优先（升序）
        sort(duplicates.begin(), duplicates.end(),
            [this](const string& a, const string& b) {
                int countA = serialNodeCount[a];
                int countB = serialNodeCount[b];
                if (countA != countB) {
                    return countA > countB;  // 节点数降序
                }
                return firstOrder[a] < firstOrder[b];  // 前序顺序升序
            });
        
        return duplicates;
    }
};

int main() {
    string input;
    cin >> input;
    
    vector<string> arr = split(input, ',');
    TreeNode* root = buildTree(arr);
    
    Solution solution;
    vector<string> result = solution.findDuplicateSubtrees(root);
    
    for (const string& s : result) {
        cout << s << endl;
    }
    
    return 0;
}