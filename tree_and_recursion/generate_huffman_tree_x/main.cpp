#include <cstdio>
#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include<queue>
#include<algorithm>
#include <functional> 
using namespace std;

//REVIEW 因为不断产生新的parent，比较内容动态变化，所以整体依靠优先队列

//构造树
struct Node { 
    int value; // 节点的值
    int num; // 节点子树拥有的节点数量 REVIEW 子树高度比较的依据
    Node* left; // 左节点
    Node* right; // 右节点
    Node(int value, int num):value(value), left(nullptr),right(nullptr), num(num){}
};

// 自定义排序
struct CompareItem {
    bool operator()(const Node* a, const Node* b) {
       if (a->value == b->value) {
           return a->num > b->num;
       } 
       return a->value > b->value;
    }
};

// 中序遍历
void dfs(Node* root) {
    if (nullptr == root) {
        return;
    }
    dfs(root->left);
    cout << root->value<<" ";
    dfs(root->right);
}

int main() {
    int n ;
    cin >>n;
    // 优先队列，自定义实现排序
    priority_queue<Node*, vector<Node*>, CompareItem> pq;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin>>tmp;
        pq.emplace(new Node(tmp, 1));
    }

    Node* root = nullptr;
    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* parent = new Node(left->value + right -> value, left->num + right->num + 1);
        parent->left = left;
        parent->right = right;
        pq.emplace(parent);
    }
    root = pq.top();

    dfs(root);
    return 0;

}
