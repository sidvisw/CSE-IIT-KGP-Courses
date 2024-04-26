#include <stdio.h> 
#include <stdlib.h>


//---QUEUE---------------------------------------------
typedef struct {
    int *Arr ;
    int queue_size, start_id, end_id;
}QUEUE;

void init(QUEUE *qP, int size){//allocates space for queue
    qP->Arr = (int *)malloc(size*sizeof(int));
    qP->start_id = 0;
    qP->end_id = -1;
    qP->queue_size = 0;
}

int isempty(QUEUE qP){//returns 1 if the queue is empty, else 0
    return (qP.queue_size == 0);
}

void enqueue(QUEUE *qP, int data){
    qP->end_id++;
    qP->Arr[qP->end_id] = data;
    qP->queue_size++;
}

int dequeue(QUEUE *qP){
    if(qP->queue_size == 0){
        perror("Trying to dequeue empty queue");
        exit(-1);
    }
    qP->start_id++;
    qP->queue_size--;
    return qP->Arr[qP->start_id-1];
}

void display_q(QUEUE *qP){
    for (int i = qP->start_id ; i <= qP->end_id ; i++){
        if (i < qP->end_id)
        printf("%d,",qP->Arr[i]);
        else
        printf("%d",qP->Arr[i]);
    }
}

void max_node(QUEUE *qP,int** adj_mat,int n){
    int count = 0;
    int new_edge_add[n][n];
    for (int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            new_edge_add[i][j] = 0;
        }
    }
    for (int i = qP->start_id ; i <= qP->end_id ; i++){
        for (int j = i+1 ; j < n ; j++){
            if (adj_mat[qP->Arr[i]][qP->Arr[j]] == 0){
                count += 1;
                new_edge_add[qP->Arr[i]][qP->Arr[j]] = 1;
            }
        }
    }
    printf("\n%d\n",count);
    for (int i = 0; i < n ; i++){
        for(int j = 0;j < n; j++){
            if (new_edge_add[i][j] == 1)
            printf("%d  %d\n",i,j);
        }
    }
}

int strategy1(int total_node,int** adj_mat, QUEUE *z_q, QUEUE *r_q){
    int node_visited = 0;
    int *degree = (int *)malloc((total_node) * sizeof(int));
    for(int i=0; i < total_node; i++){
        degree[i] = 0;
    }
    for (int i = 0; i < total_node;i++){
        int tmp_degree = 0;
        for (int j = 0 ; j< total_node; j++){
            if (adj_mat[j][i] == 1)
                tmp_degree += 1;
        }
        degree[i] = tmp_degree;
    }
    for (int i = 0; i < total_node;i++){
        if (degree[i] == 0)
            enqueue(z_q, i);    
    }
    while (!isempty(*z_q)){
        int zero = dequeue(z_q);
        node_visited += 1;
        //printf("%d\n",zero);
        enqueue(r_q,zero);
        for (int j = 0; j < total_node ; j++) {
            if (adj_mat[zero][j] == 1 && !--degree[j])
                enqueue(z_q,j);
        }
    }
    if (total_node != node_visited)
    return 1;
    return 0;
}

int main(){

    //Please read the comment on line 11 and line 110
    int n, m;
    scanf("%d %d", &n, &m); 

    int **adj_mat;
    adj_mat = (int **)malloc((n) * sizeof(int *));
    for(int i=0; i<n; i++)
        adj_mat[i] = (int *)malloc((n) * sizeof(int));
    
    for (int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            adj_mat[i][j] = 0;
        }
    }
    int x,y;
    for(int i=0; i<m; i++){
        scanf("%d %d", &x,&y);
        adj_mat[x][y] = 1;
    }

    
    QUEUE *zero_qp=(QUEUE *)malloc(sizeof(QUEUE));
    init(zero_qp,1000);
    QUEUE *result_qp=(QUEUE *)malloc(sizeof(QUEUE));
    init(result_qp,1000);

    if (strategy1(n, adj_mat, zero_qp, result_qp))
        printf("cycle\n");
    else{
        display_q(result_qp);
        max_node(result_qp,adj_mat,n);
    }    
    return 0;
}

