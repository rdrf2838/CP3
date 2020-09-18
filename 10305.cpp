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
int n, m, u, v;
const int VISITED = 1;
const int UNVISITED = -1;
vector<vii> AdjList;
vi dfs_num;
vi order;
void dfs(int u) {
	dfs_num[u] = VISITED;
	for (ii v : AdjList[u]) {
		if (dfs_num[v.first] == UNVISITED)
			dfs(v.first);
	}
	order.push_back(u);
}
int main() {
	while (true) {
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)break;

		dfs_num.clear(); AdjList.clear(); order.clear();
		dfs_num.assign(n, UNVISITED);

		for (int i = 0; i < n; i++) {
			vii temp; AdjList.push_back(temp);
		}
		while (m--) {
			scanf("%d %d", &u, &v);
			AdjList[u - 1].push_back(ii(v - 1, 0));
		}
		for (int i = 0; i < n; i++) {
			if (dfs_num[i] == UNVISITED)dfs(i);
		}
		for (int i = n - 1; i >= 0; i--) {
			printf("%d ", order[i] + 1);
		}printf("\n");
	}
}
