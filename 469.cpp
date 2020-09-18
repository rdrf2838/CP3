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

int T, R, C, x, y;
char grid[999][101], temp[101];
int dr[] = { 1,1,0,-1,-1,-1, 0, 1 }; // trick to explore an implicit 2D grid
int dc[] = { 0,1,1, 1, 0,-1,-1,-1 }; // S,SE,E,NE,N,NW,W,SW neighbors
int floodfill(int r, int c, char c1, char c2) { // returns the size of CC
	if (r < 0 || r >= R || c < 0 || c >= C) return 0; // outside grid
	if (grid[r][c] != c1) return 0; // does not have color c1
	int ans = 1; // adds 1 to ans because vertex (r, c) has c1 as its color
	grid[r][c] = c2; // now recolors vertex (r, c) to c2 to avoid cycling!
	for (int d = 0; d < 8; d++)
		ans += floodfill(r + dr[d], c + dc[d], c1, c2);
	return ans; // the code is neat due to dr[] and dc[]
}
int main() {
	scanf("%d\n", &T);
	for(int t=1;t<=T;t++) {
		if (t > 1)printf("\n");
		int i = 0; int total = 0;
		while (fgets(grid[i], 101, stdin)) {
			if (grid[i][0] == '\n')break;
			if (grid[i][0] == 'W' || grid[i][0] == 'L') R += 1;
			else {
				C = strlen(grid[0]) - 1;
				sscanf(grid[i], "%d %d", &y, &x);
				printf("%d\n", floodfill(y-1, x-1, 'W', '.'));
				floodfill(y - 1, x - 1, '.', 'W');
			}
			i += 1;
		}
	}
}
