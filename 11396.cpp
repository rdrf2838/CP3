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

int V, a, b;

int main() {
	while (1) {
		scanf("%d", &V); if (V == 0)break;
		AdjList.clear();
		for (int i = 0; i < V; i++) {
			vii temp; AdjList.push_back(temp);
		}
		while (1) {
			scanf("%d %d", &a, &b); if (a == 0 && b == 0)break;
			AdjList[a - 1].push_back(ii(b - 1, 0));
			AdjList[b - 1].push_back(ii(a - 1, 0));
		}
		queue<int>q; q.push(0);
		vi colour(V, INF); colour[0] = 0;
		bool isBi = true;
		while (!q.empty() && isBi) {
			int u = q.front(); q.pop();
			for (ii v : AdjList[u]){
				if (colour[v.first] == INF) {
					colour[v.first] = 1 - colour[u];
					q.push(v.first);
				}
				else if (colour[v.first] == colour[u]) {
					isBi = false; break;
				}
			}
		}
		isBi?printf("YES\n"):printf("NO\n");

	}
}