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



vi dfs_num;
vi dfs_removed;
vector<vii> AdjList;
int T, N, temp;


void dfs(int u) {
	dfs_num[u] = 1;//visited
	for (int j = 0; j < AdjList[u].size(); j++) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == -1)//unvisited
			dfs(v.first);
	}
}

void dfsrmv(int u, int rmv) {
	dfs_removed[u] = 1;
	for (int j = 0; j < AdjList[u].size(); j++) {
		ii v = AdjList[u][j];
		if (dfs_removed[v.first] == -1 && v.first != rmv)
			dfsrmv(v.first, rmv);
	}
}

void printspacer(int n) {
	printf("+");
	for (int i = 0; i < 2 * n - 1; i++) {
		printf("-");
	}	printf("+\n");
}

void printdfs(vi orjlist) {
	printspacer(N);
	printf("|");
	for (int currint : orjlist) {
		currint == 1 ? printf("Y|") : printf("N|");
	}printf("\n");
	printspacer(N);
}

void printdfs(vi orjlist, vi nextlist) {
	//printVector(orjlist);
	//printVector(nextlist);
	printf("|");
	for (int i = 0; i < orjlist.size(); i++) {
		if (orjlist[i] == 1 && nextlist[i] == -1) {
			printf("Y|");
		}
		else {
			printf("N|");
		}
	}printf("\n");
	printspacer(N);
}

void printans() {
	dfs(0);
	printdfs(dfs_num);
	for (int i = 1; i < N; i++) {
		dfs_removed.clear();
		for (int j = 0; j < N; j++)dfs_removed.push_back(-1);
		dfsrmv(0, i);
		printdfs(dfs_num, dfs_removed);
	}
}




int main() {
	scanf("%d", &T);
	for(int i=1; i<=T; i++) {
		AdjList.clear();
		dfs_num.clear();
		scanf("%d", &N);
		for (int r = 0; r < N; r++) {
			dfs_num.push_back(-1);
			vii pairList;
			for (int c = 0; c < N; c++) {
				scanf("%d", &temp);
				if (temp) pairList.push_back(ii(c, 0));
			}
			AdjList.push_back(pairList);
		}
		printf("Case %d:\n", i);
		printans();
	}
}

