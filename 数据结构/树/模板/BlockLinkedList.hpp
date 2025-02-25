

#ifndef BlockLinkedList_hpp
#define BlockLinkedList_hpp




#include<bits/stdc++.h>

using i64 = long long;



/*块状链表*/
template<typename T>
struct BlockLinkedList {
public:
	i64 sqn; i64 length; // 块长

	struct Node {
		std::vector<T> d;
		Node * next;
		Node() {
			next = nullptr;
		}
		void append(T c) {
			d.push_back(c);
		}
		i64 size() {
			return d.size();
		}
	};
	Node *head = nullptr;
	BlockLinkedList(i64 len): sqn(len), length(0) {
		head = new Node();
	}
	BlockLinkedList(): length(0) {
		head = new Node(); sqn = 1e3;
	}
	void split(Node *p) { // 节点分裂
		if (p->size() >= (sqn << 1)) {
			Node*q = new Node();
			for (i64 i = sqn; i < p->size(); i++) {
				q->append(p->d[i]);
			}
			q->next = p->next; p->next = q;
		}
	}
	void insert(T c, i64 position) {
		Node *p = head;
		i64 tot = 0;
		if (position > this->length) {
			this->length++;
			while (p->next != nullptr) {
				p = p->next;
			}
			p->append(c); this->split(p);
			return;
		}
		this->length++;
		for (tot = head->size(); p != nullptr and tot < position; p = p->next, tot += p->size());
		
		tot -= p->size(); i64 cnt = position - tot - 1;
		p->append(T());
		for (i64 i = p->size() - 2; i >= cnt; i--)p->d[i + 1] = p->d[i];
		p->d[cnt] = c;
		this->split(p);
	}
	T query(i64 position) {
		Node *p; i64 tot = 0;
		for (p = head, tot = head->size(); p != nullptr and tot < position; p = p->next, tot += p->size());
		tot -= p->size();
		return p->d[position - tot - 1];
	}

};

#endif BlockLinkedList_hpp

