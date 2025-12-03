#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node* root, int val) {
    if (!root) return newNode(val);
    if (val < root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int C;
    scanf("%d", &C);
    for (int t = 1; t <= C; t++) {
        int N;
        scanf("%d", &N);
        int vals[N];
        for (int i = 0; i < N; i++) scanf("%d", &vals[i]);

        Node* root = NULL;
        for (int i = 0; i < N; i++) root = insert(root, vals[i]);

        printf("Case %d:\n", t);

        Node* queue[500];
        int front = 0, back = 0;
        queue[back++] = root;

        int first = 1;
        while (front < back) {
            Node* cur = queue[front++];
            if (!first) printf(" ");
            printf("%d", cur->val);
            first = 0;
            if (cur->left) queue[back++] = cur->left;
            if (cur->right) queue[back++] = cur->right;
        }
        printf("\n\n");

        freeTree(root);
    }
    return 0;
}
