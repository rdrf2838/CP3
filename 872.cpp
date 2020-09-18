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
int T, N;
const int VISITED = 1;
const int UNVISITED = -1;
vector<vii> AdjList;
vector<char> cList;
vi dfs_num;
vi order;
void dfs(int u) {
	dfs_num[u] = VISITED;
	for (ii v : AdjList[u]) {
		if (dfs_num[v.first] == UNVISITED)dfs(v.first);
	}
	order.push_back(u);
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("\n");
		char str1[50]; AdjList.clear(); cList.clear(); order.clear();
		fgets(str1, 50, stdin);
		char* token = strtok(str1, " "); N = 0;
		while (token != NULL) {
			N += 1;
			cList.push_back(*token);
			token = strtok(NULL, " ");
		}
		sort(cList.begin(), cList.end());
		for (int i = 0; i < N; i++) {
			vii temp;
			AdjList.push_back(temp);
		}
		char str2[1500];
		fgets(str2, 1500, stdin);
		token = strtok(str2, " ");
		while (token != NULL) {
			int u = find(cList.begin(), cList.end(), token[0]) - cList.begin();
			int v = find(cList.begin(), cList.end(), token[2]) - cList.begin();
			AdjList[u].push_back(ii(v, 0));
			token = strtok(NULL, " ");
		}
		dfs_num.assign(N, UNVISITED);
		for (int i = 0; i < N; i++) {
			if (dfs_num[i] == UNVISITED) {
				dfs(i);
			}
		}
		printVector(order);
		//printAdjList(AdjList);
	}
}
