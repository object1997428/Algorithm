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
#define left (i<<1)
#define right (i<<1|1)
#define mid (s+e)/2

int Q, N, M;
typedef struct Node {
	int id;
	Node* prev;
	Node* next;
};
Node node[100001];
int nodeCnt;
Node* getNode(int id) {
	node[nodeCnt].id = id;
	node[nodeCnt].prev = NULL;
	node[nodeCnt].next = NULL;
	return &node[nodeCnt++];
}
class List {
public:
	Node head, tail;
	int size;

	List() = default;

	void init() {
		head.id = -1, tail.id = -1;
		head.next = &tail; tail.prev = &head;
		head.prev = NULL; tail.next = NULL;
		size = 0;
	}

	Node* insert(int data, Node* iter) {//iter 앞에 위치하게 됨
		Node* pre = iter->prev;
		Node* ptr = getNode(data);

		pre->next->prev = ptr;
		ptr->next = pre->next;

		pre->next = ptr;
		ptr->prev = pre;

		size++;
		return pre->next;
	}

	Node* insertNode(Node* ptr, Node* iter) {//iter 앞에 위치하게 됨
		Node* pre = iter->prev;

		pre->next->prev = ptr;
		ptr->next = pre->next;

		pre->next = ptr;
		ptr->prev = pre;

		size++;
		return pre->next;
	}

	Node* erase(Node* ptr) {
		Node* pre = ptr->prev;
		if (pre->next == &tail) return pre->next;

		pre->next->next->prev = pre;
		pre->next = pre->next->next;

		size--;
		return pre->next;
	}
};
List l1[100001];
Node* id2node[100001];

void init() {
	cin >> N >> M;
	for (int i = 0; i <= N; i++) l1[i].init();
	for (int i = 0; i < M; i++) {
		int to; cin >> to;
		Node* ptr = l1[to].insert(i + 1, &l1[to].tail);
		id2node[i + 1] = ptr;
	}
}

int moveAll(int src, int dst) {//dstCnt
	l1[src].tail.prev->next = l1[dst].head.next;
	l1[dst].head.next->prev = l1[src].tail.prev;

	l1[dst].head.next = l1[src].head.next;
	l1[src].head.next->prev = &l1[dst].head;

	l1[src].head.next = &l1[src].tail;
	l1[src].tail.prev = &l1[src].head;

	l1[dst].size += l1[src].size;
	l1[src].size = 0;
	return l1[dst].size;
}

int moveFront(int src, int dst) {//dstCnt

	bool isNext = true;
	if (!(l1[src].size == 0)) {//src->dst
		Node* ptr = l1[src].head.next;
		l1[src].erase(ptr);
		l1[dst].insertNode(ptr, l1[dst].head.next);
	}
	else isNext = false;

	if (l1[dst].size > 0) {
		Node* ptr = l1[dst].head.next;
		if (isNext) ptr = ptr->next;
		if (ptr != &l1[dst].tail) {
			l1[dst].erase(ptr);
			l1[src].insertNode(ptr, l1[src].head.next);
		}
	}

	return l1[dst].size;
}

int divide(int src, int dst) {
	int k = l1[src].size / 2;
	if (k == 0) return l1[dst].size;

	// lastNode->dst
	Node* lastNode = &l1[src].head;
	for (int i = 0; i < k; i++) {
		lastNode = lastNode->next;
	}
	Node* lastNextNode = lastNode->next;
	lastNode->next = l1[dst].head.next;
	l1[dst].head.next->prev = lastNode;

	//dst->firstNode
	l1[dst].head.next = l1[src].head.next;
	l1[src].head.next->prev = &l1[dst].head;

	//head->lastNextNode
	l1[src].head.next = lastNextNode;
	lastNextNode->prev = &l1[src].head;

	l1[dst].size += k;
	l1[src].size -= k;
	return l1[dst].size;
}

int getInfoGift(int num) {
	Node* ptr = id2node[num];
	int a = ptr->prev->id;
	int b = ptr->next->id;
	return a + 2 * b;
}

int getInfoBelt(int num) {
	int a = l1[num].head.next->id;
	int b = l1[num].tail.prev->id;
	int c = l1[num].size;
	return a + 2 * b + 3 * c;
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 100) init();
		else if (q == 200) {
			int src, dst; cin >> src >> dst;
			int dstCnt = moveAll(src, dst);
			cout << dstCnt << endl;
		}
		else if (q == 300) {
			int src, dst; cin >> src >> dst;
			int dstCnt = moveFront(src, dst);
			cout << dstCnt << endl;
		}
		else if (q == 400) {
			int src, dst; cin >> src >> dst;
			int dstCnt = divide(src, dst);
			cout << dstCnt << endl;
		}
		else if (q == 500) {
			int num; cin >> num;
			cout << getInfoGift(num) << endl;
		}
		else if (q == 600) {
			int num; cin >> num;
			cout << getInfoBelt(num) << endl;
		}
		else assert(0);
	}

	//fclose(stdin);
}