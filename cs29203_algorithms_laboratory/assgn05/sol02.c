/*
*       Author: Soumya Sharma
*       Problem: Algo Lab 5 2021 IIT KGP
*/

#include <stdio.h>
#include <stdlib.h>
 
// For Queue Size
#define SIZE 5000

// Pre-defined min, max functions
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

// A tree node
struct node {
    int data;
    struct node *right,*left;
};
 
// A queue node
struct Queue {
    int front, rear;
    int size;
    struct node* *array;
};
 
// A utility function to create a new tree node
struct node* newNode(int data) {
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
 
// A utility function to create a new Queue
struct Queue* createQueue(int size) {
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    int i;
    queue->front = queue->rear = -1;
    queue->size = size;
 
    queue->array = (struct node**) malloc(queue->size * sizeof( struct node* ));
 
    for (i = 0; i < size; ++i)
        queue->array[i] = NULL;
 
    return queue;
}
 
int isEmpty(struct Queue* queue) {
    return queue->front == -1; }
 
int isFull(struct Queue* queue){
    return queue->rear == queue->size - 1; }
 
int hasOnlyOneItem(struct Queue* queue){
    return queue->front == queue->rear;  }
 
void Enqueue(struct node *root, struct Queue* queue) {
    if (isFull(queue))
        return;
 
    queue->array[++queue->rear] = root;
 
    if (isEmpty(queue))
        ++queue->front;
}
 
struct node* Dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return NULL;
 
    struct node* temp = queue->array[queue->front];
 
    if (hasOnlyOneItem(queue))
        queue->front = queue->rear = -1;
    else
        ++queue->front;
 
    return temp;
}
 
struct node* getFront(struct Queue* queue) {
    return queue->array[queue->front]; }
 
int hasBothChild(struct node* temp) {
    return temp && temp->left && temp->right; }
 
void insert(struct node **root, int data, struct Queue* queue) {
    // Create a new node for given data
    struct node *temp = newNode(data);

    // If the tree is empty, initialize the root with new node.
    if (!*root)
        *root = temp;
    else {
        // get the front node of the queue.
        struct node* front;
        front = getFront(queue);
        while (front->data == -1) {
            Dequeue(queue);
            front = getFront(queue);
        } 
        // If the left child of this front node doesnt exist, set the
        // left child as the new node
        if (!front->left)
            front->left = temp;
 
        // If the right child of this front node doesnt exist, set the
        // right child as the new node
        else if (!front->right)
            front->right = temp;
 
        // If the front node has both the left child and right child,
        // Dequeue() it.
        // Here we check if any left or right child has -1 as value, we set it to NULL
        // We do this because in our input, we state that -1 represents no node.
        if (hasBothChild(front)){
            if (front->left->data == -1 ) {
                front->left = NULL;
            }
            if (front->right->data == -1 ) {
                front->right = NULL;
            }
            Dequeue(queue);
        }
    }
 
    // Enqueue() the new node for later insertions
    Enqueue(temp, queue);
}

void levelOrder(struct node* root) {
    struct Queue* queue = createQueue(SIZE);
 
    Enqueue(root, queue);
 
    while (!isEmpty(queue))
    {
        struct node* temp = Dequeue(queue);
 
        printf("%d ", temp->data);
 
        if (temp->left)
            Enqueue(temp->left, queue);
 
        if (temp->right)
            Enqueue(temp->right, queue);
    }
    printf("\n");
}

int dfs(struct node* root, int* cameras){
    if(!root) return 1;
    int left = dfs(root->left, cameras);
    int right = dfs(root->right, cameras);
    
    if(left == 1 && right == 1)
        return 2;
    
    if(left == 2 || right == 2)
    {
        *cameras += 1;
        return 0;
    }
    
    return 1;
}

int minCameraCover(struct node* root, int* cameras) {
    int top = dfs(root, cameras);
    return *cameras + (top == 2 ? 1 : 0);
}

// Driver program to test above functions
int main()
{
    int i, T;
    scanf("%d", &T);
    for (int idx=1; idx <= T; idx++) {
        int m, luke, leia, threshold;
        struct node* root = NULL;
        struct Queue* queue = createQueue(SIZE);
        scanf("%d",&m);
        int *array=(int*)malloc(m*sizeof(int));
        for(i=0;i<m;i++) {
            scanf("%d", &array[i]);
        }
        for(i = 0; i < m; ++i){ insert(&root, array[i], queue); }

        printf("Case #%d: ", idx);
        int cameras = 0;
        printf("%d\n", minCameraCover(root, &cameras));
    }
   return 0;
}