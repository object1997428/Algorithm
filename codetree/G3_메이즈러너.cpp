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
typedef pair<pii, int> pip;
#define endl '\n'


int N, M, K;
int arr[11][11], tmp[11][11];
vector<pii> v;
int ey, ex;
int moveCnt;
int exitCnt;

int way[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

void init() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)for (int j = 0; j < N; j++) cin >> arr[i][j];
	for (int i = 0; i < M; i++) {
		int y, x; cin >> y >> x;
		v.push_back({ y - 1,x - 1 });
	}
	cin >> ey >> ex; ey--, ex--;
}

void move() {
	for (int i = 0; i < M; i++) {
		int y = v[i].first, x = v[i].second;
		if (y == -1 && x == -1) continue;
		int dist = abs(ey - y) + abs(ex - x);
		for (int j = 0; j < 4; j++) {
			int ny = y + way[j][0];
			int nx = x + way[j][1];
			int ndist = abs(ey - ny) + abs(ex - nx);
			if (dist > ndist && ny >= 0 && nx >= 0 && ny < N && nx < N && arr[ny][nx] == 0) {
				moveCnt++;
				v[i].first = ny; v[i].second = nx;
				if (ny == ey && nx == ex) {
					exitCnt++;
					v[i].first = -1, v[i].second = -1;
				}
				break;
			}
		}
	}
}

pip makeRactangle() {
	int mink = INT_MAX;
	pii s;
	pii e = { ey,ex };
	pii zero = { 0,0 };
	for (int i = 0; i < M; i++) {
		int y = v[i].first, x = v[i].second;
		if (y == -1 && x == -1) continue;
		int x_gap = abs(ex - x);
		int y_gap = abs(ey - y);
		int k = max(y_gap, x_gap);

		pii rd = { max(e.first,v[i].first),max(e.second,v[i].second) };
		pii lu = { max(0,rd.first - k),max(0,rd.second - k) };

		if (mink > k) {
			mink = k;
			s = lu;
		}
		else if (mink == k)s = min(s, lu);
	}
	return { s,mink + 1 };
}

void rotate() {
	pip ret = makeRactangle();
	int sy = ret.first.first;
	int sx = ret.first.second;
	int n = ret.second;

	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; i++)for (int j = 0; j < n; j++) {
		tmp[sy + i][sx + j] = arr[sy + n - 1 - j][sx + i];
	}
	for (int i = 0; i < n; i++)for (int j = 0; j < n; j++) arr[sy + i][sx + j] = max(0, tmp[sy + i][sx + j] - 1);

	for (int i = 0; i < M; i++) {
		if (v[i].first == -1 && v[i].second == -1) continue;
		if (v[i].first >= sy && v[i].second >= sx && v[i].first < sy + n && v[i].second < sx + n) {
			v[i].first -= sy, v[i].second -= sx;

			int tmp = v[i].second;
			v[i].second = n - 1 - (v[i].first);
			v[i].first = tmp;

			v[i].first += sy, v[i].second += sx;
		}
	}

	ey -= sy, ex -= sx;
	int tmp = ex;
	ex = n - 1 - ey;
	ey = tmp;
	ey += sy, ex += sx;
}

void solve() {
	for (int i = 0; i < K; i++) {
		if (i == 12) {
			int q = 0;
		}
		move();
		if (exitCnt == M) break;
		rotate();
		if (exitCnt == M) break;
		assert(arr[ey][ex] == 0);
	}
	cout << moveCnt << endl;
	cout << ey + 1 << " " << ex + 1 << endl;
}

int main() {
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	solve();

	//fclose(stdin);
}