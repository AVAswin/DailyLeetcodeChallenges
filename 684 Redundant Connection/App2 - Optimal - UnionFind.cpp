class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]); //Path Compression
    }
    // void unionByRank(int u, int v) {
    //     int ulp_u = findUPar(u);
    //     int ulp_v = findUPar(v);
    //     if (ulp_u == ulp_v) return;
    //     if (rank[ulp_u] < rank[ulp_v]) {
    //         parent[ulp_u] = ulp_v;
    //     }
    //     else if (rank[ulp_v] < rank[ulp_u]) {
    //         parent[ulp_v] = ulp_u;
    //     }
    //     else {
    //         parent[ulp_v] = ulp_u;
    //         rank[ulp_u]++;
    //     }
    // }
    bool unionBySize(int u, int v) {
        int rootU = findUPar(u);
        int rootV = findUPar(v);
        if (rootU == rootV) return true; //cycle exists
        if (size[rootU] < size[rootV]) {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        }
        else {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
        return false;
    }
};
// Since there are n Nodes and n Edges, there exists a cycle.
// So no need to take concern of the 1st condtion
// just find which edge on addtion forms the cycle- DisjointSet data structure 
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        DisjointSet ds(n);
        vector<int> result;

        for(auto it : edges) {
            int node1 = it[0];
            int node2 = it[1];
            if(ds.unionBySize(node1, node2)) {
                result = {node1, node2};
                break;
            }
        }
        return result;
    }
};