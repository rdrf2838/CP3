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
int T, v, e, f, t;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &v, &e);
		AdjList.clear();
		for (int i = 0; i < v; i++) {
			vii temp; AdjList.push_back(temp);
		}
		for (int i = 0; i < e; i++) {
			scanf("%d %d", &f, &t);
			AdjList[f].push_back(ii(t, 0));
			AdjList[t].push_back(ii(f, 0));

		}
		vi color(v, INF);
		int totalsum = 0; bool isBi = true;
		for (int i = 0; i < v; i++) {
			if (!isBi) {
				printf("-1\n");
				break;
			}
			if (color[i] == INF) {
				queue<int> q; q.push(i);
				color[i] = 0;
				isBi = true;
				vi visited;
				while (!q.empty() && isBi) {
					int u = q.front(); q.pop(); visited.push_back(u);
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
				int sum = 0;
				if (visited.size() == 1) {
					sum = 1;
				}
				else {
					for (int u : visited) {
						sum += color[u];
					}
					int complement = visited.size() - sum;
					sum = min(sum, complement);
				}
				totalsum += sum;
			}
		}if (isBi)printf("%d\n", totalsum);
	}
}