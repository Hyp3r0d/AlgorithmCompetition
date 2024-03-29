

struct HLD {


public:

    i64 sz[maxn], son[maxn], top[maxn], rk[maxn], w[maxn], dfn[maxn];
    i64 cnt = 0; dep[maxn], fa[maxn];

    struct Node {
        i64 l, r, sum, add;
    };
    std::vector<Node>tr;
    std::vector<std::vector<i64>>g;
    void dfs1(i64 u, i64 f) {
        dep[u] = dep[f] + 1;
        fa[u] = f;
        son[u] = -1, sz[u] = 1;
        for (auto v : g[u]) {
            if (v == f)continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if (son[u] == -1 or sz[v] > sz[son[u]]) {
                son[u] = v;
            }
        }
    }

    void dfs2(i64 u, i64 t) {
        top[u] = t;
        cnt++; dfn[u] = cnt;
        rk[cnt] = u;
        if (son[u] == -1)return;
        dfs2(son[u], t);
        for (auto v : g[u]) {
            if (v == fa[u])continue;
            if (v == son[u])continue;
            dfs2(v, v);
        }
    }

    void pushUp(i64 p) {
        tr[p].sum = (tr[p << 1].sum % P + tr[p << 1 | 1].sum % P) % P;
    }

    void build(i64 p, i64 l, i64 r) {
        tr[p].l = l; tr[p].r = r;
        if (l == r) {
            tr[p].sum = w[rk[l]];
            return;
        }
        i64 mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushUp(p);
    }


    void pushDown(i64 p) {
        i64 ad = tr[p].add;
        tr[p].add = 0;
        tr[p << 1].add = (tr[p << 1].add % P + ad) % P;
        tr[p << 1 | 1].add = (tr[p << 1 | 1].add % P + ad) % P;
        i64 len1 = (tr[p << 1].r - tr[p << 1].l + 1);
        i64 len2 = (tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1);
        tr[p << 1].sum = (tr[p << 1].sum % P + len1 % P * ad % P) % P;
        tr[p << 1 | 1].sum = (tr[p << 1 | 1].sum % P + len2 % P * ad % P) % P;
    }

    void add(i64 p, i64 l, i64 r, i64 v) {
        if (tr[p].l >= l and tr[p].r <= r) {
            tr[p].add = (tr[p].add % P + v) % P;
            tr[p].sum = (tr[p].sum % P + (tr[p].r - tr[p].l + 1) % P * v % P) % P;
            return;
        }
        pushDown(p);
        i64 mid = (tr[p].l + tr[p].r) >> 1;
        if (l <= mid) {
            add(p << 1, l, r, v);
        }
        if (r > mid) {
            add(p << 1 | 1, l, r, v);
        }
        pushUp(p);
    }


    i64 query(i64 p, i64 l, i64 r) {
        if (tr[p].l >= l and tr[p].r <= r) {
            return tr[p].sum;
        }
        i64 ret = 0;
        pushDown(p);
        i64 mid = (tr[p].l + tr[p].r) >> 1;;
        if (r > mid) {
            ret = (ret % P + query(p << 1 | 1, l, r)) % P;
        }
        if (l <= mid) {
            ret = (ret % P + query(p << 1, l, r)) % P;
        }
        return ret % P;
    }



    i64 querySum(i64 x, i64 y) {
        i64 ret = 0, fx = top[x], fy = top[y];
        while (fx != fy) {
            if (dep[fx] >= dep[fy]) {
                ret = (ret % P + query(1, dfn[fx], dfn[x])) % P;
                x = fa[fx];
            } else {
                ret = (ret % P + query(1, dfn[fy], dfn[y])) % P;
                y = fa[fy];
            }
            fx = top[x], fy = top[y];
        }
        if (dfn[x] < dfn[y]) {
            ret = (ret % P + query(1, dfn[x], dfn[y])) % P;
        } else {
            ret = (ret % P + query(1, dfn[y], dfn[x])) % P;
        }
        return ret % P;
    }


    void change(i64 x, i64 y, i64 v) {
        i64 fx = top[x], fy = top[y];
        while (fx != fy) {
            if (dep[fx] >= dep[fy]) {
                add(1, dfn[fx], dfn[x], v);
                x = fa[fx];
            } else {
                add(1, dfn[fy], dfn[y], v);
                y = fa[fy];
            }
            fx = top[x], fy = top[y];
        }
        if (dfn[x] < dfn[y]) {
            add(1, dfn[x], dfn[y], v);
        } else {
            add(1, dfn[y], dfn[x], v);
        }
    }
};
