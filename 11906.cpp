#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <fstream>
#include <queue>

using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

void printArray(int a[], int n) {
	for (int* i = a; i < a + n; i++) {
		if (i != a) {
			printf(" ");
		}
		printf("%d", *i);
	}
	printf("\n");
}
void printVector(vector<int> vec) {
	for (int ci : vec) {
		printf("%d ", ci);
	}
	printf("\n");
}
void printAdjList(vector<vii> AdjList) {
	int i = 0;
	for (vii currpairlist : AdjList) {
		printf("%d: ", i);
		for (ii currpair : currpairlist) {
			printf("(%d %d) ", currpair.first, currpair.second);
		}
		printf("\n");
		i++;
	}
}

int board[105][105], T, R, C, M, N, W, tempx, tempy, xmove[8], ymove[8], odd, even;

bool isvalid(int x, int y) {
	if (0 <= x && x < C && 0 <= y && y < R && board[y][x] != -1) {
		return true;
	}
	else return false;
}

bool notvisited(int x, int y) {
	if (0 <= x && x < C && 0 <= y && y < R && board[y][x] == 0) {
		return true;
	}
	else return false;
}

void jumper(int x, int y) {
	//printf("Checking: X: %d Y: %d\n", x, y);
	if (notvisited(x, y)) {
		board[y][x] = 1;
		int count = 0;
		for (int i = 0; i < 8; i++) {
			if (isvalid(x + xmove[i], y + ymove[i])) {
				count += 1;
				jumper(x + xmove[i], y + ymove[i]);
			}
		}
		if ((M == 0) || (N == 0) || (M == N))count /= 2;
		if (count % 2)odd++;
		else even++;
	}


}
int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		odd = 0; even = 0;
		scanf("%d %d %d %d %d", &R, &C, &M, &N, &W);
		xmove[0] = M; xmove[1] = N; xmove[2] = M; xmove[3] = N;
		xmove[4] = -M; xmove[5] = -N; xmove[6] = -M; xmove[7] = -N;
		ymove[0] = N; ymove[1] = M; ymove[2] = -N; ymove[3] = -M;
		ymove[4] = N; ymove[5] = M; ymove[6] = -N; ymove[7] = -M;
		memset(board, 0, sizeof(board));
		for (int i = 0; i < W; i++) {
			scanf("%d %d", &tempx, &tempy);
			board[tempy][tempx] = -1;
		}
		jumper(0, 0);
		for (int i = 0; i < R; i++) {
			printArray(board[i], C);
		}printf("\n");
		printf("Case %d: %d %d\n", t, even, odd);

	}
}
