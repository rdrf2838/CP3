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
const int VISITED = 1, UNVISITED = -1, INF = 1000000000;
class UnionFind { // OOP style
private:
	vi p, rank; // remember: vi is vector<int>
	int disjSetCount;
public:
	UnionFind(int N) {
		rank.assign(N, 0); disjSetCount = N;
		p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i;
	}
	int setCount() { return disjSetCount; }
	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) { // if from different set
			disjSetCount--;
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) p[y] = x; // rank keeps the tree short
			else {
				p[x] = y;
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	}
};
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

int rowList[] = { 1,0,-1,0 };
int colList[] = { 0,1,0,-1 };
int R, C, mat[1005][1005], rows, cols, r, c, temp;

int isValid(int rowNum, int colNum) {
	if (0 <= rowNum && rowNum < R && 0 <= colNum && colNum < C)return 1;
	else return 0;
}

int main() {
	while (1) {
		scanf("%d %d", &R, &C); if (R == 0 && C == 0)break;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				mat[i][j] = UNVISITED;
		scanf("%d", &rows);
		while (rows--) {
			scanf("%d", &r);
			scanf("%d", &cols);
			while (cols--) {
				scanf("%d", &c);
				mat[r][c] = INF;
			}
		}

		/*for (int i = 0; i <= R; i++) {
			printArray(mat[i], C+1);
		}*/
		int startr, startc, endr, endc;
		scanf("%d %d %d %d", &startr, &startc, &endr, &endc);
		mat[startr][startc] = 0;
		queue<int> q; q.push(startr); q.push(startc);
		while (!q.empty()) {
			int currr = q.front(); q.pop();
			int currc = q.front(); q.pop();
			if (currr == endr && currc == endc)break;
			for (int i = 0; i < 4; i++) {
				int nextRow = rowList[i] + currr;
				int nextCol = colList[i] + currc;
				if (isValid(nextRow, nextCol)) {
					if (mat[nextRow][nextCol] == UNVISITED) {
						mat[nextRow][nextCol] = mat[currr][currc] + 1;
						q.push(nextRow); q.push(nextCol);
					}
				}
			}
		}
		printf("%d\n", mat[endr][endc]);


		//for (int i = 0; i <= R; i++) {
		//	printArray(mat[i], C + 1);
		//}
	}
}