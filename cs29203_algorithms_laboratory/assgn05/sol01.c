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

struct node* lowestCommonAncestorRecursively(struct node* root, struct node* node1, struct node* node2) {
    // If current node value is more than node1 and node2 value,
    // then both nodes lie on left subtree and ancestor would also be found there.
    if (root->data > node1->data && root->data > node2->data){
        return lowestCommonAncestorRecursively(root->left, node1, node2);
    }
    // If current node value is less than node1 and node2 value,
    // then both nodes lie on right subtree and ancestor would also be found there.
    else if(root->data < node1->data && root->data < node2->data){
        return lowestCommonAncestorRecursively(root->right, node1, node2);
    }
    // This current node is ancestor
    else{
        return root;
    }
}

struct node* lowestCommonAncestorIteratively(struct node* root, struct node* node1, struct node* node2) {
    int min, max;
    // Getting min and max values out of node1 and node2
    if (node1->data < node2->data) {
        min = node1->data;
        max = node2->data;
    } else {
        min = node2->data;
        max = node1->data;
    }
    while (root) {
        // Current node is ancestor
        if (root->data >= min && root->data <= max) {
            return root;
        }
        if (root->data < min) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return root;
}

struct node* findNodeRecursively(struct node* root, int data) {
    if (!root) {
        return NULL;
    }
    if (root->data == data) {
        return root;
    } else if (root-> data < data) {
        return findNodeRecursively(root->right, data);
    } else {
        return findNodeRecursively(root->left, data);
    }
}

struct node* findNodeIteratively(struct node* root, int data) {
    while (root) {
        if (data == root->data) {
            return root;
        } else if (data > root->data) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return NULL;
}

// Function to find a suitable node where sum of damage on level < threshold
int findSuitableNode(struct node* root, struct node* toFind, int sum[], int height, int threshold) {
    if (!root) {
        return 0;
    }
    int child;
    if (root->data == toFind->data) {
        if (sum[height] < threshold) {
            return root->data;
        } else {
            return -1;
        }
    } else if (root-> data < toFind->data) {
        child = findSuitableNode(root->right, toFind, sum, height + 1, threshold);
    } else {
        child = findSuitableNode(root->left, toFind, sum, height + 1, threshold);
    }
    if (child == -1) {
        if (sum[height] < threshold) {
            return root->data;
        } else {
            return -1;
        }
    } else {
        return child;
    }
}

int findHeightOfNode(struct node* root, struct node* toFind) {
    if(!root) {
        return -1;
    }
    if (root == toFind) {
        return 0;
    } else if (root->left->data < toFind->data) {
        return (findHeightOfNode(root->right, toFind) + 1);
    } else {
        return (findHeightOfNode(root->left, toFind) + 1);
    }
}

int getHeightOfTreeRecursively(struct node* root) {
    if (!root->left && !root->right) {
        return 0;
    }
    int left;
    if(root->left) {
        left = getHeightOfTreeRecursively(root->left);
    }
    int right;
    if(root->right) {
        left = getHeightOfTreeRecursively(root->right);
    }
    return (MAX(left, right) + 1);
}

// Start from root and add 1 for each recursive call. For each node on a level, add the damage of that
// node to sum of that level
void calculateLevelSum(struct node* node, int level, int sum[])
{
    if (!node)
        return;
 
    // Add current node data to the sum
    // of the current nodes level
    sum[level] += node->data;
 
    // Recursive call for left and right sub-tree
    calculateLevelSum(node->left, level + 1, sum);
    calculateLevelSum(node->right, level + 1, sum);
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
        scanf("%d %d %d", &luke, &leia, &threshold);
        for(i = 0; i < m; ++i){ insert(&root, array[i], queue); }

        printf("Case #%d: ", idx);
        struct node* lukeNode = findNodeRecursively(root, luke);
        struct node* leiaNode = findNodeRecursively(root, leia);
        if (lukeNode == NULL || leiaNode == NULL) {
            printf("-1\n");
            continue;
        }
        struct node* front = lowestCommonAncestorRecursively(root, lukeNode, leiaNode);
        printf("%d ", front->data);
        int height = findHeightOfNode(root, front);
        printf("%d ", height);
        int levels = getHeightOfTreeRecursively(root) + 1;
        int *sum=(int*)malloc(levels*sizeof(int));
        sum[0] = 0;
        // Sum of nodes on level can be pre-stored and does not need to be computed each time
        calculateLevelSum(root, 0, sum);
        printf("%d ", sum[height]);
        int suitable = findSuitableNode(root, front, sum, 0, threshold);
        if (suitable == -1) {
            printf("Trapped!\n");
        } else {
            printf("Escaped! %d\n", suitable);
        }
    }
    return 0;
}