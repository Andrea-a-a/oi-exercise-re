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

int main() {
    vector<Point> p;
    for (int i = 0; i < 3; i++) {
        int a, b;
        char tmp;
        cin >> tmp >> a >> tmp >> b >> tmp;
        p.push_back({a, b});
    }

    int a, b;
    char tmp;
    cin >> tmp >> a >> tmp >> b >> tmp;
    Point o = {a, b};

    for (auto i : p) {
        if (o == i) {
            cout << "4";
            return 0;
        }
    }
    int i = pointInPolygon(o, p);
    if(i == -1) cout << 3;
    else if(i == 0) cout << 2;
    else if(i == 1) cout << 1;
}