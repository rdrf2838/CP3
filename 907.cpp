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
void printArray(char a[], int n) {
	for (char* i = a; i < a + n; i++) {
		if (i != a) {
			printf(" ");
		}
		printf("%c", *i);
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

int N, K, arr[700], temp, memo[700][400];

int dist(int a, int b) {
	if (a == 0)return arr[b - 1];
	return arr[b - 1] - arr[a - 1];
}

int dfs(int pos, int night_left) {
	if (memo[pos][night_left] != -1)return memo[pos][night_left];
	if (pos == N + 1) {
		if (night_left == -1)return memo[pos][night_left] = -1;
		else return memo[pos][night_left] = INF;
	}
	else if ((night_left == -1) || (pos >= N + 1)) return memo[pos][night_left] = INF;
	int bestDist = INF;
	for (int i = pos + 1; i < N + 2; i++) {
		int nd = dfs(i, night_left - 1);
		if (nd != INF)
			bestDist = min(bestDist, max(nd, dist(pos, i)));
	}
	return memo[pos][night_left] = bestDist;
}

int main() {
	while (scanf("%d %d\n", &N, &K) == 2) {
		memset(memo, -1, sizeof(memo));
		scanf("%d\n", &arr[0]);
		for (int i = 1; i < N + 1; i++) {
			scanf("%d\n", &temp);
			arr[i] = arr[i - 1] + temp;
		}
		int ans = dfs(0, K);
		printf("%d\n", ans);
		//printArray(arr, N + 1);
		//cout << dist(0, 2) << "\n";
	}
}


