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

char grid[110][110];
int T, R, C;
int dr[] = { 1,0,-1, 0 };
int dc[] = { 0,1, 0,-1 };
int floodfill(int r, int c, int isfirst) { // returns the size of CC
	if (r < 0 || r >= R || c < 0 || c >= C) return 0; // outside grid
	if (isfirst) {
		if (grid[r][c] != 'x') return 0; // does not have color c1
	}
	else {
		if (grid[r][c] == '.') return 0; // does not have color c1
	}
	int ans = 1; // adds 1 to ans because vertex (r, c) has c1 as its color
	grid[r][c] = '.'; // now recolors vertex (r, c) to c2 to avoid cycling!
	for (int d = 0; d < 4; d++)
		ans += floodfill(r + dr[d], c + dc[d], 0);
	return ans; // the code is neat due to dr[] and dc[]
}

int main() {
	scanf("%d\n", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d\n", &R); C = R;
		for (int i = 0; i < R; i++) {
			fgets(grid[i], 110, stdin);
		}
		int counter = 0;
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				if (grid[r][c] == 'x') {
					floodfill(r, c, 1);
					counter += 1;
				}
			}
		}
		printf("Case %d: %d\n", t, counter);
	}
}
