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

//row, column, neg-left, dir
//dir: 0 - from left, 1 - from right, 2 - from top
int N, k, memo[80][80][10][4], arr[80][80];


//generic dynamic programming structure!!
int dfs(int row, int col, int neg_rem, int dir) {

	//if invalid, prune
	if ((row > N - 1) || (row < 0) || (col < 0) || (col > N - 1) || (neg_rem < 0))return -INF;

	//if memoized, return answer
	int& local = memo[row][col][neg_rem][dir];
	if (local != -1)return local;

	//if reached final state, evaluate final state and memoize
	if ((row == N - 1) && (col == N - 1)) {
		if ((arr[row][col] < 0) && (neg_rem <= 0))return -INF;
		return local = arr[row][col];
	}

	//change variables if necessary, then evaluate next vertices
	int val = -INF, neg_rem2 = neg_rem;
	if (arr[row][col] < 0) neg_rem2--;

	if ((dir == 0) || (dir == 2))val = max(val, dfs(row, col + 1, neg_rem2, 0));
	if ((dir == 1) || (dir == 2))val = max(val, dfs(row, col - 1, neg_rem2, 1));
	val = max(val, dfs(row + 1, col, neg_rem2, 2));

	return local = val + arr[row][col];
}

int main() {
	int caseNum = 1;
	int negNum = (-INF) / 10;
	while (1) {
		scanf("%d %d", &N, &k); if (N == 0 && k == 0)break;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &arr[i][j]);
		memset(memo, -1, sizeof(memo));

		int ans = dfs(0, 0, k, 2);

		if (ans < negNum)printf("Case %d: impossible\n", caseNum);
		else printf("Case %d: %d\n", caseNum, ans);

		caseNum++;
	}
}


