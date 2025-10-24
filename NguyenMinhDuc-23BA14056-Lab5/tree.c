#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;


TreeNode* createNode(int val){
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
void insert(TreeNode** root, int val) {
    if (*root == NULL) {
        *root = createNode(val);
        return;
    }
    if (val < (*root)->val) {
        insert(&(*root)->left, val);
    } else if (val > (*root)->val) {
        insert(&(*root)->right, val);
    }
}

TreeNode* search(TreeNode* root, int val) {
    if (root == NULL || root->val == val) {
        return root;
    }
    if (val < root->val) {
        return search(root->left, val);
    }
    return search(root->right, val);
}

TreeNode* findMin(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode* findMax(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->val);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->val);
    }
}

int main(){
    TreeNode* root = NULL;
    insert(&root, 50);
    insert(&root, 30);
    insert(&root, 20);
    insert(&root, 40);
    insert(&root, 70);
    insert(&root, 60);
    insert(&root, 80);

    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");

    printf("Find 40: %s\n", search(root, 40) ? "Found" : "Not Found");
    printf("Find 90: %s\n", search(root, 90) ? "Found" : "Not Found");

    TreeNode* minNode = findMin(root);
    if(minNode != NULL){
        printf("Minimum value: %d\n", minNode->val);
    }

    TreeNode* maxNode = findMax(root);
    if(maxNode != NULL){
        printf("Maximum value: %d\n", maxNode->val);
    }

    return 0;
}
