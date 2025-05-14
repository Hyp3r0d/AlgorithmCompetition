#include<bits/extc++.h>
using i8 = signed char;
using u8 = unsigned char;
using i16 = signed short int;
using u16 = unsigned short int;
using i32 = signed int;
using u32 = unsigned int;
using f32 = float;
using i64 = signed long long;
using u64 = unsigned long long;
using f64 = double;
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = long double;
using namespace std;

constexpr i64 mod = 998244353;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

 
struct Edge { 
    int u, v, c; 
}; 
 
// 并查集查找函数 
int find(int x, vector<int>& parent) { 
    return x == parent[x]? x : parent[x] = find(parent[x], parent); 
} 
 
// 并查集合并函数 
void unionSet(int x, int y, vector<int>& parent) { 
    int rootX = find(x, parent); 
    int rootY = find(y, parent); 
    if (rootX != rootY) { 
        parent[rootY] = rootX; 
    } 
} 
 
pair<int, int> burovka(vector<Edge>& edges, int n) { 
    vector<int> parent(n + 1); 
    for (int i = 1; i <= n; ++i) { 
        parent[i] = i; 
    } 
    int k = 0, maxScore = 0; 
    while (true) { 
        vector<int> minEdge(n + 1, INT_MAX); 
        for (const auto& edge : edges) { 
            int u = edge.u, v = edge.v, c = edge.c; 
            int rootU = find(u, parent); 
            int rootV = find(v, parent); 
            if (rootU != rootV) { 
                minEdge[rootU] = min(minEdge[rootU], c); 
                minEdge[rootV] = min(minEdge[rootV], c); 
            } 
        } 
        bool allConnected = true; 
        for (const auto& edge : edges) { 
            int u = edge.u, v = edge.v, c = edge.c; 
            int rootU = find(u, parent); 
            int rootV = find(v, parent); 
            if (rootU != rootV && (c == minEdge[rootU] || c == minEdge[rootV])) { 
                unionSet(rootU, rootV, parent); 
                k++; 
                maxScore = max(maxScore, c); 
                allConnected = false; 
            } 
        } 
        if (allConnected) { 
            break; 
        } 
    } 
    return {k, maxScore}; 
} 
 
int main() { 
    int n, m; 
    cin >> n >> m; 
    vector<Edge> edges(m); 
    for (int i = 0; i < m; ++i) { 
        cin >> edges[i].u >> edges[i].v >> edges[i].c; 
    } 
    auto result = burovka(edges, n); 
    cout << result.first  << " " << result.second  << endl; 
    return 0; 
} 