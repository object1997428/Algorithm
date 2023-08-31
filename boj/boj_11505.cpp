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
#define MOD 1000000007
#define endl '\n'
#define left (i<<1)
#define right (i<<1|1)
#define mid (s+e)/2

ll a[1000001];
ll tree[4000001];
int N, M, K;

ll init(int i, int s, int e) {
	if (s == e) return tree[i] = a[s];
	return tree[i] = ((init(left, s, mid) % MOD) * (init(right, mid + 1, e) % MOD)) % MOD;
}

void update(int i, int s, int e, int idx, ll div, ll mul) {
	if (idx < s || e < idx) return;
	if (s == e) {
		tree[i] = mul;
		return;
	}
	if (s != e) {
		update(left, s, mid, idx, div, mul);
		update(right, mid + 1, e, idx, div, mul);
		tree[i] = ((tree[left] % MOD) * (tree[right] % MOD)) % MOD;
	}

}

ll sum(int i, int s, int e, int l, int r) {
	if (r < s || e < l) return 1;
	if (l <= s && e <= r) return tree[i];
	return ((sum(left, s, mid, l, r) % MOD) * sum(right, mid + 1, e, l, r) % MOD);
}


int main() {
	//freopen("sample_input.txt", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	memset(tree, 1, sizeof(tree));

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) cin >> a[i];
	init(1, 0, N - 1);
	for (int i = 0; i < M + K; i++) {
		int q; cin >> q;
		if (q == 1) {
			int b; ll c; cin >> b >> c;
			ll div = a[b - 1];
			a[b - 1] = c;
			update(1, 0, N - 1, b - 1, div, c);
		}
		else {
			int b, c; cin >> b >> c;
			cout << sum(1, 0, N - 1, b - 1, c - 1) % MOD << endl;
		}
	}


	//fclose(stdin);
}