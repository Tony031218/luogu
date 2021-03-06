/*************************************************************
 *  > File Name        : P2762.cpp
 *  > Author           : Tony
 *  > Created Time     : 2020/04/15 10:48:36
 *  > Algorithm        : maxflow
**************************************************************/

#include <bits/stdc++.h>
using namespace std;

bool endr = false;

inline int read() {
    int x = 0; int f = 1; char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();}
    while (isdigit(ch))  {x = x * 10 + ch - 48; ch = getchar();}
    if (ch == '\r') endr = true;
    return x * f;
}

const int maxn = 110;
const int inf  = 0x3f3f3f3f;

int n, m, s, t, d[maxn], cur[maxn], tot;
struct Edge {
    int from, to, cap, flow;
};
vector<Edge> edges;
vector<int> G[maxn];
void add(int from, int to, int cap) {
    edges.push_back((Edge) {from, to, cap, 0});
    edges.push_back((Edge) {to, from, 0, 0});
    int mm = edges.size();
    G[from].push_back(mm - 2);
    G[to].push_back(mm - 1);
}

bool vis[maxn];
bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    d[s] = 0;
    vis[s] = 1;
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        for (int i = 0; i < G[x].size(); ++i) {
            Edge& e = edges[G[x][i]];
            if (!vis[e.to] && e.cap > e.flow) {
                vis[e.to] = 1;
                d[e.to] = d[x] + 1;
                Q.push(e.to);
            }
        }
    }
    return vis[t];
}

int DFS(int x, int a) {
    if (x == t || a == 0) return a;
    int flow = 0, f;
    for (int& i = cur[x]; i < G[x].size(); ++i) {
        Edge& e = edges[G[x][i]];
        if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
            e.flow += f;
            edges[G[x][i] ^ 1].flow -= f;
            flow += f;
            a -= f;
            if (a == 0) break;
        }
    }
    return flow;
}

int dinic(int s, int t) {
    int flow = 0;
    while (BFS()) {
        memset(cur, 0, sizeof(cur));
        flow += DFS(s, inf);
    }
    return flow;
}

int main() {
    int m_ = read(), n_ = read();
    n = m_ + n_ + 2; s = 0; t = n - 1;
    for (int i = 1; i <= m_; ++i) {
        int p = read(); tot += p;
        add(s, i, p);
        char tools[10000];
        memset(tools, 0, sizeof(tools));
        cin.getline(tools, 10000);
        int ulen = 0, tool;
        while (sscanf(tools + ulen, "%d", &tool) == 1) {
            add(i, tool + m_, inf);
            if (tool == 0) 
                ulen++;
            else {
                while (tool) {
                    tool /= 10;
                    ulen++;
                }
            }
            ulen++;
        }
    }
    for (int i = 1; i <= n_; ++i) {
        int c = read();
        add(i + m_, t, c);
    }
    int ans = dinic(s, t);
    for (int i = 1; i <= m_; ++i) {
        if (vis[i]) printf("%d ", i);
    }
    printf("\n");
    for (int i = 1; i <= n_; ++i) {
        if (vis[i + m_]) printf("%d ", i);
    }
    printf("\n");
    printf("%d\n", tot - ans);
    return 0;
}