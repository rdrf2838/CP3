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
int N, n, memo[12][12][30][144], dist[12][12], endVal[30];
char arr[12][12], arr2[12][12];

//int dfs(int i, int j, int food, int length) {
//	if ((i < 0) || (i > N - 1) || (j < 0) || (j > N - 1) || (arr[i][j] != '.') || (length > endVal[food]))return 0;
//	
//	//printf("i: %d j: %d food: %d length: %d\n", i, j, food, length);
//	//for (int i = 0; i < N; i++)printArray(arr[i], N);
//
//	int& local = memo[i][j][food][length];
//	if (local != -1)return local;
//
//	int val = arr[i][j] - 'A';
//	if (val == n - 1) return local = 1;
//	if (val == food)return local = dfs(i, j, food + 1, 0);
//
//	int ways = 0;
//
//	for (int k = 0; k < 4; k++) {
//		int i2 = i + xl[k], j2 = j + yl[k];
//		ways += dfs(i2, j2, food, length + 1);
//	}
//	return local = ways;
//}

int dfs(int i, int j, int food, int length) {
	if ((i < 0) || (i > N - 1) || (j < 0) || (j > N - 1) || ((arr[i][j] != '.') && ((arr[i][j] - 'A') != food)) || (length > endVal[food - 1]))return 0;

	int& local = memo[i][j][food][length];
	if (local != -1)return local;

	int val = arr[i][j] - 'A';
	if (val == food)return 1;

	int ways = 0;

	for (int k = 0; k < 4; k++) {
		int i2 = i + xl[k], j2 = j + yl[k];
		ways += dfs(i2, j2, food, length + 1);
	}
	return local = ways;
}

int main() {
	int caseNum = 1;
	while (1) {
		scanf("%d\n", &N); if (N == 0)break;
		n = 0; memset(memo, -1, sizeof(memo));
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				scanf("%c", &arr[r][c]);
				if ((arr[r][c] != '.') && (arr[r][c] != '#')) {
					int val = arr[r][c] - 'A';
					loc[val] = ii(r, c);
					n++;
				}
			}
			scanf("\n");
		}

		for (int i = 0; i < N; i++)for (int j = 0; j < N; j++)
			arr2[i][j] = arr[i][j];
		int food = 0; int ctr = 0; memset(endVal, -1, sizeof(endVal));
		while ((food < n - 1) && (ctr < 2 * n)) {
			ctr++;
			ii s = loc[food], t = loc[food + 1]; arr2[s.first][s.second] = '.';
			memset(dist, -1, sizeof(dist)); dist[s.first][s.second] = 0;
			queue<ii> q; q.push(s);
			while (!q.empty()) {
				ii u = q.front(); q.pop();
				if (u == t) {
					endVal[food] = dist[u.first][u.second];
					food++;
					break;
				}
				for (int j = 0; j < 4; j++) {
					ii v = ii(u.first + xl[j], u.second + yl[j]);
					if ((0 <= v.first) && (v.first < N) && (0 <= v.second) && (v.second < N)) {
						if ((dist[v.first][v.second] == -1) && ((arr2[v.first][v.second] == '.') || (arr2[v.first][v.second] == ((char)(food + 1 + 'A'))))) {
							q.push(v); dist[v.first][v.second] = dist[u.first][u.second] + 1;
						}
					}
				}
			}
		}
		if (endVal[n - 2] != -1) {
			int totWays = 1;
			int divisor = 20437;
			for (int i = 1; i < n; i++) {
				ii prevFoodLoc = loc[i - 1];
				arr[prevFoodLoc.first][prevFoodLoc.second] = '.';
				int partAns = dfs(prevFoodLoc.first, prevFoodLoc.second, i, 0);
				totWays = (totWays * (partAns % divisor)) % divisor;
			}
			int totDist = 0;
			for (int i = 0; i < n - 1; i++) {
				totDist += endVal[i];
			}
			printf("Case %d: %d %d\n", caseNum, totDist, totWays);
		}
		else if (n == 1) {
			printf("Case %d: 0 1\n", caseNum);
		}
		else {
			printf("Case %d: Impossible\n", caseNum);
		}
		caseNum++;
	}
}


