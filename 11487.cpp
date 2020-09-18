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
}
void printArray(double a[], int n) {
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

ii loc[30];
// i, j, food, length
int N, n, memo[12][12][30][144];
char arr[12][12];

int dfs(int i, int j, int food, int length) {
	if ((i < 0) || (i > N - 1) || (j < 0) || (j > N - 1) || (arr[i][j] == '#') || (length > 140))return 0;

	int& local = memo[i][j][food][length];

	if (local != -1)return local;

	int val = arr[i][j] - 'A';
	if (val == n - 1)return local = 1;
	if (val == food)return local = dfs(i, j, food + 1, length);

	int ways = 0;
	for (int k = 0; k < 4; k++) {
		int i2 = i + xl[k], j2 = j + xl[k];
		ways += dfs(i2, j2, food, length + 1);
	}
	return local = ways;
}

int main() {
	while (1) {
		scanf("%d\n", &N); if (N == 0)break;
		n = 0; memset(memo, -1, sizeof(memo));
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				scanf("%c", &arr[r][c]);
				if ((arr[r][c] != '.') && (arr[r][c] != '#')) {
					loc[n] = ii(r, c);
					n += 1;
				}
			}
			scanf("\n");
		}
		//for (int i = 0; i < N; i++)printArray(arr[i], N);
		//for (int i = 0; i < n; i++)printf("%d %d\n", loc[i].first, loc[i].second);
		dfs(loc[0].first, loc[0].second, 0, 0);
		for (int i = 0; i < 140; i++) {
			if (memo[loc[n - 1].first][loc[n - 1].second][n - 1][i] != -1) {
				cout << "ans:"<< memo[loc[n - 1].first][loc[n - 1].second][n - 1][i]<<"\n";
				break;
			}
		}
	}
}


