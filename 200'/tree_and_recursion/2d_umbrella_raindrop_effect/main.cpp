#include <iostream>
#include <vector>

class TreeNode{
public:
TreeNode(int val):val(val){

}//疑问 构造函数初始化列表怎么写的
TreeNode *left;
TreeNode *right;
int val;
};
//疑问 递归没手感了 
void buildTreeNode(TreeNode *root,const std::vector<int> &input,int i,int j){
    //终止条件
    if(root == nullptr){
      
    }
    //全部比root->val小的数字段
    
    buildTreeNode(root->left,input,);
    buildTreeNode(root->right,input,);
}

int main(){
    //判断二叉搜索树前序遍历 疑问 什么是搜索树来着
    //最左子节点 最右子节点
    std::vector<int> input;
    int node;
    while(std::cin >> node){
      input.push_back(node);
    }

    TreeNode *root = new TreeNode(input[0]);

    auto result = buildTreeNode(root,input,0,input.size()-1);
    
    return 0;
}

8
31647.   10 14 13