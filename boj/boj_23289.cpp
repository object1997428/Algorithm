#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#define MAX 987654321
#pragma warning(disable:4996)
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<pii, int> pip;
#define endl '\n'

vector<pip> robot;//온풍기, {{y,x},w}
vector<pii> chkT;
queue<pii> q;
int way[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
int bw[4][3][2] = {
    {{-1,-1},{-1,0},{-1,1}},
    {{-1,1},{0,1},{1,1}},
    {{1,-1},{1,0},{1,1}},
    {{-1,-1},{0,-1},{1,-1}}
};
int isWall[21][21][21][21];
int arr[21][21];
//int arr[3][3] = { 
//    {0,0,0},
//    {0,46,0},
//    {0,2,0}
//};
int tmp[21][21];
int chk[21][21];
int N, M, K, W;

void blow(int ry, int rx, int w) {
    memset(chk, 0, sizeof(chk));
    while (!q.empty()) q.pop();

    int sy = ry + way[w][0];
    int sx = rx + way[w][1];
    q.push({ sy,sx });
    chk[sy][sx] = 5;

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        if (chk[y][x] == 0) break;

        arr[y][x] += chk[y][x];

        for (int i = 0; i < 3; i++) {
            int ny = y + bw[w][i][0];
            int nx = x + bw[w][i][1];
            if (ny >= 0 && nx >= 0 && ny < N && nx < M && chk[ny][nx] == 0 && isWall[y][x][ny][nx] == 0) {
                if (bw[w][i][0] != 0 && bw[w][i][1] != 0) {
                    if (w & 1 && (isWall[y][x][ny][x] == 0 && isWall[ny][x][ny][nx] == 0)) {
                        chk[ny][nx] = chk[y][x] - 1;
                        q.push({ ny,nx });
                    }
                    else if (w % 2 == 0 && (isWall[y][x][y][nx] == 0 && isWall[y][nx][ny][nx] == 0)) {
                        chk[ny][nx] = chk[y][x] - 1;
                        q.push({ ny,nx });
                    }
                }
                else {
                    chk[ny][nx] = chk[y][x] - 1;
                    q.push({ ny,nx });
                }
            }
        }
    }
}

void changeT() {
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < N; i++)for (int j = 0; j < M; j++) {
        int y = i, x = j;
        int sum = 0;
        for (int w = 0; w < 4; w++) {
            int ny = y + way[w][0];
            int nx = x + way[w][1];
            if (ny >= 0 && nx >= 0 && ny < N && nx<M && isWall[y][x][ny][nx] == 0 && arr[y][x]>arr[ny][nx]) {
                int gap = (arr[y][x] - arr[ny][nx]) / 4;
                assert(gap >= 0);
                tmp[ny][nx] += gap;
                sum += gap;
            }
        }
        tmp[y][x] -= sum;
    }
    for (int i = 0; i < N; i++)for (int j = 0; j < M; j++) arr[i][j] += tmp[i][j];
}

void OutLine() {
    int y = 0, x = 1, w = 1;
    while (1) {
        int ny = y + way[w][0];
        int nx = x + way[w][1];
        if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
            w = (w + 1) % 4;
            if (w == 1) {
                arr[y][x] = max(arr[y][x] - 1, 0);
                break;
            }
            continue;
        }

        arr[y][x] = max(arr[y][x] - 1, 0);
        y = ny, x = nx;
    }
}

bool isSumK() {
    for (auto yx : chkT) {
        int y = yx.first;
        int x = yx.second;
        if (arr[y][x] < K) return false;
    }
    return true;
}

int solve() {
    int choco;
    for (choco = 1; choco <= 100; choco++) {
        //1. 온풍기에서 바람
        for (int i = 0; i < robot.size(); i++) {
            int ry = robot[i].first.first;
            int rx = robot[i].first.second;
            int rw = robot[i].second;
            blow(ry, rx, rw);
        }
        //2. 온도 조절
        changeT();
        //3. 가장 바깥쪽의 칸-1
        OutLine();
        //4. 체크
        if (choco > 50) {
            int q = 0;
        }
        if (isSumK()) break;
    }
    return choco;
}

void init() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)for (int j = 0; j < M; j++) {
        int x;
        cin >> x;
        if (x == 5) chkT.push_back({ i,j });
        else if (x > 0) {
            if (x == 1) robot.push_back({ {i,j},1 });
            else if (x == 2) robot.push_back({ {i,j},3 });
            else if (x == 3) robot.push_back({ {i,j},0 });
            else if (x == 4) robot.push_back({ {i,j},2 });
        }
    }
    cin >> W;
    for (int i = 0; i < W; i++) {
        int y, x, t; cin >> y >> x >> t; --x, --y;
        if (t == 0) isWall[y][x][y - 1][x] = 1, isWall[y - 1][x][y][x] = 1;
        else isWall[y][x][y][x + 1] = 1, isWall[y][x + 1][y][x] = 1;
    }
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    init();
    int ans = solve();
    cout << ans << endl;

    //fclose(stdin);
}