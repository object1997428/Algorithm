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

int a[100001];
pii tree[400001];
int N, M;


pii init(int i, int s, int e) {
	if (s == e) return tree[i] = { a[s],a[s] };
	pii l = init(left, s, mid);
	pii r = init(right, mid + 1, e);
	return tree[i] = { max(l.first,r.first),min(l.second,r.second) };
}

pii query(int i, int s, int e, int l, int r) {
	if (r < s || e < l) return { INT_MIN,INT_MAX };
	if (l <= s && e <= r) return tree[i];
	if (s != e) {
		pii l1 = query(left, s, mid, l, r);
		pii r1 = query(right, mid + 1, e, l, r);
		return { max(l1.first,r1.first),min(l1.second,r1.second) };
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	for (int i = 0; i <= 4 * N; i++) tree[i] = { INT_MIN,INT_MAX };

	cin >> N >> M;
	for (int i = 0; i < N; i++) cin >> a[i];
	init(1, 0, N - 1);
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		pii ret = query(1, 0, N - 1, a - 1, b - 1);
		cout << ret.second << " " << ret.first << endl;
	}


	//fclose(stdin);
}