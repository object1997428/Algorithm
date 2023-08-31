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

int N, E;
vector<pii> g1[801];
//vector<pii> g2[801];
int a, b;

priority_queue<pii, vector<pii>, greater<>> q;


vector<int> dijkstra(int src, vector<pii> g[]) {
    vector<int> dist(N + 1, INT_MAX);
    dist[src] = 0;
    q.push({ 0,src });
    while (!q.empty()) {
        int src_u = q.top().first;
        int u = q.top().second;
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

void init() {
    cin >> N >> E;
    for (int i = 0; i < E; ++i) {
        int u, v, w; cin >> u >> v >> w;
        g1[u].push_back({ v,w });
        g1[v].push_back({ u,w });
    }
    cin >> a >> b;
}

ll solve() {
    auto from1 = dijkstra(1, g1);
    auto toN = dijkstra(N, g1);
    auto fromB = dijkstra(b, g1);

    int one_A = from1[a], one_B = from1[b];
    int A_N = toN[a];
    int B_N = toN[b];
    int B_A;
    int A_B = B_A = fromB[a];
    assert(A_B == B_A);

    ll ret1 = INT_MAX;
    if (one_A != INT_MAX && A_B != INT_MAX && B_N != INT_MAX) ret1 = one_A + A_B + B_N;
    ll ret2 = INT_MAX;
    if (one_B != INT_MAX && B_A != INT_MAX && A_N != INT_MAX) ret2 = one_B + B_A + A_N;
    if (ret1 == INT_MAX && ret2 == INT_MAX) return -1;
    else if (ret1 == INT_MAX) return ret2;
    else if (ret2 == INT_MAX) return ret1;
    return min(ret1, ret2);
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    init();
    cout << solve() << endl;

    //fclose(stdin);
}