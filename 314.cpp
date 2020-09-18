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

int M, N, grid[60][60], dirVisited[61][61][4], b1, b2, e1, e2, startDir, temp;
int rl[] = { -1,0,1,0 };
int cl[] = { 0,1,0,-1 };
char startDirStr[10];

struct state {
	int r, c, dir, dist;
};

int isValid(int r, int c) {
	if (0 < r && r < M && 0 < c && c < N) {
		int rl[] = { 0,-1,0,-1 };
		int cl[] = { 0,0,-1,-1 };
		for (int i = 0; i < 4; i++) {
			if (grid[r + rl[i]][c + cl[i]] == 1)return 0;
		}return 1;
	}return 0;
}

int main() {
	while (1) {
		scanf("%d %d", &M, &N); if (M == 0 && N == 0)break;
		for (int r = 0; r < M; r++)
			for (int c = 0; c < N; c++)
				scanf("%d", &grid[r][c]);
		memset(dirVisited, UNVISITED, sizeof(dirVisited));
		scanf("%d %d %d %d %s", &b1, &b2, &e1, &e2, &startDirStr);
		char c = startDirStr[0];
		if (c == 'n')startDir = 0;
		else if (c == 'e')startDir = 1;
		else if (c == 's')startDir = 2;
		else if (c == 'w')startDir = 3;

		state init = { b1,b2,startDir,0 };

		queue<state> q; q.push(init);
		dirVisited[b1][b2][startDir] = 1;
		int answer = -1;

		while (!q.empty()) {
			state u = q.front(); q.pop();
			//printf("Visiting State: r: %d c: %d dir: %d dist: %d\n", u.r, u.c, u.dir, u.dist);
			if (u.r == e1 && u.c == e2) {
				answer = u.dist;
				break;
			}
			for (int i = 3; i > 0; i--) {
				int nextr = u.r + i * rl[u.dir];
				int nextc = u.c + i * cl[u.dir];
				int isValid2 = 1;
				if (i == 3) {
					isValid2 = isValid(u.r + rl[u.dir], u.c + cl[u.dir]);
				}
				//printf("nextr: %d nextc: %d isvalid: %d\n", nextr, nextc, isValid(nextr, nextc));
				if (isValid2&&isValid(nextr, nextc) && dirVisited[nextr][nextc][u.dir] == UNVISITED) {
					state v = { nextr, nextc, u.dir, u.dist + 1 };
					dirVisited[v.r][v.c][v.dir] = VISITED;
					q.push(v);
				}
			}
			int x[] = { -1,1 };
			for (int i = 0; i < 2; i++) {
				int nextDir = u.dir + x[i];
				if (nextDir < 0)nextDir += 4;
				else if (nextDir == 4)nextDir -= 4;
				if (dirVisited[u.r][u.c][nextDir] == UNVISITED) {
					//printf("nextDir: %d\n", nextDir);
					dirVisited[u.r][u.c][nextDir] = VISITED;
					state v = { u.r,u.c,nextDir,u.dist + 1 };
					q.push(v);
				}
			}
		}
		if (answer == -1)printf("-1\n");
		else printf("%d\n", answer);

		
	}
}