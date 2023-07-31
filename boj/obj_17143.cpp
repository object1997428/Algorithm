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
#define endl '\n'

typedef struct shark{
    int y, x;
    int v, w, size;
    bool lived;
}shark;
shark node[10001];
int nodeCnt = 0;
shark* getNode(int y, int x, int v, int w, int size) {
    node[nodeCnt].y = y;
    node[nodeCnt].x = x;
    node[nodeCnt].v = v;
    node[nodeCnt].w = w;
    node[nodeCnt].size = size;
    node[nodeCnt].lived = true;
    return &node[nodeCnt++];
}

int R, C, M;
shark* arr[101][101];
int way[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
queue<shark*> q;

void init() {
    cin >> R >> C >> M;
    for (int i = 0; i < M; i++) {
        int y, x, v, w, size; cin >> y >> x >> v >> w >> size;
        if (w == 1) w = 0;
        else if (w == 3) w = 1;
        else if (w == 4) w = 3;//내가 편한 시계방향 설정으로 맞춰줌

        shark* s = getNode(y - 1, x - 1, v, w, size);
        q.push(s);
        arr[y - 1][x - 1] = s;
    }
}

pii getNextPos(shark* sh) {
    int move = sh->v;
    int y = sh->y, x = sh->x;
    int nw = sh->w;
    while (1) {
        int ny = y + way[nw][0] * move, nx = x + way[nw][1]*move;
        if (ny >= 0 && nx >= 0 && ny < R && nx < C) {//경계에 부딪히지 않으면 이제 이동하고 멈춤
            sh->w = nw; sh->y = ny, sh->x = nx;
            return { ny,nx };
        }
        //else 경계에 부딪히니까 1.벽에 붙고 2.move차감 3.방향 반대

        if (nw == 2) {//아래로
            move -= R - 1 - y, y = R - 1;
            nw = (nw + 2) % 4; //반대방향: 위로
        }
        else if (nw == 0) {//위로
            move -= y, y = 0;
            nw = (nw + 2) % 4; //반대방향: 아래로
        }
        else if (nw == 3) {//왼쪽으로
            move -= x, x = 0;
            nw = (nw + 2) % 4; //오른쪽으로
        }
        else if (nw == 1) {//오른쪽으로
            move -= C - 1 - x, x = C - 1;
            nw = (nw + 2) % 4; //왼쪽으로
        }
    }
    assert(0);
}

int solve(int kx) {
    //kx에 있는 상어중에 땅과 제일 가까운 상어 잡기
    int sum = 0;
    for (int i = 0; i < R; i++) {
        if (arr[i][kx] != NULL) {
            sum += arr[i][kx]->size;
            arr[i][kx]->lived = false;
            arr[i][kx] = NULL;
            break;
        }
    }

    //상어들 이동
    memset(arr, 0, sizeof(arr));//리셋: 이동 전 상어와 엉킬수 있음+ 이동 전 상어의 지도정보는 사용되지 않음

    int qsize = (int)q.size();
    for (int i = 0; i < qsize; i++) {
        shark* sh = q.front(); q.pop();//앞을 뽑아서 살아남으면 다시 넣고, 아님 넣지않음
        if (!sh->lived) continue; //낚시왕한테 죽었으면 다시 넣지X

        pii ret = getNextPos(sh);
        int ny = ret.first, nx = ret.second;
        assert(ny >= 0 && nx >= 0 && ny < R&& nx < C);
        if (arr[ny][nx] != 0) {//이동할 위치에 상어가 이미 있으면(지도에 상어가 2마리 이상)
            if (arr[ny][nx]->size < sh->size) {//사이즈가 커서 sh가 잡아먹음
                arr[ny][nx]->lived = false;//이전 상어 죽임
                arr[ny][nx] = sh;//sh는 살아남음: q와 지도에 들어감
                q.push(sh);
            }
            else sh->lived = false;//sh가 작아서 죽음: q와 지도에 들어가지 못함
        }
        else {//지도에 아무도 없어서 살아남음: q와 지도에 들어감
            arr[ny][nx] = sh;
            q.push(sh);
        }
    }
    return sum;
}


int main() {
    freopen("sample_input.txt", "r", stdin);
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    init();
    int ans = 0;
    for (int i = 0; i < C; i++) {
        ans+=solve(i);
    }
    cout << ans << endl;


    fclose(stdin);
}
