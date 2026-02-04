// #include <iostream>
// #include <vector>

// class TreeNode{
// public:
// TreeNode(int val):val(val){

// }//疑问 构造函数初始化列表怎么写的
// TreeNode *left;
// TreeNode *right;
// int val;
// };
// //疑问 递归没手感了 什么时候用尾递归 什么时候不用
// void buildTreeNode(TreeNode *root,const std::vector<int> &input,int i,int j){
//     //终止条件
//     if(root == nullptr){
      
//     }
//     //全部比root->val小的数字段
    
//     buildTreeNode(root->left,input,);
//     buildTreeNode(root->right,input,);
// }

// int main(){
//     //判断二叉搜索树前序遍历 疑问 什么是搜索树来着
//     //最左子节点 最右子节点
//     std::vector<int> input;
//     int node;
//     while(std::cin >> node){
//       input.push_back(node);
//     }

//     TreeNode *root = new TreeNode(input[0]);

//     auto result = buildTreeNode(root,input,0,input.size()-1);
    
//     return 0;
// }

// 8
// 31647.   10 14 13

#include <cstdio>
#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<algorithm>
#include<list>
#include<queue>
#include<map>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node():left(nullptr), right(nullptr){}
    Node(int value, Node* left, Node* right):value(value),left(left),right(right) {}
    Node(int value):value(value),left(nullptr), right(nullptr){}
};


// 通用 split 函数
vector<string> split(const string& str, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // 添加最后一个部分
    result.push_back(str.substr(start));
    return result;
}

//同时验证树和构建树
bool isValid(Node* root, int start, int end, vector<int>& preOrder) {
    if (start == end) {
        return true;
    }
    
    int i = start + 1;
    // 不断迭代找到父节点的右子树节点为止 
    while (i <= end && preOrder[i] < root -> value) {
        i++;
    }
       
    int j = i;
    // 按照搜索树规则 找到右子树的终点位置
    while (j <= end && preOrder[j] > root -> value) {
        j++;
    }
    // 异常 j 必须大于end才是正常的
    if (j <= end) {
        return false;
    }

    // i > start + 1说明才存在左子树
    if (i > start  + 1) {
        root->left = new Node(preOrder[start+1]);
        //递归构建左节点的结构
        return isValid(root->left, start + 1, i - 1, preOrder);
    }
    
    // i <= end说明才存在右子树
    if (i <= end) {
        root->right = new Node(preOrder[i]);
        return isValid(root->right, i, end, preOrder);
    }

    return true;
}

// 获取左伞坠的值
int leftBottom(Node* root, int level) {
    if (root -> left != nullptr) {
        return leftBottom(root->left, level + 1);
    }
    // 说明根节点没有子节点，没有坠子，直接返回0
    if (level == 0) {
        return 0;
    }
    
    // 存在
    if (root->right != nullptr) {
        return leftBottom(root->right, level + 1);
    }
    return root->value;
}

// 获取右伞坠的值
int rightBottom(Node* root, int level) {
    if (root -> right != nullptr) {
        return rightBottom(root->right, level + 1);
    }
    // 说明根节点没有子节点，没有坠子，直接返回0
    if (level == 0) {
        return 0;
    }
    
    // 存在右节点
    if (root->left != nullptr) {
        return rightBottom(root->left, level + 1);
    }
    return root->value;
}

void dfs(Node* root, vector<int>& res) {
    if (root == nullptr) {
        return;
    }
    dfs(root->left, res);
    res.push_back(root->value);
    dfs(root->right, res);
}


int main() {
    string line;
    getline(cin, line);
    vector<string> tmp = split(line, " ");
    int n = tmp.size();
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = stoi(tmp[i]);
    }
    Node* root = new Node(ans[0]);
    // 不合法
    if (!isValid(root, 0, ans.size() - 1, ans)) {
        cout << "0 0 0";
        return 0;
    }
    vector<int> res;
    dfs(root, res);//中序遍历

   int leftValue = leftBottom(root, 0);
   int rightValue = rightBottom(root, 0);

   cout << "1 " << leftValue << " " << rightValue;
   return 0;
}
