struct Mex {
    int cnt[maxn]; set<int> st;
    multiset<int> mulst;
    Mex() {
        for (int i = 0; i < maxn; ++i) cnt[i] = 0;
        for (int i = 0; i < maxn; ++i) st.insert(i);
    }
    void add(int x) {
        //第一次添加
        if (cnt[x] == 0) {
            st.erase(x);
        }
        ++cnt[x];
        mulst.insert(x);
    }
    void del(int x) {
        //只剩一个了
        if (cnt[x] == 1) {
            st.insert(x);
        }
        --cnt[x];
        //不能写成mulst.erase(x) 这样是删除所有值为x的元素
        mulst.erase(mulst.find(x));
    }
    int mex() {
        return *st.begin();
    }
    void clear() {
        while (!mulst.empty()) {
            del(*mulst.begin());
        }
    }
};