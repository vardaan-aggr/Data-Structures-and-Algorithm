# include<iostream>
using namespace std;

struct node {
    int val;
    node* left;
    node* right;

    node(int x) {
        val = x;
        left = right = nullptr;
    }
};

void transform(node* pointer, int& sum) {
    if (!pointer) return;
    transform(pointer->right, sum);
    sum += pointer->val;
    pointer->val = sum;
    transform(pointer->left, sum);
}

node* insert(node* root, int key) {
    if (!root)
        return new node(key);
    if (key < root->val)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}

void inorder(node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

int main(){

    node* root = nullptr;
    int num, val;

    cout << "Enter number of elements : ";
    cin >> num;

    cout << "Enter " << num << " integers: ";
    for (int i = 0; i < num; i++) {
        cin >> val;
        root = insert(root, val); }
    cout <<"orignal : ";
    inorder(root);
    int sum=0;
    transform(root,sum);
    cout<<endl;
    cout <<"after implementation : " ;
    inorder(root);
    return 0;
}