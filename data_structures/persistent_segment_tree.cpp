// sample submission: https://atcoder.jp/contests/abc453/submissions/74928788
template<typename T>
struct PersistentSegmentTree{
    static const int MAX_NODES = 4500000;
    struct Node{
        T sum;
        int l,r;
    }tree[MAX_NODES];

    int n,node_count = 0;

    int copy_node(int old_node){
        int new_node = ++node_count;
        tree[new_node] = tree[old_node];
        return new_node;
    }

    PersistentSegmentTree(int n) : n(n){
        init(0, 0, n - 1);
    }

    void init(int node, int l, int r){
        if(l == r){
            tree[node].sum = 0;
            return;
        }
        int mi = (l + r) >> 1;
        ++node_count;
        tree[node].l = node_count;
        init(node_count, l, mi);
        ++node_count;
        tree[node].r = node_count;
        init(node_count, mi + 1, r);
        tree[node].sum = tree[tree[node].l].sum + tree[tree[node].r].sum;
    }

    int update(int node, int idx, T val){
        return update(node, 0, n - 1, idx, val);
    }

    int update(int node, int l, int r, int idx, T val){
        int cur = copy_node(node);
        if(l == r){
            tree[cur].sum = val;
            return cur;
        }
        int mi = (l + r) >> 1;
        if(idx <= mi){
            tree[cur].l = update(tree[cur].l, l, mi, idx, val);
        }else{
            tree[cur].r = update(tree[cur].r, mi + 1, r, idx, val);
        }
        tree[cur].sum = tree[tree[cur].l].sum + tree[tree[cur].r].sum;
        return cur;
    }

    T query(int node, int ql, int qr){
        return query(node, 0, n - 1, ql, qr);
    }

    T query(int node, int l, int r, int ql, int qr){
        if(l > qr || r < ql) return 0;
        if(ql <= l && r <= qr) return tree[node].sum;
        int mi = (l + r) >> 1;
        return query(tree[node].l, l, mi, ql, qr) + query(tree[node].r, mi + 1, r, ql, qr);
    }
};