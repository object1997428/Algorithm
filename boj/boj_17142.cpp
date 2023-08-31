#include <algorithm>
#include <iostream>
#include <string.h>
#include <climits>
#include <cassert>
#include <queue>
#include <cmath>
#pragma warning(disable:4996)
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, pii> pp;

int N, M, K;
int arr[51][51];
int chk[51][51];
vector<pii> v;//바이러스 좌표y,x
vector<int> pick;//조합 선택 담는 용
int ans, wallCnt;
int way[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
void init() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) {
				v.push_back({ i,j });
			}
			else if (arr[i][j] == 1) wallCnt++;
		}
	}
	ans = INT_MAX;
}

int play() {
	assert(pick.size() == M);
	queue<pii> q;
	memset(chk, 0, sizeof(chk));//1이상이면 활성화됨
	for (int i = 0; i < M; i++) {
		int p = pick[i];
		int y = v[p].first;
		int x = v[p].second;
		q.push({ y,x });
		chk[y][x] = 1;
	}

	int cnt = 0;
	int time = 0;
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		if (arr[y][x] == 0) cnt++;
		time = max(time, chk[y][x]);
		if (cnt == (N * N) - (v.size()) - wallCnt) break;

		for (int i = 0; i < 4; i++) {
			int ny = y + way[i][0];
			int nx = x + way[i][1];
			if (ny >= 0 && nx >= 0 && ny < N && nx < N && chk[ny][nx] == 0 && arr[ny][nx] != 1) {
				chk[ny][nx] = chk[y][x] + 1;
				q.push({ ny,nx });
			}
		}
	}

	if (cnt < (N * N) - (v.size()) - wallCnt) return INT_MAX;
	return time - 1;
}


void makePlay(int cnt, int start) {
	if (cnt == M) {
		ans = min(ans, play());
		return;
	}


	for (int i = start; i < v.size(); i++) {
		pick.push_back(i);
		makePlay(cnt + 1, i + 1);
		pick.pop_back();
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);

	init();
	makePlay(0, 0);
	if (ans == INT_MAX) ans = -1;
	cout << ans << endl;

	//fclose(stdin);
}