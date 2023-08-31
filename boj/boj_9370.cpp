#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#define MAX 987654321
#pragma warning(disable:4996)
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define endl '\n'

int N, M, T;
int s, v1, v2;
vector<pii> g[2001];
vector<int> candidate;

void init() {
    for (int i = 0; i < 2001; i++) {
        if (g[i].size() > 0) g[i].clear();
    }
    candidate.clear();


    cin >> N >> M >> T;
    cin >> s >> v1 >> v2;
    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({ v,w });
        g[v].push_back({ u,w });
    }
    for (int i = 0; i < T; i++) {
        int c; cin >> c;
        candidate.push_back(c);
    }
}
priority_queue<pii, vector<pii>, greater<>> q;
vector<int> dijkstra(int src) {
    vector<int> dist(N + 1, INT_MAX);
   

    q.push({ 0,src });
    dist[src] = 0;
    while (!q.empty()) {
        int u = q.top().second;
        int src_u = q.top().first;
        q.pop();
        if (dist[u] < src_u) continue;

        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first;
            int u_v = g[u][i].second;
            if (src_u + u_v < dist[v]) {
                dist[v] = src_u + u_v;
                q.push({ dist[v],v });
            }
        }
    }

    return dist;
}

void solve() {
    auto sDist = dijkstra(s);
    auto v1Dist = dijkstra(v1);
    auto v2Dist = dijkstra(v2);

    vector<int> ans;
    for (int cand : candidate) {
        if (sDist[cand] == sDist[v1] + v1Dist[v2] + v2Dist[cand]) ans.push_back(cand);
        else if(sDist[cand] == sDist[v2] + v2Dist[v1] + v1Dist[cand]) ans.push_back(cand);
    }
    sort(ans.begin(), ans.end());
    for (int dst : ans) cout << dst << " ";
    cout << endl;
}

int main() {
    freopen("sample_input.txt", "r", stdin);
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int tc; cin >> tc;
    while (tc--) {
        init();
        solve();
    }
   

    fclose(stdin);
}
