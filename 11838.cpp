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

const int VISITED = 1, NOT_FOUND = -1, UNVISITED = -1;
vector<vii> AdjList;
int N, M, V, W, P, dfsNumberCounter, numSCC;

vi dfs_num, dfs_low, S, visited;
void tarjanSCC(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
	S.push_back(u); // stores u in a vector based on order of visitation
	visited[u] = 1;
	for (int j = 0; j < (int)AdjList[u].size(); j++) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == UNVISITED)
			tarjanSCC(v.first);
		if (visited[v.first]) // condition for update
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
	}
	if (dfs_low[u] == dfs_num[u]) { // if this is a root (start) of an SCC
		++numSCC;
		//printf("SCC %d:", ++numSCC); // this part is done after recursion
		while (1) {
			int v = S.back(); S.pop_back(); visited[v] = 0;
			//printf(" %d", v);
			if (u == v) break;
		}
		//printf("\n");
	}
}
int main() {
	while (1) {
		scanf("%d %d", &N, &M); if (N == 0 && M == 0)break;
		AdjList.clear();
		for (int i = 0; i < N; i++) {
			vii temp; AdjList.push_back(temp);
		}
		while (M--) {
			scanf("%d %d %d", &V, &W, &P);
			if (P == 1) {
				AdjList[V - 1].push_back(ii(W - 1, 0));
			}
			else {
				AdjList[V - 1].push_back(ii(W - 1, 0));
				AdjList[W - 1].push_back(ii(V - 1, 0));
			}
		}
		dfs_num.assign(N, UNVISITED); dfs_low.assign(N, 0); visited.assign(N, 0);
		dfsNumberCounter = numSCC = 0;
		for (int i = 0; i < N; i++)
			if (numSCC<2&&dfs_num[i] == UNVISITED)
				tarjanSCC(i);
		printf("%d\n", numSCC==1?1:0);


	}
}