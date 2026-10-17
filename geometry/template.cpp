#include <bits/stdc++.h>
using namespace std;

/*************************** 浮点数精度控制 ***************************/
const double eps = 1e-8;
const double PI = acos(-1.0);
const double INF = 1e30; // 代表无穷大，用于竖直直线

// 浮点数符号判断：-1 负数，0 零，1 正数
int sgn(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

/*************************** 点 / 向量 ***************************/
struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}

    // 向量加减、数乘
    Point operator+(const Point &b) const { return Point(x + b.x, y + b.y); }
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }

    // 比较运算符（用于排序、去重）
    bool operator==(const Point &b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator<(const Point &b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
};

// 用 Vector 别名表示向量，与 Point 本质相同
typedef Point Vector;

/*************************** 直线 / 圆 ***************************/

// 直线（点向式）：点 p + 方向向量 v
struct Line {
    Point p;
    Vector v;
    Line() {}
    Line(Point _p, Vector _v) : p(_p), v(_v) {}
};

// 圆
struct Circle {
    Point o;
    double r;
    Circle() {}
    Circle(Point _o, double _r) : o(_o), r(_r) {}
};

/*************************** 向量基本运算 ***************************/

// 点积 Dot Product: |a||b|cosθ
double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

// 叉积 Cross Product: |a||b|sinθ，几何意义为 a 和 b 张成的有向平行四边形面积[reference:2]
double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

// 向量模长
double len(Vector a) {
    return sqrt(dot(a, a));
}

// 向量夹角（弧度）
double angle(Vector a, Vector b) {
    return acos(dot(a, b) / len(a) / len(b));
}

// 向量旋转（逆时针旋转 rad 弧度）
Vector rotate(Vector a, double rad) {
    return Point(a.x * cos(rad) - a.y * sin(rad),
                 a.x * sin(rad) + a.y * cos(rad));
}

// 单位法向量（左转90°）
Vector normal(Vector a) {
    double l = len(a);
    return Point(-a.y / l, a.x / l);
}

/*************************** 垂直与对称关系 ***************************/

// 判断两个向量是否垂直（点积为零）
bool isVertical(Vector a, Vector b) {
    return sgn(dot(a, b)) == 0;
}

// 判断两条线段（或直线）AB 与 CD 是否垂直（重载）
// 直接复用向量版本，传入各自的方向向量
bool isVertical(Point A, Point B, Point C, Point D) {
    return isVertical(B - A, D - C);
}

// 求点 P 在直线 AB 上的投影点（垂足）
// 若 A == B（直线退化），则返回 A
Point projection(Point P, Point A, Point B) {
    if (A == B) return A;
    Vector v = B - A;
    double t = dot(P - A, v) / dot(v, v); // 投影系数
    return A + v * t;
}

// 求点 P 关于直线 AB 的对称点（镜像点）
Point reflection(Point P, Point A, Point B) {
    Point foot = projection(P, A, B);
    return foot * 2 - P;
}

/*************************** 点 / 线段 / 直线 ***************************/

// 两点距离
double dist(Point a, Point b) {
    return len(a - b);
}

// 计算两点连线斜率，若直线竖直（dx=0）则返回 INF
double slope(Point a, Point b) {
    double dx = a.x - b.x;
    if (sgn(dx) == 0) return INF; // 竖直
    return (a.y - b.y) / dx;
}

// 判断点 C 在直线 AB 的哪一侧
// cross(B-A, C-A) > 0 => C 在 AB 左侧；< 0 => 右侧；= 0 => 在直线上[reference:4]
int pointSide(Point A, Point B, Point C) {
    return sgn(cross(B - A, C - A));
}

// 判断点 C 是否在线段 AB 上（含端点）
bool pointOnSegment(Point A, Point B, Point C) {
    return sgn(cross(B - A, C - A)) == 0 && sgn(dot(A - C, B - C)) <= 0;
}

// 点到直线的距离
double pointToLine(Point P, Point A, Point B) {
    Vector v1 = B - A, v2 = P - A;
    return fabs(cross(v1, v2)) / len(v1);
}

// 点到线段的距离
double pointToSegment(Point P, Point A, Point B) {
    if (A == B) return dist(P, A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (sgn(dot(v1, v2)) < 0) return dist(P, A);
    if (sgn(dot(v1, v3)) > 0) return dist(P, B);
    return pointToLine(P, A, B);
}

/*************************** 线段相交判断 ***************************/

// 快速排斥实验 + 实验: AB和CD不相交
bool segmentIntersect(Point A, Point B, Point C, Point D) {
    // 快速排斥实验：以线段为对角线的矩形是否相交
    if (max(A.x, B.x) < min(C.x, D.x) + eps ||
        max(C.x, D.x) < min(A.x, B.x) + eps ||
        max(A.y, B.y) < min(C.y, D.y) + eps ||
        max(C.y, D.y) < min(A.y, B.y) + eps)
        return false;

    // 跨立实验：C 和 D 在 AB 两侧，且 A 和 B 在 CD 两侧
    double c1 = cross(B - A, C - A), c2 = cross(B - A, D - A);
    double c3 = cross(D - C, A - C), c4 = cross(D - C, B - C);
    return sgn(c1) * sgn(c2) <= 0 && sgn(c3) * sgn(c4) <= 0;
}

// 求两条直线的交点（需保证不平行）
Point getLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P - Q;
    double t = cross(w, u) / cross(v, w);
    return P + v * t;
}

/*************************** 多边形 ***************************/

// 多边形面积（顶点按顺时针或逆时针顺序排列）
double polygonArea(vector<Point> &p) {
    double area = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += cross(p[i], p[j]);
    }
    return fabs(area) / 2.0;
}

// 多边形周长（顶点按你想要的顺序排列）
double polygonPerimeter(vector<Point> &p) {
    double per = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        per += dist(p[i], p[(i + 1) % n]);
    }
    return per;
}

// 判断点是否在多边形内（射线法）
// 返回：-1 在边上，0 在外部，1 在内部
int pointInPolygon(Point P, vector<Point> &p) {
    int n = p.size();
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (pointOnSegment(p[i], p[j], P)) return -1;
        if ((p[i].y > P.y) != (p[j].y > P.y)) {
            double x = (p[j].x - p[i].x) * (P.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
            if (sgn(x - P.x) > 0) inside = !inside;
        }
    }
    return inside ? 1 : 0;
}

/*************************** 极角排序 ***************************/

// 返回点 p 相对于原点的象限（1~4），原点返回 0
// 象限定义：从 x 正半轴逆时针旋转，[0, π/2) 为1，[π/2, π) 为2，[π, 3π/2) 为3，[3π/2, 2π) 为4
int quad(const Point &p) {
    if (sgn(p.x) > 0 && sgn(p.y) >= 0) return 1;
    if (sgn(p.x) <= 0 && sgn(p.y) > 0) return 2;
    if (sgn(p.x) < 0 && sgn(p.y) <= 0) return 3;
    if (sgn(p.x) >= 0 && sgn(p.y) < 0) return 4;
    return 0; // 原点
}

// 极角比较器（相对于原点），按极角从小到大排序，极角相同时按到原点距离从小到大
bool polarCmp(const Point &a, const Point &b) {
    int qa = quad(a), qb = quad(b);
    if (qa != qb) return qa < qb;
    int c = cross(a, b);
    if (c != 0) return c > 0; // a 在 b 逆时针方向，则 a 角度小
    return len(a) < len(b);   // 共线时距离近的在前
}

// 极角比较器（相对于指定点 o）
// 用法：sort(pts.begin(), pts.end(), [&](const Point& a, const Point& b) { return polarCmp(o, a, b); });
bool polarCmp(const Point &o, const Point &a, const Point &b) {
    Vector va = a - o, vb = b - o;
    int qa = quad(va), qb = quad(vb);
    if (qa != qb) return qa < qb;
    int c = cross(va, vb);
    if (c != 0) return c > 0;
    return len(va) < len(vb);
}

/*************************** 凸包 ***************************/

// Andrew 算法求凸包（逆时针顺序，去除共线点）
// 输入：点集 p（可含重复点、内部点）
// 输出：凸包顶点数组（逆时针顺序），不含共线中间点
// 如果要求不去重的话，把判断里的<= 0 改成 <
vector<Point> convexHull(vector<Point> p) {
    int n = p.size();
    if (n <= 1) return p;

    sort(p.begin(), p.end()); // 按 x 升序，x 相同按 y 升序

    vector<Point> hull;
    hull.reserve(n * 2);

    // 构建下凸壳：从左到右，维护逆时针转向
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 &&
               sgn(cross(hull[hull.size() - 1] - hull[hull.size() - 2], p[i] - hull[hull.size() - 1])) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }

    // 构建上凸壳：从右到左，跳过已使用的点
    int lower = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower &&
               sgn(cross(hull[hull.size() - 1] - hull[hull.size() - 2], p[i] - hull[hull.size() - 1])) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }

    // 删除重复的起点（末尾与开头相同）
    hull.pop_back();
    return hull;
}

/*************************** 闵可夫斯基和 ***************************/

// 计算两个凸包的闵可夫斯基和
// 要求：a 和 b 必须为逆时针顺序的凸包，且起点为最左下角的点（即 y 最小，y 相同时 x 最小）
// 时间复杂度 O(n + m)
vector<Point> minkowskiSum(const vector<Point> &a, const vector<Point> &b) {
    int n = (int)a.size(), m = (int)b.size();
    if (n == 0 || m == 0) return {};

    // 特判：如果某个凸包只有一个点
    if (n == 1) {
        vector<Point> res;
        for (auto p : b)
            res.push_back(p + a[0]);
        return res;
    }
    if (m == 1) {
        vector<Point> res;
        for (auto p : a)
            res.push_back(p + b[0]);
        return res;
    }

    // 1. 提取两个凸包的所有边向量
    vector<Vector> edges;
    edges.reserve(n + m);

    // 从凸包 a 中提取边向量 (a[i+1] - a[i])
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        edges.push_back(a[j] - a[i]);
    }
    // 从凸包 b 中提取边向量 (b[i+1] - b[i])
    for (int i = 0; i < m; i++) {
        int j = (i + 1) % m;
        edges.push_back(b[j] - b[i]);
    }

    // 2. 对所有边向量按极角排序 (使用叉积比较)
    // 排序规则：先按象限排序，再按叉积正负排序，使得向量按逆时针顺序排列
    sort(edges.begin(), edges.end(), [](const Vector &u, const Vector &v) {
        // 上半平面优先 (y > 0 或 y == 0 && x > 0)
        bool left_u = (u.y > 0 || (u.y == 0 && u.x > 0));
        bool left_v = (v.y > 0 || (v.y == 0 && v.x > 0));
        if (left_u != left_v) return left_u > left_v;
        // 叉积大于0 表示 u 在 v 的逆时针方向
        return cross(u, v) > 0;
    });

    // 3. 去重：去除共线的向量 (方向相同或相反的向量)
    // 注意：这里保留第一个向量，跳过后续与之共线的向量
    vector<Vector> unique_edges;
    for (auto e : edges) {
        if (unique_edges.empty()) {
            unique_edges.push_back(e);
        } else {
            // 如果当前向量与上一个向量共线，则合并 (只保留一个)
            // 使用叉积判断是否共线，点积判断是否同向
            if (sgn(cross(unique_edges.back(), e)) == 0 && sgn(dot(unique_edges.back(), e)) > 0) {
                // 共线且同向，跳过
                continue;
            } else {
                unique_edges.push_back(e);
            }
        }
    }

    // 4. 从起始点开始，依次加上所有边向量，构建闵可夫斯基和的凸包
    // 起始点选择两个凸包最左下角的点之和
    Point start = a[0] + b[0]; // 确保 a[0] 和 b[0] 是最左下角的点
    vector<Point> res;
    res.reserve(unique_edges.size() + 1);
    res.push_back(start);

    Point cur = start;
    for (auto e : unique_edges) {
        cur = cur + e;
        res.push_back(cur);
    }

    // 5. 移除最后一个点（它会与起点重合）
    if (res.size() > 1 && res.back() == res[0]) {
        res.pop_back();
    }

    return res;
}

/*************************** 旋转卡壳 ***************************/

// 计算凸包直径（最远点对距离），hull 必须为逆时针严格凸，无共线点
double convexDiameter(const vector<Point> &hull) {
    int n = hull.size();
    if (n == 1) return 0;
    if (n == 2) return dist(hull[0], hull[1]);

    double ans = 0;
    for (int i = 0, j = 1; i < n; i++) {
        // 寻找对踵点：当 (hull[i+1]-hull[i]) 与 (hull[j+1]-hull[j]) 叉积最大时
        while (sgn(cross(hull[(i + 1) % n] - hull[i], hull[(j + 1) % n] - hull[j])) > 0)
            j = (j + 1) % n;
        ans = max(ans, dist(hull[i], hull[j]));
        ans = max(ans, dist(hull[(i + 1) % n], hull[j]));
    }
    return ans;
}

// 计算凸包内最大三角形面积（hull 必须为逆时针严格凸）
double maxTriangleArea(const vector<Point> &hull) {
    int n = hull.size();
    if (n < 3) return 0;
    double ans = 0;
    for (int i = 0; i < n; i++) {
        int k = (i + 1) % n;
        for (int j = (i + 1) % n; j != i; j = (j + 1) % n) {
            while (sgn(cross(hull[(k + 1) % n] - hull[i], hull[j] - hull[i]) -
                       cross(hull[k] - hull[i], hull[j] - hull[i])) > 0)
                k = (k + 1) % n;
            ans = max(ans, fabs(cross(hull[j] - hull[i], hull[k] - hull[i])) / 2.0);
        }
    }
    return ans;
}

/*************************** 半平面交 ***************************/

// 极角比较器（用于 Line 排序），按方向向量 v 的极角从小到大
bool lineAngleCmp(const Line &a, const Line &b) {
    int qa = quad(a.v), qb = quad(b.v);
    if (qa != qb) return qa < qb;
    int c = cross(a.v, b.v);
    if (c != 0) return c > 0;              // 角度更小
    return sgn(cross(b.v, a.p - b.p)) > 0; // 平行时保留左边
}

// 求两条直线的交点（已保证不平行）
Point lineIntersection(const Line &a, const Line &b) {
    Vector u = a.p - b.p;
    double t = cross(b.v, u) / cross(a.v, b.v);
    return a.p + a.v * t;
}

// 半平面交（所有半平面左侧为有效区域），返回交点多边形（逆时针）
vector<Point> halfPlaneIntersection(vector<Line> lines) {
    const double INF = 1e30;
    // 添加四个边界（防止交点为无穷大），可选，视题目而定
    // lines.push_back(Line(Point(-INF, -INF), Vector(1, 0)));
    // lines.push_back(Line(Point(INF, -INF), Vector(0, 1)));
    // lines.push_back(Line(Point(INF, INF), Vector(-1, 0)));
    // lines.push_back(Line(Point(-INF, INF), Vector(0, -1)));

    sort(lines.begin(), lines.end(), lineAngleCmp);

    deque<Line> dq;
    deque<Point> pts; // 存储相邻交点
    for (auto &l : lines) {
        while (!pts.empty() && sgn(cross(l.v, pts.back() - l.p)) <= 0) {
            pts.pop_back();
            dq.pop_back();
        }
        while (!pts.empty() && sgn(cross(l.v, pts.front() - l.p)) <= 0) {
            pts.pop_front();
            dq.pop_front();
        }
        if (!dq.empty() && sgn(cross(dq.back().v, l.v)) == 0) {
            // 平行且同向，取更靠左的
            if (sgn(cross(l.v, dq.back().p - l.p)) > 0)
                continue;
            else
                return vector<Point>(); // 空集
        }
        if (!dq.empty()) pts.push_back(lineIntersection(dq.back(), l));
        dq.push_back(l);
    }
    // 处理首尾
    while (!pts.empty() && sgn(cross(dq.front().v, pts.back() - dq.front().p)) <= 0) {
        pts.pop_back();
        dq.pop_back();
    }
    while (!pts.empty() && sgn(cross(dq.back().v, pts.front() - dq.back().p)) <= 0) {
        pts.pop_front();
        dq.pop_front();
    }
    if (dq.size() <= 2) return vector<Point>(); // 空或点/线

    // 重新计算交点
    pts.clear();
    for (int i = 0; i < (int)dq.size(); i++) {
        int j = (i + 1) % dq.size();
        pts.push_back(lineIntersection(dq[i], dq[j]));
    }
    // 去重（可选）
    vector<Point> res;
    for (auto &p : pts) {
        if (res.empty() || !(res.back() == p)) res.push_back(p);
    }
    if (!res.empty() && res.front() == res.back()) res.pop_back();
    return res;
}

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

/*************************** 三角剖分（凸多边形） ***************************/

// 将凸多边形（逆时针）剖分为三角形，返回三角形列表（三个顶点）
vector<array<Point, 3>> triangulateConvex(const vector<Point> &poly) {
    vector<array<Point, 3>> tris;
    int n = poly.size();
    if (n < 3) return tris;
    for (int i = 1; i < n - 1; i++) {
        tris.push_back({poly[0], poly[i], poly[i + 1]});
    }
    return tris;
}

/*************************** 最小圆覆盖（随机增量法） ***************************/

// 判断点是否在圆内或上
bool inCircle(const Point &p, const Circle &c) {
    return sgn(dist(p, c.o) - c.r) <= 0;
}

// 由两点确定圆（直径）
Circle circleFromTwoPoints(const Point &a, const Point &b) {
    Point o = (a + b) / 2.0;
    return Circle(o, dist(a, b) / 2.0);
}

// 由三点确定圆（外接圆）
Circle circleFromThreePoints(const Point &a, const Point &b, const Point &c) {
    // 中垂线求交点
    Vector v1 = b - a, v2 = c - a;
    double d1 = dot(v1, v1), d2 = dot(v2, v2), d = 2 * cross(v1, v2);
    if (sgn(d) == 0) return Circle(Point(0, 0), 0); // 共线，不会发生
    double ux = (v2.y * d1 - v1.y * d2) / d;
    double uy = (v1.x * d2 - v2.x * d1) / d;
    Point o = a + Point(ux, uy);
    return Circle(o, dist(o, a));
}

Circle minEnclosingCircle(vector<Point> pts) {
    random_shuffle(pts.begin(), pts.end());
    Circle c(Point(0, 0), 0);
    int n = pts.size();
    for (int i = 0; i < n; i++) {
        if (!inCircle(pts[i], c)) {
            c = Circle(pts[i], 0);
            for (int j = 0; j < i; j++) {
                if (!inCircle(pts[j], c)) {
                    c = circleFromTwoPoints(pts[i], pts[j]);
                    for (int k = 0; k < j; k++) {
                        if (!inCircle(pts[k], c)) {
                            c = circleFromThreePoints(pts[i], pts[j], pts[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}

double normAng(double ang) {
    while (ang < 0)
        ang += 2 * PI;
    while (ang >= 2 * PI)
        ang -= 2 * PI;
    return ang;
}

double normAngPi(double ang) {
    while (ang < -PI)
        ang += 2 * PI;
    while (ang >= PI)
        ang -= 2 * PI;
    return ang;
}

/*************************** 平面最近点对 ***************************/

// 分治求最近点对（区间为 [l, r)，调用前需保证 pts 已按 x 升序排序）
double closestPairRec(vector<Point> &pts, int l, int r) {
    if (r - l <= 1) return INF;                 // 0 或 1 个点
    if (r - l == 2) return dist(pts[l], pts[l + 1]);

    int mid = (l + r) >> 1;
    double midx = pts[mid].x;

    // 左右两半分别求最近距离
    double d = min(closestPairRec(pts, l, mid),
                   closestPairRec(pts, mid, r));

    // 取出跨越中线的候选点：x 落在 [midx - d, midx + d] 内
    vector<Point> strip;
    strip.reserve(r - l);
    for (int i = l; i < r; i++) {
        if (fabs(pts[i].x - midx) < d) strip.push_back(pts[i]);
    }

    // 按 y 坐标升序排序
    sort(strip.begin(), strip.end(),
         [](const Point &a, const Point &b) { return a.y < b.y; });

    // 每个点只需与后面 y 差值小于 d 的点比较（最多常数个）
    int s = strip.size();
    for (int i = 0; i < s; i++) {
        for (int j = i + 1; j < s && strip[j].y - strip[i].y < d; j++) {
            d = min(d, dist(strip[i], strip[j]));
        }
    }
    return d;
}

// 接口：传入点集，内部先按 x 排序
double closestPair(vector<Point> pts) {
    if (pts.size() < 2) return INF;
    sort(pts.begin(), pts.end());
    return closestPairRec(pts, 0, (int)pts.size());
}


