#include <stdio.h>
#include <stdlib.h>

struct node {
    double priority;
    struct node* left;
    struct node* right;
};

struct node* root = NULL;

struct node* create_new_heap_node(double priority) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->priority = priority;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* merge(struct node* heap1, struct node* heap2) {
    struct node* temp;

    if (heap1 == NULL) {
        return heap2;
    } else if (heap2 == NULL) {
        return heap1;
    } else {
        if (heap1->priority > heap2->priority) {
            temp = heap1;
            heap1 = heap2;
            heap2 = temp;
        }
        temp = heap1->left;
        heap1->left = heap1->right;
        heap1->right = temp;
        heap1->left = merge(heap2, heap1->left);
    }

    return heap1;
}

void traverse_print(struct node* node) {
    if (node != NULL) {
        printf("(");
        printf("%f ", node->priority);
        traverse_print(node->left);
        traverse_print(node->right);
        printf(")");
    }
}

int traverse_count(struct node* node) {
    if (node != NULL) {
        return 1 + traverse_count(node->left) + traverse_count(node->right);
    }
    return 0;
}

void traversal_print_heap() {
    printf("Heap: ");
    traverse_print(root);
    printf("\n");
}

int traversal_count_heap() {
    return traverse_count(root);
}

void reset(struct node* node) {
    if (node != NULL) {
        reset(node->left);
        reset(node->right);
        free(node);
    }
}

void reset_heap() {
    reset(root);
    root = NULL;
}

void enqueue_heap(double priority) {
    struct node* newNode = create_new_heap_node(priority);
    root = merge(root, newNode);
    // printf("Enqueue - ");
    // traversal_print_heap();
    // printf("\n");
}

double dequeue_heap() {
    if (root == NULL) {
        fprintf(stderr, "Cannot dequeue from an empty heap!\n");
        exit(1);
    }

    struct node* temp1 = root->left;
    struct node* temp2 = root->right;
    double priority = root->priority;

    temp1 = merge(temp1, temp2);
    free(root);
    root = temp1;

    // printf("Dequeue - ");
    // printf("List after dequeue:\n");
    // traversal_print_heap();
    // printf("\n");

    return priority;
}

// int main() {
    
//     enqueue(6.0);
//     enqueue(12.0);
//     enqueue(7.0);
//     enqueue(2.0);

//     traversal_print();

//     dequeue();
//     dequeue();

//     traversal_print();

//     reset_queue();

//     traversal_print();
// }

