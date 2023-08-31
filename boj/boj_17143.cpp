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
        else if (w == 4) w = 3;//���� ���� �ð���� �������� ������

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
        if (ny >= 0 && nx >= 0 && ny < R && nx < C) {//��迡 �ε����� ������ ���� �̵��ϰ� ����
            sh->w = nw; sh->y = ny, sh->x = nx;
            return { ny,nx };
        }
        //else ��迡 �ε����ϱ� 1.���� �ٰ� 2.move���� 3.���� �ݴ�

        if (nw == 2) {//�Ʒ���
            move -= R - 1 - y, y = R - 1;
            nw = (nw + 2) % 4; //�ݴ����: ����
        }
        else if (nw == 0) {//����
            move -= y, y = 0;
            nw = (nw + 2) % 4; //�ݴ����: �Ʒ���
        }
        else if (nw == 3) {//��������
            move -= x, x = 0;
            nw = (nw + 2) % 4; //����������
        }
        else if (nw == 1) {//����������
            move -= C - 1 - x, x = C - 1;
            nw = (nw + 2) % 4; //��������
        }
    }
    assert(0);
}

int solve(int kx) {
    //kx�� �ִ� ����߿� ���� ���� ����� ��� ���
    int sum = 0;
    for (int i = 0; i < R; i++) {
        if (arr[i][kx] != NULL) {
            sum += arr[i][kx]->size;
            arr[i][kx]->lived = false;
            arr[i][kx] = NULL;
            break;
        }
    }

    //���� �̵�
    memset(arr, 0, sizeof(arr));//����: �̵� �� ���� ��ų�� ����+ �̵� �� ����� ���������� ������ ����

    int qsize = (int)q.size();
    for (int i = 0; i < qsize; i++) {
        shark* sh = q.front(); q.pop();//���� �̾Ƽ� ��Ƴ����� �ٽ� �ְ�, �ƴ� ��������
        if (!sh->lived) continue; //���ÿ����� �׾����� �ٽ� ����X

        pii ret = getNextPos(sh);
        int ny = ret.first, nx = ret.second;
        assert(ny >= 0 && nx >= 0 && ny < R&& nx < C);
        if (arr[ny][nx] != 0) {//�̵��� ��ġ�� �� �̹� ������(������ �� 2���� �̻�)
            if (arr[ny][nx]->size < sh->size) {//����� Ŀ�� sh�� ��Ƹ���
                arr[ny][nx]->lived = false;//���� ��� ����
                arr[ny][nx] = sh;//sh�� ��Ƴ���: q�� ������ ��
                q.push(sh);
            }
            else sh->lived = false;//sh�� �۾Ƽ� ����: q�� ������ ���� ����
        }
        else {//������ �ƹ��� ��� ��Ƴ���: q�� ������ ��
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
