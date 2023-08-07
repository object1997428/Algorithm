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

int N, M;
int a[100001];
int tree[400001];
int liveCnt;


int init(int i, int s, int e) {
	if (s == e) return tree[i] = 1;
	return tree[i] = init(left, s, mid) + init(right, mid + 1, e);
}

void Input() {
	cin >> N >> M;
	init(1, 0, N - 1);
	liveCnt = N;
}


int findK(int i, int s, int e, int k) {//k번째 수의 idx
	if (s == e) return s;

	if (tree[left] >= k) {
		return findK(left, s, mid, k);
	}
	else {
		return findK(right, mid + 1, e, k - tree[left]);
	}
}

void update(int i, int s, int e, int idx,int diff) {
	if (idx < s || e < idx) return;
	tree[i] += diff;
	assert(tree[i] >= 0);
	if (s != e) {
		update(left, s, mid, idx, diff);
		update(right, mid + 1, e, idx, diff);
	}
}

void solve() {
	int cnt = M-1;
	for (int i = 0; i < N; i++) {
		int idx = findK(1,0,N-1,cnt+1);// a[idx]를 제거할 차례
		cout << idx + 1;
		if (i == N - 1) break;
		cout << ", ";
		update(1, 0, N - 1, idx, -1);
		cnt = (cnt + M - 1) % (--liveCnt);

	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	Input();
	cout << "<";
	solve();
	cout << ">";

	fclose(stdin);
}