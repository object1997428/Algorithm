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
typedef pair<int, pii> pip;
#define endl '\n'

int maxCnt, minCnt;
vector<pii> v;
int arr[101], tmp1[101][101], tmp2[101][101];
int N, K, stop;
int way[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };

void init() {
	cin >> N >> K;
	minCnt = INT_MAX, maxCnt = INT_MIN;
	stop = false;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		if (arr[i] < minCnt) {
			minCnt = arr[i];
			v.clear();
			v.push_back({ arr[i],i });
		}
		else if (arr[i] == minCnt) v.push_back({ arr[i],i });

		maxCnt = max(maxCnt, arr[i]);
	}
}

void rotate1() {
	//최소값 +1
	for (int i = 0; i < v.size(); i++) arr[v[i].second]++;

	//공중부양하고 쌓기
	memset(tmp1, 0, sizeof(tmp1));
	for (int i = 0; i < N; i++) tmp1[0][i] = arr[i];

	int r = 1, c = 1;
	int k = 0;
	int s = 0;//움직일 덩어리 시작 x
	while (N - r * c >= r) {
		k++;
		for (int i = 0; i < c; i++)for (int j = 0; j < r; j++) {
			tmp1[1 + i][s + c + j] = tmp1[j][s + c - 1 - i];
		}

		s += c;
		swap(r, c); r++;
	}

	//물고기수 조절
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) tmp2[i][j] = tmp1[i][j];
	for (int i = 0; i < N; i++) {
		if (tmp1[i][s] == 0) break;
		for (int j = s; j < N; j++) {
			if (tmp1[i][j] == 0) break;

			int y = i, x = j;
			int sum = 0;
			for (int w = 0; w < 4; w++) {
				int ny = y + way[w][0];
				int nx = x + way[w][1];
				if (ny >= 0 && nx >= s && ny < N && nx < N && tmp1[ny][nx]>0 && tmp1[y][x]>tmp1[ny][nx]) {
					int d = abs(tmp1[y][x] - tmp1[ny][nx]) / 5;
					if (d > 0) {
						tmp2[ny][nx] += d;
						sum += d;
					}
				}
			}
			tmp2[y][x] -= sum;
		}
	}

	//1자로 되돌리기
	int cnt = 0;
	for (int i = s; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tmp2[j][s] == 0) break;
			if (tmp2[j][i] == 0) continue;
			arr[cnt++] = tmp2[j][i];
		}
	}
}

void rotate2() {
	memset(tmp1, 0, sizeof(tmp1));
	memset(tmp2, 0, sizeof(tmp2));
	for (int i = 0; i < N; i++) tmp1[0][i] = arr[i];

	int r = 1, c = N / 2;
	int s = 0; //돌려야하는 덩어리 시작x
	for (int k = 0; k < 2; k++) {

		//1번 반시계
		for (int i = 0; i < c; i++)for (int j = 0; j < r; j++) {
			tmp2[i][j] = tmp1[j][c - i - 1 + s];
		}

		swap(r, c);

		//2번 반시계 
		for (int i = 0; i < c; i++)for (int j = 0; j < r; j++) {
			tmp1[i + c][j + r + s] = tmp2[j][c - i - 1];
		}

		swap(r, c);

		r = r + 1;
		s += c;
		c = c / 2;
	}

	//물고기수 조절
	memset(tmp2, 0, sizeof(tmp2));
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) tmp2[i][j] = tmp1[i][j];
	for (int i = 0; i < N; i++) {
		if (tmp1[i][s] == 0) break;
		for (int j = s; j < N; j++) {
			if (tmp1[i][j] == 0) break;

			int y = i, x = j;
			int sum = 0;
			for (int w = 0; w < 4; w++) {
				int ny = y + way[w][0];
				int nx = x + way[w][1];
				if (ny >= 0 && nx >= s && ny < N && nx < N && tmp1[ny][nx]>0 && tmp1[y][x]>tmp1[ny][nx]) {
					int d = abs(tmp1[y][x] - tmp1[ny][nx]) / 5;
					if (d > 0) {
						tmp2[ny][nx] += d;
						sum += d;
					}
				}
			}
			tmp2[y][x] -= sum;
		}
	}


	//1자로 되돌리기
	int cnt = 0;
	minCnt = INT_MAX, maxCnt = INT_MIN;
	for (int i = s; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tmp2[j][s] == 0) break;
			if (tmp2[j][i] == 0) continue;
			arr[cnt++] = tmp2[j][i];

			if (tmp2[j][i] < minCnt) {
				minCnt = tmp2[j][i];
				v.clear();
				v.push_back({ tmp2[j][i],cnt - 1 });
			}
			else if (tmp2[j][i] == minCnt) v.push_back({ tmp2[j][i],cnt - 1 });

			maxCnt = max(maxCnt, tmp2[j][i]);
		}
	}

	if (maxCnt - minCnt <= K) stop = 1;
}


void solve() {
	rotate1();
	rotate2();
}

int main() {
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	int i;
	for (i = 0; ; i++) {
		solve();
		if (stop) break;
	}
	cout << i + 1 << endl;

	//fclose(stdin);
}