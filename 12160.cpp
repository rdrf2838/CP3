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

int L, U, R, RV[12], memo[10000];

int adder(int u, int v) {
	return (u + v) % 10000;
}

int main() {
	int caseNo = 0;
	while (1) {
		caseNo++;
		scanf("%d %d %d", &L, &U, &R); if (L == 0 && R == 0 && U == 0)break;
		for (int i = 0; i < R; i++) {
			scanf("%d", &RV[i]);
		}

		memset(memo, UNVISITED, sizeof(memo));
		memo[L] = 0; int dist = -1;
		queue<int> q; q.push(L);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			//printf("Visiting: %d\n", u);
			if (u == U) { dist = memo[u]; break; }
			for (int i = 0; i < R; i++) {
				int v = adder(u, RV[i]);
				if (memo[v] == UNVISITED) {
					//printf("From %d visiting %d\n", u, v);
					memo[v] = memo[u] + 1;
					q.push(v);
				}
			}
		}
		printf("Case %d: ", caseNo); dist == -1 ? printf("Permanently Locked\n") : printf("%d\n", dist);

	}
}