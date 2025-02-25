


#ifndef PersistantSegmentTree_hpp
#define PersistantSegmentTree_hpp

#include<bits/stdc++.h>

using i64 = signed long long;


/*可持久化权值线段树(主席树) 模板*/

struct PersistantSegmentTree {
	struct Node {
		i64 lson, rson; i64 val;
	};

	std::vector<Node>tr;
	std::vector<i64>a, root; i64 top = 0;
	PersistantSegmentTree(i64 n): a(n), root(n), tr(n << 5) {

	}

	i64 clone(i64 p) {
		tr[++top] = tr[p];
		return top;
	}

	i64 build(i64 p, i64 l, i64 r) {
		if (not p)p = ++top;
		if (l == r) {
			tr[p].val = a[l];
			return p;
		}
		i64 mid = (l + r) >> 1;
		tr[p].lson = build(tr[p].lson, l, mid);
		tr[p].rson = build(tr[p].rson, mid + 1, r);
		return p;
	}

	i64 update(i64 p, i64 l, i64 r, i64 idx, i64 val) {
		p = clone(p);
		if (l == r) {
			tr[p].val = val;
		} else {
			i64 mid = (l + r) >> 1;
			if (idx <= mid) {
				tr[p].lson = update(tr[p].lson, l, mid, idx, val);
			} else {
				tr[p].rson = update(tr[p].rson, mid + 1, r, idx, val);
			}
		}
		return p;
	}

	i64 query(i64 p, i64 l, i64 r, i64 x) {
		if (l == r) {
			return tr[p].val;
		} else {
			i64 mid = (l + r) >> 1;
			if (x <= mid) {
				return query(tr[p].lson, l, mid, x);
			} else {
				return query(tr[p].rson, mid + 1, r, x);
			}
		}
	}
};


#endif PersistantSegmentTree_hpp