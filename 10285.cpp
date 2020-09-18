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
#include <bitset>

using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
const int VISITED = 1, UNVISITED = -1, INF = 1000000000, MAX_V = 300;
int xl[] = { 1, -1, 0, 0 };
int yl[] = { 0,0,-1,1 };
class UnionFind {
private:
	vi p, rank, setSize;
	int numSets;
public:
	UnionFind(int N) {
		setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
		p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i;
	}
	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) {
			numSets--;
			int x = findSet(i), y = findSet(j);
			// rank is used to keep the tree short
			if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
			else {
				p[x] = y; setSize[y] += setSize[x];
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	}
	int numDisjointSets() { return numSets; }
	int sizeOfSet(int i) { return setSize[findSet(i)]; }
};
void printArray(int a[], int n) {
	for (int* i = a; i < a + n; i++) {
		if (i != a) {
			printf(" ");
		}
		printf("%d", *i);
	}
	printf("\n");
}void printArray(double a[], int n) {
	for (double* i = a; i < a + n; i++) {
		if (i != a) {
			printf(" ");
		}
		printf("%lf", *i);
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
void printAdjList(vector<vi> AdjList) {
	int i = 0;
	for (vi currpairlist : AdjList) {
		printf("%d: ", i);
		for (int currpair : currpairlist) {
			printf("(%d) ", currpair);
		}
		printf("\n");
		i++;
	}
}



int N, R, C, height[101][101], dist[101][101];
char str[50];
int isValid(int r, int c) {
	return(0 <= r && r < R && 0 <= c && c < C);
}
int dfs(int r, int c) {
	if (dist[r][c] != -1)return dist[r][c];

	int maxDist = 0;
	for (int i = 0; i < 4; i++) {
		int r2 = r + yl[i], c2 = c + xl[i];
		if (isValid(r2, c2) && height[r2][c2] < height[r][c]) 
			maxDist = max(maxDist, dfs(r2, c2) + 1);
	}
	return dist[r][c] = maxDist;
}
int main() {
	scanf("%d\n", &N);
	while (N--) {
		scanf("%s %d %d\n", &str, &R, &C);
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf("%d", &height[i][j]);
			}
		}
		memset(dist, -1, sizeof(dist));
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				if (dist[i][j] == -1)dfs(i, j);
		int maxDist = 0;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				maxDist = max(maxDist, dist[i][j]);
		printf("%s: %d\n", str, maxDist + 1);
		//for (int i = 0; i < R; i++)printArray(dist[i], C);
	}
}


