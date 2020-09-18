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

const int INF = 99999, VISITED = 1, UNVISITED = -1;
vector<vii> AdjList;
char str[250], *temp;
int N, u, v, dfsNumberCounter, dfsRoot, rootChildren;

vi dfs_low, dfs_num, dfs_parent, articulation_vertex;


void articulationPointandBridge(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
	for (ii v : AdjList[u]) {
		if (dfs_num[v.first] == UNVISITED) {
			dfs_parent[v.first] = u;
			if (u == dfsRoot)rootChildren++;
			articulationPointandBridge(v.first);

			if (dfs_low[v.first] >= dfs_num[u])
				articulation_vertex[u] = 1;
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
		}
		else if (v.first != dfs_parent[u]) {
			dfs_low[u] = min(dfs_low[u], dfs_num[v.first]);
		}
	}
}

int main() {
	while (1) {
		scanf("%d\n", &N); if (N == 0)break;
		AdjList.clear();
		for (int i = 0; i < N; i++) {
			vii temp; AdjList.push_back(temp);
		}
		while (1) {
			scanf("%d ", &u); if (u == 0)break;
			fgets(str, 250, stdin);
			temp = strtok(str, " ");
			while (temp != NULL) {
				v = (int)temp[0]-'0';
				AdjList[u - 1].push_back(ii(v - 1, 0));
				AdjList[v - 1].push_back(ii(u - 1, 0));
				temp = strtok(NULL, " ");
			}
		}
		dfsNumberCounter = 0; dfs_num.assign(N, UNVISITED); dfs_low.assign(N, 0);
		dfs_parent.assign(N, 0); articulation_vertex.assign(N, 0);
		for (int i = 0; i < N; i++) {
			if (dfs_num[i] == UNVISITED) {
				dfsRoot = i; rootChildren = 0; articulationPointandBridge(i);
				articulation_vertex[dfsRoot] = (rootChildren > 1);
			}
		}
		int ctr = 0;
		for (int i = 0; i < N; i++) {
			if (articulation_vertex[i])ctr++;
		}
		printVector(articulation_vertex);
		printf("Result: %d\n", ctr);
	}
}