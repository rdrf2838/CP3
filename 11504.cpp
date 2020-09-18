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
vector<vii> AdjList, AdjListRev;
vi dfs_num, dfs_low, S, visited;
int T, n, m, u, v, dfsNumberCounter, totalCount, numSCC;


int inList(int u, vector<int> v) {
	for (int curr : v) {
		if (curr == u)return 1;
	}
	return 0;
}

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
		//printf("SCC %d:", ++numSCC); // this part is done after recursion
		vi sccList, intoSCCList;
		while (1) {
			int v = S.back(); S.pop_back(); visited[v] = 0;
			sccList.push_back(v);
			for (ii currPair : AdjListRev[v]) {
				intoSCCList.push_back(currPair.first);
			}
			//printf(" %d", v);
			if (u == v) break;
		}
		//printf("\n");
		//printVector(sccList); printVector(intoSCCList);
		//printf("SCC size: %d SCCList size: %d\n", sccList.size(), intoSCCList.size());
		if (sccList.size() == 1 && intoSCCList.size() == 0)totalCount++;
		else {
			int inVec = 0;
			for (int v : intoSCCList) {
				if (!inList(v, sccList)) {
					inVec++; break;
				}
			}
			if (inVec == 0)totalCount++;
		}
	}
}

int main() {
	ofstream outFile; outFile.open("Test.txt");
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		AdjList.clear(); AdjListRev.clear();
		for (int i = 0; i < n; i++) {
			vii temp; AdjList.push_back(temp);
			vii temp2; AdjListRev.push_back(temp2);
		}
		while (m--) {
			scanf("%d %d", &u, &v);
			AdjList[u - 1].push_back(ii(v - 1, 0));
			AdjListRev[v - 1].push_back(ii(u - 1, 0));
		}
		int V = n;
		totalCount = 0;
		dfs_num.assign(V, UNVISITED); dfs_low.assign(V, 0); visited.assign(V, 0);
		dfsNumberCounter = numSCC = 0;
		for (int i = 0; i < V; i++)
			if (dfs_num[i] == UNVISITED)
				tarjanSCC(i);
		printf("%d\n", totalCount);
		outFile << totalCount << "\n";
	}
	outFile.close();
}