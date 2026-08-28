#include <bits/stdc++.h>
using namespace std;

/*************************** 浮点数精度控制 ***************************/
const double eps = 1e-8;
const double PI = acos(-1.0);

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
    Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
    Point operator * (double k) const { return Point(x * k, y * k); }
    Point operator / (double k) const { return Point(x / k, y / k); }

    // 比较运算符（用于排序、去重）
    bool operator == (const Point &b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator < (const Point &b) const {
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

/*************************** 点 / 线段 / 直线 ***************************/

// 两点距离
double dist(Point a, Point b) {
    return len(a - b);
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

// 快速排斥实验 + 跨立实验[reference:6]
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

// 多边形面积（顶点按顺时针或逆时针顺序排列）[reference:8]
double polygonArea(vector<Point> &p) {
    double area = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += cross(p[i], p[j]);
    }
    return fabs(area) / 2.0;
}

// 多边形周长
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

