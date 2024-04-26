#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef struct Node {
    int v;
    int l;
    Node* next;
} Node, *nodeList, **adjList;

struct Tree {
    int N;
    adjList nodes;
};

struct branch {
    int u, v, l;
};

struct Edge {
    int w;
    int to;
};

Node *newNode(int v, int l) {
    Node *nnode = new Node;
    nnode->v = v;
    nnode->l = l;
    nnode->next = NULL;

    return nnode;
}

Tree *createTree(int N) {
    Tree *tree = new Tree;
    tree->N = N;

    tree->nodes = new nodeList[N];

    for(int i = 0; i < N; i++) {
        tree->nodes[i] = NULL;
    }

    return tree;
}

void addEdge(Tree *t, int u, int v, int l) {
    Node *nnode = newNode(v, l);
    nnode->next = t->nodes[u];
    t->nodes[u] = nnode;

    nnode = newNode(u, l);
    nnode->next = t->nodes[v];
    t->nodes[v] = nnode;

    return;
}

int max_mst(int n, int **adj, branch *tree) {
    int total_power = 0;
    bool visited[n];
    Edge max_edge[n];

    int idx = 0;
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        max_edge[i].w = -1;
        max_edge[i].to = -1;
    }
    max_edge[0].w = 2e9;

    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (v == -1 || max_edge[j].w > max_edge[v].w))
                v = j;
        }

        visited[v] = true;
        int u = max_edge[v].to;
        if (u != -1) {
            total_power += max_edge[v].w;
            tree[idx++] = {v, u, adj[v][u]};
        }

        for (int to = 0; to < n; ++to) {
            if (!visited[to] && adj[v][to] > max_edge[to].w) {
                max_edge[to] = {adj[v][to], v};
            }
        }
    }

    return total_power;
}

int dfs(int u, int p, int f, Tree *tree) {
    if(u == f) {
        return 1001;
    }

    int minv = -1;
    Node *child = tree->nodes[u];
    while(child != NULL) {
        if (p != child->v) {
            int val = dfs(child->v, u, f, tree);
            if (val != -1) {
                minv = min(val, child->l);
                break;
            }
        }
        child = child->next;
    }

    return minv;
}

int main() {
    // freopen("input/input14.txt", "r", stdin);
    // freopen("output/output14.txt", "w", stdout);

    auto start = high_resolution_clock::now();

    int N, Q;
    cin >> N >> Q;
    int M = (N * (N - 1)) / 2;
    
    int **adj = new int*[N];
    for(int i = 0; i < N; i++) {
        adj[i] = new int[N];
    }

    for(int i = 0; i < M; i++) {
        int tu, tv, luv;
        cin >> tu >> tv >> luv;
        tu--, tv--;

        adj[tu][tv] = adj[tv][tu] = luv;
    }

    branch *tree = new branch[N - 1];
    int ans = max_mst(N, adj, tree);
    cout << ans << endl;

    // construct the MST
    Tree *t = createTree(N);
    for(int i = 0; i < N - 1; i++) {
        addEdge(t, tree[i].u, tree[i].v, tree[i].l);
    }

    /*
    Another approach is possible here which allows query processing in O(1). 
    Glad that a lot of you did that solution!

    I have presented the below solution to suggest an alternative method. Each query takes O(N) here. 
    This approach will be better if queries are not independent and MST changes after each query.
    */
    while(Q--) {
        int tui, tvi, xi;
        cin >> tui >> tvi >> xi;
        tui--, tvi--;

        // check if edge is in MST
        bool exists = false;
        int old_len = -1;
        for(int i = 0; i < N - 1; i++) {
            if(tui == tree[i].u && tvi == tree[i].v) {
                exists = true;
                old_len = tree[i].l;
                break;
            }
            else if(tui == tree[i].v && tvi == tree[i].u) {
                exists = true;
                old_len = tree[i].l;
                break;
            }
        }

        if(exists) {
            // the edge already exists so just update the length
            cout << ans - old_len + xi << endl;
        }
        else {
            // find the edge with minimum length on the path tui -- tvi in MST and remove it if not optimal
            // and add the edge tui - tvi to maximize the power!
            int len = dfs(tui, -1, tvi, t);
            if (len < xi) {
                cout << ans - len + xi << endl;
            }
            else {
                cout << ans << endl;
            }
        }
    }

    // free allocated memory
    delete[] tree;
    
    for(int i = 0; i < N; i++) {
        Node *current = t->nodes[i];
        Node *next;

        while (current != NULL)
        {
            next = current->next;
            delete current;
            current = next;
        }
        t->nodes[i] = NULL;
    }
    delete[] t->nodes;
    delete t;
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cerr << "Time taken by function: " << 1.0*duration.count() / 1000000 << " seconds" << endl;

    return 0;
}