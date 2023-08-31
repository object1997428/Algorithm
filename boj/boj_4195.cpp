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

unordered_map<string, int> m1;
int parent[200001];
int cnt[200001];
int wCnt = 1;
int N;

int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}

int merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return cnt[u];

    parent[u] = v;
    return cnt[v] += cnt[u];
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int tc; cin >> tc;
    while (tc--) {
        cin >> N;
        for (int i = 1; i <= N * 2; i++) parent[i] = i, cnt[i] = 1;
        m1.clear();

        wCnt = 1;
        for (int i = 0; i < N; i++) {
            string a, b; cin >> a >> b;
            if (m1[a] == 0) m1[a] = wCnt++;
            if (m1[b] == 0) m1[b] = wCnt++;
            int x = m1[a], y = m1[b];
            cout << merge(x, y) << endl;
        }
    }



    //fclose(stdin);
}