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

int N, M, S;
char grid[105][105], query[70000];

struct Robot {
	int stickers = 0;
	pair<int, int> loc;
	char dir;
	void move(char action) {
		if (action == 'D') {
			if (dir == 'N')dir = 'L';
			else if (dir == 'L')dir = 'S';
			else if (dir == 'S')dir = 'O';
			else if (dir == 'O')dir = 'N';

			//grid[loc.second][loc.first] = dir;
			//for (int r = 0; r < N; r++) {
			//	printf("%s\n", grid[r]);
			//}
			//printf("\n");
		}
		if (action == 'E') {
			if (dir == 'N')dir = 'O';
			else if (dir == 'L')dir = 'N';
			else if (dir == 'S')dir = 'L';
			else if (dir == 'O')dir = 'S';
			//grid[loc.second][loc.first] = dir;
			//for (int r = 0; r < N; r++) {
			//	printf("%s\n", grid[r]);
			//}
			//printf("\n");
		}
		else if (action == 'F') {
			pair<int, int> motion;
			if (dir == 'N')motion.first = 0, motion.second = -1;
			if (dir == 'L')motion.first = 1, motion.second = 0;
			if (dir == 'S')motion.first = 0, motion.second = 1;
			if (dir == 'O')motion.first = -1, motion.second = 0;
			int x = loc.first + motion.first; int y = loc.second + motion.second;
			//printf("x0: %d y0: %d x: %d y: %d\n", loc.first, loc.second, x, y);

			if (0 <= x && x < M && 0 <= y && y < N) {
				char nextpos = grid[y][x];
				if (nextpos == '.') {
					loc.first = x, loc.second = y;
				}
				if (nextpos == '*') {
					grid[y][x] = '.';
					stickers += 1;
					loc.first = x, loc.second = y;
				}
			}
			//for (int r = 0; r < N; r++) {
			//	printf("%s\n", grid[r]);
			//}
			//printf("\n");

		}
	}
};



int main() {
	while (true) {
		Robot robot;
		scanf("%d %d %d\n", &N, &M, &S);
		if (N == 0 && M == 0 && S == 0)break;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				scanf("%c", &grid[r][c]);
				if (grid[r][c] == 'N' || grid[r][c] == 'S' ||
					grid[r][c] == 'L' || grid[r][c] == 'O') {
					robot.loc = pair<int, int>(c, r);
					robot.dir = grid[r][c];
					grid[r][c] = '.';
				}
			}
			scanf("\n");
		}
		fgets(query, 70000, stdin);
		for (int i = 0; i < S; i++) {
			char act = query[i];
			robot.move(act);
		}
		printf("%d\n", robot.stickers);
	}
}
