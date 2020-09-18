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
const int VISITED = 1;
const int UNVISITED = -1;
int T, N, AdjList[50050], u, v, dfs_num[50050], memo[50050], maxval, maxver, loopV;



int dfs(int u) {
	dfs_num[u] = VISITED;
	if (memo[u] != -1)return memo[u];
	int v = AdjList[u];
	if (dfs_num[v] == UNVISITED) {
		memo[u] = 1 + dfs(v);
	}
	else {
		loopV = v;
		memo[u] = 1;
	}
	if (u == loopV) {
		while (true) {
			int v = AdjList[u];
			if (loopV == v)break;
			memo[v] = memo[u];
			u = v;
		}
	}
	return memo[u];
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &u, &v);
			AdjList[u - 1] = v - 1;
		}
		memset(memo, -1, sizeof(memo));
		maxval = 0; maxver = 0;
		for (int i = 0; i < N; i++) {
			memset(dfs_num, -1, sizeof(dfs_num)); loopV = 50050;
			if (memo[i] == UNVISITED) {
				int nextval = dfs(i);
				if (nextval > maxval)maxver = i, maxval = nextval;
			}
		}
		printf("Case %d: %d\n", t, maxver + 1);
	}
}
