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
int V, u, v, l, dfsNumberCounter;
vi dfs_low, dfs_num, dfs_parent;
vii bridge_list;
void articulationPointAndBridge(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
	for (int j = 0; j < (int)AdjList[u].size(); j++) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == UNVISITED) { // a tree edge
			dfs_parent[v.first] = u;
			articulationPointAndBridge(v.first);
			if (dfs_low[v.first] > dfs_num[u]) // for bridge
				bridge_list.push_back(ii(min(u, v.first), max(u, v.first)));
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]); // update dfs_low[u]
		}
		else if (v.first != dfs_parent[u]) // a back edge and not direct cycle
			dfs_low[u] = min(dfs_low[u], dfs_num[v.first]); // update dfs_low[u]
	}
}

int main() {
	while (scanf("%d", &V) == 1) {
		AdjList.clear();
		for (int i = 0; i < V; i++) {
			vii temp; AdjList.push_back(temp);
		}
		for (int i = 0; i < V; i++) {
			scanf("%d (%d)", &u,&l);
			for (int j = 0; j < l; j++) {
				scanf("%d", &v);
				AdjList[u].push_back(ii(v, 0));
				AdjList[v].push_back(ii(u, 0));
			}
		}
		dfsNumberCounter = 0; dfs_num.assign(V, UNVISITED); dfs_low.assign(V, 0);
		dfs_parent.assign(V, 0); bridge_list.clear();
		for (int i = 0; i < V; i++)
			if (dfs_num[i] == UNVISITED) {
				articulationPointAndBridge(i);
			} // special case
		sort(bridge_list.begin(), bridge_list.end()); int sz = bridge_list.size();
		printf("%d critical links\n", sz);
		for (int i = 0; i < sz; i++) {
			ii u = bridge_list[i];
			printf("%d - %d\n", u.first, u.second);
		}printf("\n");
	}
}