struct Mex {
    std::vector<i64>cnt; set<i64> st;
    multiset<i64> mulst;
    Mex(i64 len):cnt(len + 1, 0) {
        for (i64 i = 0; i < len; ++i) st.insert(i);
    }
    void add(i64 x) {
        //第一次添加
        if (cnt[x] == 0) {
            st.erase(x);
        }
        ++cnt[x];
        mulst.insert(x);
    }
    void del(i64 x) {
        //只剩一个了
        if (cnt[x] == 1) {
            st.insert(x);
        }
        --cnt[x];
        //不能写成mulst.erase(x) 这样是删除所有值为x的元素
        mulst.erase(mulst.find(x));
    }
    i64 mex() {
        return *st.begin();
    }
    void clear() {
        while (!mulst.empty()) {
            del(*mulst.begin());
        }
    }
};