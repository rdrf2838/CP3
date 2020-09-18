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
vector<vii> AdjList;
int T; char temp1, temp2, N, tempstr[40];

void dfs(int u) {
	dfs_num[u] = 1;
	for (int j = 0; j < AdjList[u].size(); j++) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == -1) {
			dfs(v.first);
		}
	}
}

int converter(char c) {
	return (int)c - 65;
}
int main() {
	//scanf("%d\n", &T);
	//fgets(tempstr, 40, stdin);
	//while (true) {
	//	fgets(tempstr, 40, stdin);
	//	if (tempstr[0] == '\n') {
	//		printf("/n");
	//	}else printf("Str: %s", tempstr);
	//}

	scanf("%d\n",&T);
	for(int t=0; t<T; t++) {
		if (t > 0)printf("\n");
		dfs_num.clear(); AdjList.clear();
		fgets(tempstr, 40, stdin);
		temp1 = tempstr[0];
		N = converter(temp1) + 1;

		for (int i = 0; i < N; i++) {
			dfs_num.push_back(-1);
			vii list;
			AdjList.push_back(list);
		}

		while (fgets(tempstr, 40, stdin)!=EOF) {
			if (tempstr[0] == '\n')break;
			int u = converter(tempstr[0]);
			int v = converter(tempstr[1]);
			AdjList[u].push_back(ii(v, 0));
			AdjList[v].push_back(ii(u, 0));
		}
		int counter = 0;
		for (int i = 0; i < N; i++) {
			if (dfs_num[i] == -1) {
				counter += 1;
				dfs(i);
			}
		}
		printf("%d\n", counter);

	}
}

