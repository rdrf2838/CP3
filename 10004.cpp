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

const int INF = 99999;
vector<vii> AdjList;
int n, l, u, v;
int main() {
	while (true) {
		scanf("%d", &n); if (n == 0)break;
		AdjList.clear();
		for (int i = 0; i < n; i++) {
			vii temp; AdjList.push_back(temp);
		}
		scanf("%d", &l);
		for (int i = 0; i < l; i++) {
			scanf("%d %d", &u, &v);
			AdjList[u].push_back(ii(v, 0));
		}
		queue<int> q; q.push(0);
		vi color(n, INF); color[0] = 0;
		bool isBi = true;
		while (!q.empty() && isBi) {
			int u = q.front(); q.pop();
			for (ii v : AdjList[u]) {
				if (color[v.first] == INF) {
					color[v.first] = 1 - color[u];
					q.push(v.first);
				}
				else if (color[v.first] == color[u]) {
					isBi = false; break;
				}
			}
		}
		isBi ? printf("BICOLORABLE.\n") : printf("NOT BICOLORABLE.\n");
	}
}