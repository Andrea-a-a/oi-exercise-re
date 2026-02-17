#include <bits/stdc++.h>
using namespace std;

int n;
const int MAXN = 1e5+10;
int const MAXM = 200010;
int a[MAXN];
long long k[MAXN];
void Dijkstra(int u);
typedef pair<long long, int> PII; 

int p[MAXN], len;
int dis[MAXN], minn;
bool vis[MAXN];
set<PII> s;

struct edge {
	int v, w, next;
} e[MAXM << 2];

void init(){
	memset(p, -1, sizeof(p));
	len = 0;
}

void insert(int u, int v, int w){
	e[len].v = v; e[len].w = w, e[len].next = p[u];
	p[u] = len++;
}

int main(){
	ios::sync_with_stdio(0);
	init();

    cin >> n;
    for(int i = 1; i <= n ; i++){
        cin >> a[i];
    }
    for(int i = 1; i <= n ; i++){
        cin >> k[i];
    }
    for(int i = 1; i <= n ; i++){
        for(int o = 1; o <= k[i]&&o+1<=n; o++){
			insert(i, i+o-a[i+o], 1);
		}
    }
	Dijkstra(1);
	if(dis[n]== 2139062143)	cout << -1;
	else cout << dis[n];

    return 0;
}



void Dijkstra(int u){
	memset(dis, 0x7f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[u] = 0;
	s.insert(make_pair(0, u));
	while (s.size()) {
		set<PII>::iterator it = s.begin();
		u = it->second;
		s.erase(*it);
		vis[u] = 1;
		for (int i = p[u]; i != -1; i = e[i].next) {
			int v = e[i].v;
			long long w = e[i].w;
			if (!vis[v] && dis[u] + w < dis[v]) {
				s.erase(make_pair(dis[v],v));
				dis[v] = dis[u] + w;
				s.insert(make_pair(dis[v], v));
			} 
		}
	}
}
