// Since there are n Nodes and n Edges, there exists a cycle.
// So no need to take concern of the 1st condtion
// just find which edge on addtion forms the cycle- DFS or BFS - Brute Approach
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> adj[n+1];
        vector<int> vis(n+1, 0);

        vector<int> ans(2, 0);
        for(auto it : edges) {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
            if(dfsDetectCycleInUnDirectedGraph(it[1], -1, adj, vis, ans)) {
                // it[1] should be passed, else ans order will be changed
                break;
            }
        }
        return ans;
    }

private:
    bool dfsDetectCycleInUnDirectedGraph(int node, int parent,
    vector<int> adj[], vector<int> &vis, vector<int> &ans) {
        vis[node] = 1;  // Mark node as visited

        for(auto it : adj[node]) {
            if(!vis[it]) {
                if(dfsDetectCycleInUnDirectedGraph(it, node, adj, vis, ans) == true) 
                    return true;
            }
            else if(it != parent) {
                ans[0] = node;
                ans[1] = it;
                return true; // Cycle detected
            }
        }
        vis[node] = 0; // line to be inserted in cycle dectection in UG - DFS
        // backtrack -- as new DFS calls needs to be made after each addition of edges
        return false;
    }
};