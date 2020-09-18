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
int n, m, dfsNumberCounter, numSCC;
char temp1[30], temp2[30], nameList[30][30];
vi dfs_num, dfs_low, S, visited;

int nameIdx(char name[30]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(name, nameList[i]) == 0)return i;
	}
	return -1;
}

void tarjanSCC(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
	S.push_back(u); visited[u] = 1;
	for (ii v : AdjList[u]) {
		if (dfs_num[v.first] == UNVISITED)
			tarjanSCC(v.first);
		if (visited[v.first])
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
	}
	if (dfs_low[u] == dfs_num[u]) {
		int ctr = 0;
		while (1) {
			ctr += 1; if (ctr != 1)printf(", ");
			int v = S.back(); S.pop_back(); visited[v] = 0;
			printf("%s", nameList[v]);
			if (u == v) break;
		}
		printf("\n");
	}
}

int main() {
	int setNo = 0;
	while (1) {
		scanf("%d %d\n", &n, &m); if (n == 0 && m == 0)break;
		setNo += 1; if (setNo != 1)printf("\n");

		int ctr = 0;
		AdjList.clear(); memset(nameList, '0', sizeof(nameList));
		for (int i = 0; i < n; i++) {
			vii temp; AdjList.push_back(temp);
		}
		for (int i = 0; i < m; i++) {
			scanf("%s %s\n", &temp1, &temp2);
			int u = nameIdx(temp1);
			if (u == NOT_FOUND) {
				strcpy(nameList[ctr], temp1); u = ctr; ctr++;
			}
			int v = nameIdx(temp2);
			if (v == NOT_FOUND) {
				strcpy(nameList[ctr], temp2); v = ctr; ctr++;
			}
			AdjList[u].push_back(ii(v, 0));
		}int V = n;
		dfs_num.assign(V, UNVISITED); dfs_low.assign(V, 0); visited.assign(V, 0);
		dfsNumberCounter = numSCC = 0;
		printf("Calling circles for data set %d:\n", setNo);
		for (int i = 0; i < V; i++)
			if (dfs_num[i] == UNVISITED)
				tarjanSCC(i);
	}
}