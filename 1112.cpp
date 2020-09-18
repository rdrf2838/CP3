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

vector<vii> AdjList;

int cases, N, E, T, M, u, v, w;

int main() {
	scanf("%d", &cases);
	int caseNo = 0;
	while (cases--) {
		caseNo++; if (caseNo != 1)printf("\n");
		scanf("%d %d %d %d", &N, &E, &T, &M);
		AdjList.clear();
		for (int i = 0; i < N; i++) {
			vii temp; AdjList.push_back(temp);
		}
		while (M--) {
			scanf("%d %d %d", &u, &v, &w);
			//reminder: reversed edge directions to run from source
			AdjList[v - 1].push_back(ii(u - 1, w));
		}
		priority_queue<ii> pq; pq.push(ii(0, E - 1));
		vector<int> dist(N, INF); dist[E - 1] = 0;
		while (!pq.empty()) {
			ii front = pq.top(); pq.pop();
			int d = -front.first, u = front.second;
			if (d > dist[u])continue;
			for (ii v : AdjList[u]) {
				if (dist[u] + v.second < dist[v.first]) {
					dist[v.first] = dist[u] + v.second;
					pq.push(ii(-dist[v.first], v.first));
				}
			}
		}
		int counter = 0;
		for (int time : dist) {
			if (time <= T)counter++;
		}
		printf("%d\n", counter);
	}
}