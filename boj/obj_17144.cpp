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

int arr[51][51];
int tmp[51][51], chk[51][51];
int N, M, T;
int cy = -1, cx = -1;
int way[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };

void init() {
    cin >> N >> M >> T;
    for (int i = 0; i < N; i++)for (int j = 0; j < M; j++) {
        cin >> arr[i][j];
        if (arr[i][j] == -1 && cy == -1) cy = i, cx = j;
    }
}

void solve() {
    //미세먼지 확산
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < N; i++)for (int j = 0; j < M; j++) {
        if (arr[i][j] == -1) tmp[i][j] = -1;
        if (arr[i][j] <= 0) continue;
        int sum = 0, y = i, x = j;
        for (int w = 0; w < 4; w++) {
            int ny = y + way[w][0];
            int nx = x + way[w][1];
            if (ny >= 0 && nx >= 0 && ny < N && nx < M) {
                if ((nx == cx && ny == cy) || (nx == cx && ny == cy + 1)) {
                    continue;
                }
                sum += arr[y][x] / 5;
                tmp[ny][nx] += arr[y][x] / 5;
            }
        }
        tmp[y][x] += arr[y][x] - sum;
    }
    for (int i = 0; i < N; i++)for (int j = 0; j < M; j++) arr[i][j] = tmp[i][j];

    //공기청정기 작동
    memset(tmp, 0, sizeof(tmp));
    //1. 위쪽
    int wayUp[4][2] = { {0,1},{-1,0},{0,-1},{1,0} };
    int y = cy, x = cx + 1, w = 0;
    chk[y][x] = 1;
    while (arr[y][x] != -1) {
        int ny = y + wayUp[w][0];
        int nx = x + wayUp[w][1];
        if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
            w++; continue;
        }
        if (arr[ny][nx] == -1) break;
        tmp[ny][nx] = arr[y][x];
        chk[ny][nx] = 1;
        y = ny, x = nx;
    }
    //2. 아래쪽
    int wayDown[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
    y = cy + 1, x = cx + 1, w = 0; chk[y][x] = 1;
    while (arr[y][x] != -1) {
        int ny = y + wayDown[w][0];
        int nx = x + wayDown[w][1];
        if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
            w++; continue;
        }
        if (arr[ny][nx] == -1) break;
        tmp[ny][nx] = arr[y][x];
        chk[ny][nx] = 1;
        y = ny, x = nx;
    }
    for (int i = 0; i < N; i++)for (int j = 0; j < M; j++) if (chk[i][j]) arr[i][j] = tmp[i][j];
}

int calcSum() {
    int sum = 0;
    for (int i = 0; i < N; i++)for (int j = 0; j < M; j++) {
        if (arr[i][j] != -1) sum += arr[i][j];
    }
    return sum;
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    init();
    for (int i = 0; i < T; i++) {
        solve();
    }
    cout << calcSum() << endl;


    //fclose(stdin);
}