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

int N;
int a[2000001];
int tree[8000001];

void update(int i, int s, int e, int idx, int diff) {
	if (idx < s || e < idx) return;
	tree[i] += diff;
	if (s != e) {
		update(left, s, mid, idx, diff);
		update(right, mid + 1, e, idx, diff);
	}
}

int query(int i, int s, int e, int k) {
	if (s == e) return s;
	if (tree[left] >= k) return query(left, s, mid, k);
	else {
		return query(right, mid + 1, e, k - tree[left]);
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	int M = 2000000;
	for (int i = 0; i < N; i++) {
		int t, x; cin >> t >> x;
		if (t == 1) {
			update(1, 0, M, x, 1);
		}
		else {
			int idx = query(1, 0, M, x);
			update(1, 0, M, idx, -1);
			cout << idx << endl;
		}
	}


	//fclose(stdin);
}