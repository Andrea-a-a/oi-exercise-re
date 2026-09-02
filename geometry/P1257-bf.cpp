#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long double dis(Point q, Point p){
    long double w = (q.x - p.x) * (q.x - p.x)+ (q.y - p.y) * (q.y - p.y);
    return sqrt(w);
}

int main(){
    int n;
    cin >> n;
    vector<Point> p;
    int q = n;
    while(q--){
        long long x, y;
        cin >> x >> y;
        p.push_back({x, y});
    }
    long double mind = 1e19;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            mind = min(dis(p[i], p[j]), mind);
        }
    }
    cout << std::fixed << std::setprecision(4) << mind;
    return 0;
}