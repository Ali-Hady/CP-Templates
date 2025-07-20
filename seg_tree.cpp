struct Node {
    ll val;
    ll lazy;

    Node(ll v = 0, ll l = LLONG_MAX) : val(v), lazy(l) {}
};

struct SegmentTree {
    vector<Node> tree;
    int size;
    const Node IDENTITY;

    Node merge(const Node& a, const Node& b) {
        return Node(a.val + b.val, IDENTITY.lazy);
    }

    SegmentTree(const vector<ll>& arr) {
        size = 1;
        while(size < arr.size()) size <<= 1;
        tree.resize(2 * size, IDENTITY);
        build(arr, 1, 0, size - 1);
    }

    void build(const vector<ll>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = Node((l < arr.size()) ? arr[l] : IDENTITY);
            return;
        }

        int mid = (l + r) / 2;
        build(arr, 2*node, l, mid);
        build(arr, 2*node+1, mid+1, r);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

    void propagate(int node, int l, int r) {
        if (tree[node].lazy == IDENTITY.lazy) return;

        tree[node].val = tree[node].lazy * (r - l + 1);

        if(l != r) {
            tree[2*node].lazy = tree[node].lazy;
            tree[2*node+1].lazy = tree[node].lazy;
        }

        tree[node].lazy = IDENTITY.lazy;
    }

    void modify(int ql, int qr, ll val, int node, int l, int r) {
        propagate(node, l, r);
        if(qr < l || ql > r) return;
        if(ql <= l && r <= qr) {
            tree[node].lazy = val;
            propagate(node, l, r);
            return;
        }

        int mid = (l + r)/2;
        modify(ql, qr, val, 2*node, l, mid);
        modify(ql, qr, val, 2*node+1, mid+1, r);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

    void update(int idx, ll val, int node, int l, int r) {
        propagate(node, l, r);
        if(l == r) {
            tree[node].val = val;
            return;
        }

        int mid = (l + r)/2;
        if(idx <= mid) update(idx, val, 2*node, l, mid);
        else update(idx, val, 2*node+1, mid+1, r);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

    Node query(int ql, int qr, int node, int l, int r) {
        propagate(node, l, r);
        if(qr < l || ql > r) return IDENTITY;
        if(ql <= l && r <= qr) return tree[node];

        int mid = (l + r)/2;
        return merge(query(ql, qr, 2*node, l, mid),query(ql, qr, 2*node+1, mid+1, r));
    }

    // Wrapper functions
    void modify(int l, int r, ll val) { modify(l, r, val, 1, 0, size-1); }
    void update(int idx, ll val) { update(idx, val, 1, 0, size-1); }
    Node query(int l, int r) { return query(l, r, 1, 0, size-1); }
};