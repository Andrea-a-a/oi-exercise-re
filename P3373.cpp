#include <bits/stdc++.h>
using namespace std;

int n, q, mod;
const int MAXN = 4e5+10;
long long a[100101];
long long c[MAXN] = {0};
long long tagp[MAXN] = {0};
long long tagm[MAXN];

int getl(int i){
    return (i << 1);
}

int getr(int i){
    return (i << 1)+1;
}

void pushup(int i){
    int il = getl(i);
    int ir = getr(i);

    //b[i] = max(b[il], b[ir]);
    c[i] = c[ir] + c[il];
    c[i] %= mod;
}

void build(int l, int r, int i){
    if(l == r){
        //b[i] = a[l];
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

void pushtag(int i, int l, int r){
    if(l != r){
        int mid = (r+l) >> 1;
        int mr = getr(i);
        int ml = getl(i);

        if(tagm[i] != 1){
        c[mr] *= tagm[i], c[mr] %= mod;
        c[ml] *= tagm[i], c[ml] %= mod;
        tagm[ml] *= tagm[i], tagm[ml] %= mod;
        tagm[mr] *= tagm[i], tagm[mr] %= mod;
        tagp[ml] *= tagm[i], tagp[ml] %= mod;
        tagp[mr] *= tagm[i], tagp[mr] %= mod;
        tagm[i] = 1;
        }

        if(tagp[i]){
        c[mr] += tagp[i]*(r-mid), c[mr] %= mod;
        c[ml] += tagp[i] * (mid-l+1), c[ml] %= mod;

        tagp[mr] += tagp[i], tagp[mr] %= mod;
        tagp[ml] += tagp[i], tagp[ml] %= mod;
        tagp[i] = 0;
        }
    }

    return;
}

void update(int nl, int nr, int i, int l, int r, long long x){
    if(nl <= l && nr >= r){
        tagp[i] += x;
        //b[i] += x;
        c[i] += x * (r-l+1);
        c[i] %= mod;
        return;
    }
    //pushtagb(i, l, r);
    if(tagp[i] || tagm[i] != 1)  pushtag(i, l, r);
    int mid = (l+r) >> 1;
    if(nl <= mid)   update(nl, nr, getl(i), l, mid, x);
    if(nr >= mid+1) update(nl, nr, getr(i), mid+1, r, x);
    
    pushup(i);
}

void updatem(int nl, int nr, int i, int l, int r, long long x){
    if(nl <= l && nr >= r){
        tagm[i] *= x;
        //b[i] += x;
        c[i] *= x;
        c[i] %= mod;
        return;
    }
    //pushtagb(i, l, r);
    if(tagp[i] || tagm[i] != 1)  pushtag(i, l, r);
    int mid = (l+r) >> 1;
    if(nl <= mid)   updatem(nl, nr, getl(i), l, mid, x);
    if(nr >= mid+1) updatem(nl, nr, getr(i), mid+1, r, x);
    
    pushup(i);
}

long long queryc(int nl, int nr, int i, int l, int r){
    long long ans = 0;
    if(nl <= l && nr >= r){
        cout << "return! i=" << i << "   c[i] =" << c[i] << endl;
        return c[i];
    }
    if(tagp[i] || tagm[i] != 1) pushtag(i, l, r);


    int mid = (l+r)/2;
    if(mid >= nl) ans += queryc(nl, nr, getl(i), l, mid), ans%=mod;
    if(mid+1 <= nr) ans += queryc(nl, nr, getr(i), mid+1, r), ans%=mod;
    return ans;
}


int main(){
    ios::sync_with_stdio(0);
    cin >> n >> q >> mod;
    //memset(tagm, 1, sizeof(tagm));
    fill(tagm, tagm+MAXN, 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    build(1, n, 1);

    cout << tagm[1] << tagm[2] << tagm[4];
    
    for(int i = 0; i < q; i++){
        int opt, l, r;
        cin >> opt >> l >> r;
        if(opt == 2){
            long long k;
            cin >> k;
            update(l, r, 1, 1, n, k);
        }    
        else if(opt == 3){
            long long ans = queryc(l, r, 1, 1, n);
            ans %= mod;
            cout << ans << endl;
        }
        else{
            long long k;
            cin >> k;
            updatem(l, r, 1, 1, n, k);
        }
    }


    return 0;
}