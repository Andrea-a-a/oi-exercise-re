#include <bits/stdc++.h>
using namespace std;



/*************************** 扫描线（矩形面积并） ***************************/

struct Rect {
    double x1, y1, x2, y2; // 左下、右上
};

// 线段树节点（用于扫描线）
struct SegNode {
    int cnt;    // 覆盖次数
    double len; // 覆盖总长度
};

vector<double> ys; // 离散化后的 y 坐标

void pushup(int u, int l, int r, vector<SegNode> &tree) {
    if (tree[u].cnt > 0)
        tree[u].len = ys[r] - ys[l];
    else if (l + 1 == r)
        tree[u].len = 0;
    else
        tree[u].len = tree[u << 1].len + tree[u << 1 | 1].len;
}

void update(int u, int l, int r, int ql, int qr, int val, vector<SegNode> &tree) {
    if (ql <= l && r <= qr) {
        tree[u].cnt += val;
        pushup(u, l, r, tree);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql < mid) update(u << 1, l, mid, ql, qr, val, tree);
    if (qr > mid) update(u << 1 | 1, mid, r, ql, qr, val, tree);
    pushup(u, l, r, tree);
}

double rectangleUnion(vector<Rect> rects) {
    struct Event {
        double x, y1, y2;
        int type; // 1 入边，-1 出边
        bool operator<(const Event &e) const { return x < e.x; }
    };
    vector<Event> events;
    ys.clear();
    for (auto &r : rects) {
        events.push_back({r.x1, r.y1, r.y2, 1});
        events.push_back({r.x2, r.y1, r.y2, -1});
        ys.push_back(r.y1);
        ys.push_back(r.y2);
    }
    sort(events.begin(), events.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int m = ys.size();
    vector<SegNode> tree(4 * m + 5);
    double ans = 0;
    for (int i = 0; i < (int)events.size() - 1; i++) {
        int l = lower_bound(ys.begin(), ys.end(), events[i].y1) - ys.begin();
        int r = lower_bound(ys.begin(), ys.end(), events[i].y2) - ys.begin();
        update(1, 0, m - 1, l, r, events[i].type, tree);
        ans += (events[i + 1].x - events[i].x) * tree[1].len;
    }
    return ans;
}

int main(){
    int n;
    cin >> n;
    vector<Rect> rects;

    while(n--){
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Rect i = {x1, y1, x2, y2};
        rects.push_back(i);
    }

    cout << fixed << setprecision(0) <<  rectangleUnion(rects);
}