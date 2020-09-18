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

const int VISITED = 1, UNVISITED = -1;
vector<vii> AdjList;
int n, m, u, v, dfsNumberCounter, dfsRoot, rootChildren;
vi dfs_low, dfs_num, dfs_parent, articulation_vertex, dfs_num2;

void dfs(int u, int skip) {
	if (u != skip) {
		dfs_num2[u] = VISITED;
		for (ii v : AdjList[u]) {
			if (dfs_num2[v.first] == UNVISITED) {
				dfs(v.first, skip);
			}
		}
	}
}

void articulationPointAndBridge(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
	for (int j = 0; j < (int)AdjList[u].size(); j++) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == UNVISITED) { // a tree edge
			dfs_parent[v.first] = u;
			if (u == dfsRoot) rootChildren++; // special case if u is a root
			articulationPointAndBridge(v.first);
			if (dfs_low[v.first] >= dfs_num[u]) // for articulation point
				articulation_vertex[u] = true; // store this information first
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]); // update dfs_low[u]
		}
		else if (v.first != dfs_parent[u]) // a back edge and not direct cycle
			dfs_low[u] = min(dfs_low[u], dfs_num[v.first]); // update dfs_low[u]
	}
}
int main() {
	while (1) {
		scanf("%d %d", &n, &m); if (n == 0 && m == 0)break;
		AdjList.clear();
		for (int i = 0; i < n; i++) {
			vii temp; AdjList.push_back(temp);
		}
		while (1) {
			scanf("%d %d", &u, &v); if (u == -1 && v == -1)break;
			AdjList[u].push_back(ii(v, 0));
			AdjList[v].push_back(ii(u, 0));
		}int V = n;
		dfsNumberCounter = 0; dfs_num.assign(V, UNVISITED); dfs_low.assign(V, 0);
		dfs_parent.assign(V, 0); articulation_vertex.assign(V, 0);
		for (int i = 0; i < V; i++)
			if (dfs_num[i] == UNVISITED) {
				dfsRoot = i; rootChildren = 0; articulationPointAndBridge(i);
				articulation_vertex[dfsRoot] = (rootChildren > 1);
			} // special case
		priority_queue<ii> targets;
		for (int i = 0; i < V; i++) {
			int birdctr = 1;
			if (articulation_vertex[i]) {
				dfs_num2.assign(V, UNVISITED);
				int ctr = 0;
				for (int j = 0; j < V; j++) {
					if (dfs_num2[j] == UNVISITED) {
						dfs(j, i); ctr++;
					}
				}
				birdctr = ctr - 1;
			}
			targets.push(ii(birdctr, -i));
		}
		for (int i = 0; i < m; i++) {
			ii u = targets.top(); targets.pop();
			printf("%d %d\n", -u.second, u.first);
		}printf("\n");
	}
}