#ifndef PartitialArray_hpp
#define PartitialArray_hpp


struct PartitialArray {
public:
    i64 blockLength, totalLength, totalBlocks;
    std::vector<i64>blockStart, blockEnd, array, backArray , belong, lazy;

    void build() {
        for (i64 i = 1; i <= totalBlocks; i++) {
            blockStart[i] = (i - 1) * blockLength + 1;
            blockEnd[i] = i * blockLength;
        }
        blockEnd[totalBlocks] = totalLength;

        for (i64 i = 1; i <= totalLength; i++) {
            belong[i] = (i + blockLength - 1) / blockLength;
        }

        for (i64 i = 1; i <= totalBlocks; i++) {
            resort(i);
        }
    }

    void pushDown(i64 idx) {
        if (lazy[idx] != inf) {
            for (i64 i = blockStart[idx]; i <= blockEnd[idx]; i++)array[i] = backArray[i] = lazy[idx];
            lazy[idx] = inf;
        }
    }

    void modify(i64 l, i64 r, i64 c) {
        i64 x = belong[l], y = belong[r];
        pushDown(x);
        if (x == y) {
            for (i64 i = l; i <= r; i++)array[i] = c;
            resort(x);
            return;
        }
        pushDown(y);
        for (i64 i = l; i <= blockEnd[x]; i++)array[i] = c;
        for (i64 i = blockStart[y]; i <= r; i++)array[i] = c;
        resort(x); resort(y);
        for (i64 i = x + 1; i <= y - 1; i++)lazy[i] = c;
    }

    i64 query(i64 l, i64 r, i64 c) {
        i64 ans = 0; i64 x = belong[l], y = belong[r];
        pushDown(x);
        if (x == y) {
            for (i64 i = l; i <= r; i++)if (array[i] <= c)ans++;
            return ans;
        }
        pushDown(y);
        for (i64 i = l; i <= blockEnd[x]; i++)if (array[i] <= c)ans++;
        for (i64 i = blockStart[y]; i <= r; i++)if (array[i] <= c)ans++;
        for (i64 i = x + 1; i <= y - 1; i++) {
            if (lazy[i] == inf)ans += upper_bound(d.begin() + blockStart[i], d.begin() + blockEnd[i] + 1, c) - d.begin() - 1;
            else if (lazy[i] <= c)ans += blockEnd[i] - blockStart[i] + 1;
        }
        return ans;
    }

    void resort(i64 idx) {
        for (i64 i = blockStart[idx]; i <= blockEnd[idx]; i++) {
            backArray[i] = array[i];
        }
        std::sort(backArray.begin() + blockStart[idx], backArray.begin() + blockEnd[idx] + 1);
    }



    PartitialArray(std::vector<i64>a, i64 n): totalLength(n), blockLength(sqrt(n)),
        totalBlocks((totalLength + blockLength - 1) / blockLength), blockStart(totalBlocks + 1),
        blockEnd(totalBlocks + 1), array(a), backArray(totalLength + 1), belong(totalLength + 1),
        lazy(totalBlocks + 1, inf) {
        build();
    }
};



#endif PartitialArray_hpp