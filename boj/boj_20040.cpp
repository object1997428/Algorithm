#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cassert>
#include <unordered_map>
#define MAX 987654321
#pragma warning(disable:4996)
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define endl '\n'

int parent[500001];
int N, M;

int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;

    parent[u] = v;
}

void init() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) parent[i] = i;
}

int solve() {
    int ans = 0;
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        if (ans != 0) continue;
        u = find(u); v = find(v);
        if (u == v && ans == 0) ans = i + 1;

        merge(u, v);
    }
    return ans;
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    init();
    cout << solve() << endl;

    //fclose(stdin);
}