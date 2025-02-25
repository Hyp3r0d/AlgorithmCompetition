#ifndef SplayTree_hpp
#define SplayTree_hpp

/*平衡树*/
#include<bits/stdc++.h>

using i64 = long long;


struct SplayTree {
	struct Node {
		i64 ch[2];
		i64 fa = 0; i64 lazy = 0;
		i64 val = 0; i64 cnt = 0; i64 size = 0;
	};
	vector<Node>tr;

	SplayTree(i64 n): tr(n * 2 + 5) {}


	bool get(i64 x) {
		return x == tr[tr[x].fa].ch[1];
	}
	i64 rt = 0, tot = 0;
	void update(i64 x) {
		tr[x].size = tr[tr[x].ch[0]].size + tr[tr[x].ch[1]].size + tr[x].cnt;
	}

	void clear(i64 x) {
		tr[x].ch[0] = tr[x].ch[1] = tr[x].fa = tr[x].val = tr[x].size = tr[x].cnt = tr[x].lazy = 0;
	}

	void rotate(i64 x) {
		i64 y = tr[x].fa, z = tr[y].fa, chk = get(x);
		tr[y].ch[chk] = tr[x].ch[chk ^ 1];
		if (tr[x].ch[chk ^ 1]) tr[tr[x].ch[chk ^ 1]].fa = y;
		tr[x].ch[chk ^ 1] = y;
		tr[y].fa = x;
		tr[x].fa = z;
		if (z) tr[z].ch[y == tr[z].ch[1]] = x;
		update(y);
		update(x);
	}


	void insert(i64 k) {
		if (!rt) {
			tr[++tot].val = k;
			tr[tot].cnt++;
			rt = tot;
			update(rt);
			return;
		}
		i64 cur = rt, f = 0;
		while (1) {
			if (tr[cur].val == k) {
				tr[cur].cnt++;
				update(cur);
				update(f);
				splay(cur);
				break;
			}
			f = cur;
			cur = tr[cur].ch[tr[cur].val < k];
			if (!cur) {
				tr[++tot].val = k;
				tr[tot].cnt++;
				tr[tot].fa = f;
				tr[f].ch[tr[f].val < k] = tot;
				update(tot);
				update(f);
				splay(tot);
				break;
			}
		}
	}


	/*查询值的排名*/
	i64 queryRank(i64 k) {
		i64 res = 0, cur = rt;
		while (1) {
			if (k < tr[cur].val) {
				cur = tr[cur].ch[0];
			} else {
				res += tr[tr[cur].ch[0]].size;
				if (!cur) return res + 1;
				if (k == tr[cur].val) {
					splay(cur);
					return res + 1;
				}
				res += tr[cur].cnt;
				cur = tr[cur].ch[1];
			}
		}
	}
	/*根据排名查询值*/
	i64 queryRange(i64 k) {
		i64 cur = rt;
		while (1) {
			pushdown(cur);
			if (tr[cur].ch[0] and k <= tr[tr[cur].ch[0]].size) {
				cur = tr[cur].ch[0];
			} else {
				k -= tr[cur].cnt + tr[tr[cur].ch[0]].size;
				if (k <= 0) {
					splay(cur);
					return cur;
				}
				cur = tr[cur].ch[1];
			}
		}
	}
	i64 pre() {
		i64 cur = tr[rt].ch[0];
		if (!cur) return cur;
		while (tr[cur].ch[1]) cur = tr[cur].ch[1];
		splay(cur);
		return cur;
	}

	i64 nxt() {
		i64 cur = tr[rt].ch[1];
		if (!cur) return cur;
		while (tr[cur].ch[0]) cur = tr[cur].ch[0];
		splay(cur);
		return cur;
	}

	void erase(i64 k) {
		queryRank(k);
		if (tr[rt].cnt > 1) {
			tr[rt].cnt--;
			update(rt);
			return;
		}
		if (not tr[rt].ch[0] and not tr[rt].ch[1]) {
			clear(rt);
			rt = 0;
			return;
		}
		if (!tr[rt].ch[0]) {
			i64 cur = rt;
			rt = tr[rt].ch[1];
			tr[rt].fa = 0;
			clear(cur);
			return;
		}
		if (!tr[rt].ch[1]) {
			i64 cur = rt;
			rt = tr[rt].ch[0];
			tr[rt].fa = 0;
			clear(cur);
			return;
		}
		i64 cur = rt;
		i64 x = pre();
		tr[tr[cur].ch[1]].fa = x;
		tr[x].ch[1] = tr[cur].ch[1];
		clear(cur);
		update(rt);
	}

	void splay(i64 x, i64 goal = 0) {
		if (goal == 0) rt = x;
		while (tr[x].fa != goal) {
			i64 f = tr[x].fa, g = tr[tr[x].fa].fa;
			if (g != goal) {
				if (get(f) == get(x))
					rotate(f);
				else
					rotate(x);
			}
			rotate(x);
		}
	}

	void tag(i64 x) {
		swap(tr[x].ch[0], tr[x].ch[1]);
		tr[x].lazy ^= 1;
	}

	void pushdown(i64 x) {
		if (tr[x].lazy) {
			tag(tr[x].ch[0]);
			tag(tr[x].ch[1]);
			tr[x].lazy = 0;
		}
	}
	 // 在前后各设置一个哨兵
	void reverse(i64 l, i64 r) {
		i64 L = queryRange(l - 1), R = queryRange(r + 1);
		splay(L), splay(R, L);
		i64 tmp = tr[tr[L].ch[1]].ch[0];
		tag(tmp);
	}


};


#endif SplayTree_hpp