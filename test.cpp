#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// N < 1e5，所以 N_MAX = 100000。
const int N_MAX = 100000;
// 线段树空间：4 * N_MAX + 10 是安全的
const int MAXN = 4 * N_MAX + 10; 

// 避免使用 q，以防与 iostream 发生潜在冲突
int n, q_count, mod; 
// 原始数组 a 必须足够大，N_MAX + 1
long long a[N_MAX + 1]; 
long long c[MAXN] = {0};   // 区间和
long long tagp[MAXN] = {0}; // 加法懒惰标记
long long tagm[MAXN] = {1}; // 乘法懒惰标记

// 获取子节点索引
int getl(int i){ return (i << 1); }
int getr(int i){ return (i << 1) + 1; }

// 向上更新区间和
void pushup(int i){
    c[i] = (c[getl(i)] + c[getr(i)]) % mod;
}

// 构建线段树
void build(int l, int r, int i){
    if(l == r){
        // 修正 1: 初始值必须取模
        c[i] = a[l] % mod; 
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, getl(i));
    build(mid + 1, r, getr(i));
    pushup(i);
}

// 核心：下推懒惰标记 (先乘后加)
void pushtag(int i, int l, int r){
    if(l == r) return;
    
    int mid = (r + l) >> 1;
    int ml = getl(i);
    int mr = getr(i);

    // 1. 处理乘法标记 tagm[i] (先乘)
    if(tagm[i] != 1){
        long long m_val = tagm[i];

        // a. 更新子节点的 sum c: c = c * m
        c[ml] = c[ml] * m_val % mod;
        c[mr] = c[mr] * m_val % mod;
        
        // b. 更新子节点的 tagm: tagm = tagm * m
        tagm[ml] = tagm[ml] * m_val % mod;
        tagm[mr] = tagm[mr] * m_val % mod;
        
        // c. 更新子节点的 tagp: tagp = tagp * m (乘法作用于加法)
        tagp[ml] = tagp[ml] * m_val % mod;
        tagp[mr] = tagp[mr] * m_val % mod;
        
        // d. 清除父节点的 tagm
        tagm[i] = 1;
    }

    // 2. 处理加法标记 tagp[i] (后加)
    if(tagp[i] != 0){
        long long p_val = tagp[i];
        
        // a. 更新子节点的 sum c: c = c + p * 长度
        c[ml] = (c[ml] + p_val * (mid - l + 1)) % mod;
        c[mr] = (c[mr] + p_val * (r - mid)) % mod;

        // b. 更新子节点的 tagp: tagp = tagp + p
        // 修正 2: 必须对 tagp[ml/mr] 取模
        tagp[ml] = (tagp[ml] + p_val) % mod;
        tagp[mr] = (tagp[mr] + p_val) % mod;
        
        // c. 清除父节点的 tagp
        tagp[i] = 0;
    }
}

// 区间加法： [nl, nr] 增加 x
void update_add(int nl, int nr, int i, int l, int r, long long x){
    // 1. 完全覆盖：直接更新
    if(nl <= l && nr >= r){
        // 修正 3: tagp[i] 必须取模
        tagp[i] = (tagp[i] + x) % mod;
        // 更新 sum c[i]
        c[i] = (c[i] + x * (r - l + 1)) % mod;
        return;
    }
    
    // 2. 任何操作前，都要下推所有懒惰标记
    pushtag(i, l, r);
    
    int mid = (l + r) >> 1;

    // 3. 递归更新子节点
    if(nl <= mid) update_add(nl, nr, getl(i), l, mid, x);
    if(nr >= mid + 1) update_add(nl, nr, getr(i), mid + 1, r, x);
    
    // 4. 向上更新当前节点的区间和
    pushup(i);
}

// 区间乘法： [nl, nr] 乘以 x
void update_mul(int nl, int nr, int i, int l, int r, long long x){
    // 1. 完全覆盖：直接更新
    if(nl <= l && nr >= r){
        // 修正 4: tagp 也必须乘以 x (乘法对加法的分配律)
        tagm[i] = tagm[i] * x % mod;
        tagp[i] = tagp[i] * x % mod; 

        // 更新 sum c[i]
        c[i] = c[i] * x % mod;
        return;
    }
    
    // 2. 任何操作前，都要下推所有懒惰标记
    pushtag(i, l, r);
    
    int mid = (l + r) >> 1;

    // 3. 递归更新子节点
    if(nl <= mid) update_mul(nl, nr, getl(i), l, mid, x);
    if(nr >= mid + 1) update_mul(nl, nr, getr(i), mid + 1, r, x);
    
    // 4. 向上更新当前节点的区间和
    pushup(i);
}


// 区间查询操作： 查询 [nl, nr] 的区间和
long long queryc(int nl, int nr, int i, int l, int r){
    // 1. 完全覆盖：直接返回当前节点的值
    if(nl <= l && nr >= r){
        return c[i];
    }
    
    // 2. 查询前，都要下推所有懒惰标记
    // 触发条件已在 pushtag 内检查
    pushtag(i, l, r);
    
    long long ans = 0;
    int mid = (l + r) / 2;

    // 3. 规范化递归查询逻辑
    if(nl <= mid) 
        ans = (ans + queryc(nl, nr, getl(i), l, mid)) % mod;
    
    if(nr >= mid + 1) 
        ans = (ans + queryc(nl, nr, getr(i), mid + 1, r)) % mod;
    
    return ans;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); 

    // 使用 q_count 代替 q，以与你的代码逻辑保持一致
    cin >> n >> q_count >> mod; 
    
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    
    build(1, n, 1);
    
    for(int i = 0; i < q_count; i++){
        int opt, l, r;
        long long k; // k 必须是 long long
        
        cin >> opt >> l >> r;
        
        if(opt == 1 || opt == 2){
            cin >> k;
            k %= mod; // 增量/乘数也应该在读取时取模
        }

        if(opt == 1){
            // 区间乘法
            update_mul(l, r, 1, 1, n, k);
        } else if(opt == 2){ 
            // 区间加法
            update_add(l, r, 1, 1, n, k);
        } else if(opt == 3) {
            // 区间查询
            long long ans = queryc(l, r, 1, 1, n);
            cout << ans << "\n";
        }
    }

    return 0;
}
