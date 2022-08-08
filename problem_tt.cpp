#include <stdio.h>
#include <stdlib.h>


struct Node {
    struct Node *left;
    struct Node *right;
    int data;
};

struct Node* NodeCtr(struct Node *left, struct Node *right, int data);
struct Node* TreeCtr(int *arr, int **pre, int size, int root);
int make_common(struct Node *root, int n);
int TreeDtr(struct Node *root);


int main() {
    unsigned n = 0;
    int *pre, *in, *old_pre;
    struct Node *root;

    scanf("%u", &n);

    pre = (int*)calloc(n, sizeof(int));
    in  = (int*)calloc(n, sizeof(int));
    old_pre = pre;

    for (unsigned i = 0; i < n; i++) 
        scanf("%d", &pre[i]);
    
    for (unsigned i = 0; i < n; i++)
        scanf("%d", &in[i]);

    root = TreeCtr(in, &pre, n, *pre);

    printf("%d\n", n);
    make_common(root, n);
    printf("\n");
    for (unsigned i = 0; i < n; i++) 
        printf("%d ", old_pre[i]);
    printf("\n");    

    TreeDtr(root);

    free(old_pre);
    free(in);

    return 0;
}

struct Node* NodeCtr(struct Node *left, struct Node *right, int data) {
    struct Node *node = (struct Node*)calloc(1, sizeof(struct Node));
    node->left  = left;
    node->right = right;
    node->data  = data;

    return node;
}

struct Node* TreeCtr(int *arr, int **pre, int size, int root) {
    int i = 0;
    struct Node *left  = NULL;
    struct Node *right = NULL;

    if (size == 1) 
        return NodeCtr(NULL, NULL, root);

    while (arr[i] != root) 
        i++;

    if (i != 0) {
        int new_root;
        (*pre)++;
        new_root = **pre;
        left  = TreeCtr(arr, pre, i, new_root);
    }
    
    if (i != size - 1) {
        int new_root;
        (*pre)++;
        new_root = **pre;
        right = TreeCtr(arr + i + 1, pre, size - i - 1, new_root);
    }

    return NodeCtr(left, right, root);
}

int make_common(struct Node *root, int n) {
    static int i = 0;
    i++;

    printf("1 ");

    if (((root->left == NULL) && (root->right == NULL)) && (i != n)) { 
        printf("0 0 ");
        return 0;
    }
    else if (i == n) {
        printf("0 ");
        return 0;
    }
    
    if (root->left == NULL)
        printf("0 ");
    else 
        make_common(root->left, n);

    if (root->right == NULL)
        printf("0 ");
    else 
        make_common(root->right, n);
    
    return 0;
}

int TreeDtr(struct Node *root) {
    if ((root->left == NULL) && (root->right == NULL)) {
        free(root);
        return 0;
    }

    if (root->left != NULL) 
        TreeDtr(root->left);

    if (root->right != NULL) 
        TreeDtr(root->right);

    free(root);

    return 0;
}