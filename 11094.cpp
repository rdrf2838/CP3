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
#include <stack>

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

int R, C, Kr, Kc;
char grid[25][25], land, water;

int dr[] = { 1,0,-1, 0 };
int dc[] = { 0,1, 0,-1 };
int floodfill(int r, int c, char c1, char c2) { // returns the size of CC
	if (r < 0 || r >= R) return 0; // outside grid
	if (c < 0) c = C - 1;
	if (c >= C) c = 0;
	if (grid[r][c] != c1) return 0; // does not have color c1
	int ans = 1; // adds 1 to ans because vertex (r, c) has c1 as its color
	grid[r][c] = c2; // now recolors vertex (r, c) to c2 to avoid cycling!
	for (int d = 0; d < 4; d++)
		ans += floodfill(r + dr[d], c + dc[d], c1, c2);
	return ans; // the code is neat due to dr[] and dc[]
}

int main() {
	while (scanf("%d %d\n", &R, &C) == 2) {
		for (int r = 0; r < R; r++) {
			fgets(grid[r], 25, stdin);
		}
		scanf("%d %d\n", &Kr, &Kc);
		land = grid[Kr][Kc]; water = (char)((int)land + 1);
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				if (grid[r][c] != land) {
					water = grid[r][c];
					c = C; r = R;
				}
			}
		}
		floodfill(Kr, Kc, land, water);
		int bestArea = 0;
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				if (grid[r][c] == land)
					bestArea = max(bestArea, floodfill(r, c, land, water));
			}
		}
		for (int i = 0; i < R; i++)
			printf("%s", grid[i]);

		printf("%d\n", bestArea);
	}
}
