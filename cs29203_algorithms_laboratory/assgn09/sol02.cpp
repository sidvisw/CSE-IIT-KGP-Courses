#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct branch {
    int u, v, l;
};

void merge(int start, int mid, int end, branch* edges) {
    int i = 0, j = 0, k = 0;

    branch *tmp = new branch[end - start + 1];
    while(k < end - start + 1) {
        tmp[k] = edges[start + k];
        k++;
    }

    k = 0;
    while(i < mid - start + 1 && j < end - mid) {
        if(tmp[i].l <= tmp[mid - start + 1 + j].l) {
            edges[start + k] = tmp[i];
            i++; 
        }
        else {
            edges[start + k] = tmp[mid - start + 1 + j];
            j++;
        }
        k++;
    }

    while(i < mid - start + 1) {
        edges[start + k] = tmp[i];
        i++, k++;
    }

    while(j < end - mid) {
        edges[start + k] = tmp[mid - start + 1 + j];
        j++, k++;
    }

    delete[] tmp;
    return;
}

void sort_edges(int start, int end, branch *edges) {
    if (start >= end) return;

    int mid = (start + end) / 2;
    sort_edges(start, mid, edges);
    sort_edges(mid + 1, end, edges);

    merge(start, mid, end, edges);

    return;
}

int findset(int u, int *parent) {
    if (u == parent[u]) return u;
    return parent[u] = findset(parent[u], parent);
}

void mergeset(int u, int v, int *parent, int *sz) {
    u = findset(u, parent);
    v = findset(v, parent);

    if (u == v) return;

    if (sz[u] > sz[v]) {
        parent[v] = u;
        sz[u] += sz[v];
    }
    else {
        parent[u] = v;
        sz[v] += sz[u];
    }
    
    return;
}

void min_mst(int N, int M, int C, branch *edges) {  
    sort_edges(0, M - 1, edges);

    int *parent = new int[N];
    int *sz = new int[N];

    for(int i = 0; i < N; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    int resettingCost = 0, j = 0;
    for(int i = 0; i < M && j < N - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int l = edges[i].l;

        // only include edges with lower cost
        if(l > C) break;

        if(findset(u, parent) == findset(v, parent)) continue;
        mergeset(u, v, parent, sz);

        resettingCost += l;
        j++;
    }

    // find out the number of components now
    int numResetCharges = 0;
    for(int i = 0; i < N; i++) {
        if(parent[i] == i) numResetCharges++;
    }

    // for each component 1 reset charge is needed
    int overallCost = resettingCost + numResetCharges * C;

    cout << overallCost << " " << numResetCharges << endl;

    delete[] parent;
    delete[] sz;

    return;
}

int32_t main() {
    // freopen("input/input07.txt", "r", stdin);
    // freopen("output/output07.txt", "w", stdout);

    auto start = high_resolution_clock::now();

    int T;
    cin >> T;

    while(T--) {
        int N, M, C;
        cin >> N >> M >> C;
        
        branch* edges = new branch[M];
        for(int i = 0; i < M; i++) {
            int tu, tv, luv;
            cin >> tu >> tv >> luv;
            tu--, tv--;

            edges[i] = {tu, tv, luv};
        }

        min_mst(N, M, C, edges);

        delete[] edges;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cerr << "Time taken: " << 1.0*duration.count() / 1000000 << " seconds" << endl;

    return 0;
}