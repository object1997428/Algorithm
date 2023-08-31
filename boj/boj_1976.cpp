#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cassert>
#define MAX 987654321
#pragma warning(disable:4996)
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define endl '\n'

int N, M;
int parent[201];

int find(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find(parent[u]);
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;

    parent[u] = v;
}

bool isConnected() {
    int cur; cin >> cur;
    cur = find(cur);
    for (int i = 1; i < M; i++) {
        int next; cin >> next;
        next = find(next);
        if (cur != next) {
            return false;
        }
        cur = next;
    }
    return true;
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) parent[i] = i;

    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++) {
        int x; cin >> x;
        if (x == 1) {
            merge(i, j);
        }
    }

    if (isConnected()) cout << "YES" << endl;
    else cout << "NO" << endl;




    //fclose(stdin);
}