#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cassert>
#include <vector>
#define MAX 987654321
#pragma warning(disable:4996)
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define endl '\n'
#define left (i<<1)
#define right (i<<1|1)
#define mid (s+e)/2

int N, M, K;
ll a[1000001];
ll tree[4000001];

ll init(int i, int s, int e) {
	if (s == e) return tree[i] = a[s];
	return tree[i] = init(left, s, mid) + init(right, mid + 1, e);
}

void update(int i, int s, int e, int idx, ll val) {
	if (idx < s || e < idx) return;
	tree[i] += val;
	if (s != e) {
		update(left, s, mid, idx, val);
		update(right, mid + 1, e, idx, val);
	}
}

ll sum(int i, int s, int e, int l, int r) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return tree[i];
	return sum(left, s, mid, l, r) + sum(right, mid + 1, e, l, r);
}


void Input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) cin >> a[i];
	init(1, 0, N - 1);
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	Input();
	for (int i = 0; i < M + K; i++) {
		int q; cin >> q;
		if (q == 1) {
			int b; ll c; cin >> b >> c;
			ll diff = c - a[b - 1];
			a[b - 1] = c;
			update(1, 0, N - 1, b - 1, diff);
		}
		else {
			int b, c; cin >> b >> c;
			cout << sum(1, 0, N - 1, b - 1, c - 1) << endl;
		}
	}


	//fclose(stdin);
}