// Diameter of a tree: https://codeforces.com/blog/entry/101271
// sample submission: https://codeforces.com/contest/2134/submission/335741610

struct TreeDiameter{
    int n;
    vector< vector<int> > L;
    vector<bool> visited;
    vector<int> prev;

    TreeDiameter(int _n){
        n = _n;
        L = vector< vector<int> >(n);
        visited = vector<bool>(n);
        prev = vector<int>(n);
    }

    void add_edge(int u, int v){
        assert(u >= 0 && u < n);
        assert(v >= 0 && v < n);
        L[u].push_back(v);
        L[v].push_back(u);
    }

    int most_distant(int s){
        fill(visited.begin(), visited.end(), false);
        queue<int> Q;
        Q.push(s);
        visited[s] = true;
        prev[s] = -1;
        int ans = s;

        while(!Q.empty()){
            int cur = Q.front();
            Q.pop();
            ans = cur;

            for(int to : L[cur]){
                if(!visited[to]){
                    visited[to] = true;
                    Q.push(to);
                    prev[to] = cur;
                }
            }
        }

        return ans;
    }

    vector<int> get_diameter(){
        int s = most_distant(0);
        int e = most_distant(s);
        vector<int> ret;
        while(e != s){
            ret.push_back(e);
            e = prev[e];
        }
        ret.push_back(s);
        return ret;
    }
};