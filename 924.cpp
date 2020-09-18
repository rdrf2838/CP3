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
const int VISITED = 1, UNVISITED = -1, INF = 1000000000;
class UnionFind { // OOP style
private:
	vi p, rank; // remember: vi is vector<int>
	int disjSetCount;
public:
	UnionFind(int N) {
		rank.assign(N, 0); disjSetCount = N;
		p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i;
	}
	int setCount() { return disjSetCount; }
	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) { // if from different set
			disjSetCount--;
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) p[y] = x; // rank keeps the tree short
			else {
				p[x] = y;
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	}
};
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

vector<vii>AdjList;

int E, N, T, temp, source;

int main() {
	scanf("%d", &E);
	for (int i = 0; i < E; i++) {
		vii temp; AdjList.push_back(temp);
	}
	for (int i = 0; i < E; i++) {
		scanf("%d", &N);
		for (int j = 0; j < N; j++) {
			scanf("%d", &temp);
			AdjList[i].push_back(ii(temp, 0));
		}
	}
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &source);
		vi dist(E, INF); dist[source] = 0;
		vi best(E, 0);
		queue<int> q; q.push(source);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (ii v : AdjList[u]) {
				if (dist[v.first] == INF) {
					dist[v.first] = dist[u] + 1;
					q.push(v.first);
				}
			}
		}
		int counter = 0;
		for (int i = 0; i < E; i++) {
			if (dist[i] != INF) {
				best[dist[i]]++;
				counter++;
			}
		}
		if (counter == 1) {
			printf("0\n");
		}
		else {
			int bestVal = 0, idx = 0;
			for (int i = 1; i < E; i++) {
				if (best[i] > bestVal) {
					bestVal = best[i];
					idx = i;
				}
			}
			printf("%d %d\n", bestVal, idx);
		}

	}
}