#include <bits/stdc++.h>
using namespace std;

int n, m;
const int MAXN = 4e5+10;
long long a[100101];
long long c[MAXN] = {0};
long long tag[MAXN] = {0};

int getl(int i){
    return (i << 1);
}

int getr(int i){
    return (i << 1)+1;
}

void pushup(int i){
    int il = getl(i);
    int ir = getr(i);

    c[i] = c[ir] + c[il];
}

void build(int l, int r, int i){
    if(l == r){
        c[i] = a[l];
        return;
    }
    int mid = (l + r) >> 1;

    int il = getl(i);
    int ir = getr(i);
    build(l, mid, il);
    build(mid+1, r, ir);

    pushup(i);

}

void pushtagc(int i, int l, int r){
    if(l != r && tag[i]){
        int mid = (r+l) >> 1;
        int mr = getr(i);
        int ml = getl(i);
        c[mr] += tag[i]*(r-mid);
        c[ml] += tag[i] * (mid-l+1);

        tag[mr] += tag[i];
        tag[ml] += tag[i];
        tag[i] = 0;

    }

    return;
}

void update(int nl, int nr, int i, int l, int r, long long x){
    if(nl <= l && nr >= r){
        tag[i] += x;
        c[i] += x * (r-l+1);
        return;
    }
    if(tag[i])  pushtagc(i, l, r);
    int mid = (l+r) >> 1;
    if(nl <= mid)   update(nl, nr, getl(i), l, mid, x);
    if(nr >= mid+1) update(nl, nr, getr(i), mid+1, r, x);
    
    pushup(i);
}

long long queryc(int nl, int nr, int i, int l, int r){
    long long ans = 0;
    if(nl <= l && nr >= r){
        return c[i];
    }
    if(tag[i]) pushtagc(i, l, r);


    int mid = (l+r)/2;
    if(mid >= nl) ans += queryc(nl, nr, getl(i), l, mid);
    if(mid+1 <= nr) ans += queryc(nl, nr, getr(i), mid+1, r);
    return ans;
}


int main(){
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    build(1, n, 1);
    
    for(int i = 0; i < m; i++){
        int opt, l, r;
        cin >> opt >> l >> r;
        if(opt == 1){
            long long k;
            cin >> k;
            update(l, r, 1, 1, n, k);
        }    
        else{
            cout << queryc(l, r, 1, 1, n) << endl;
        }
    }


    return 0;
}