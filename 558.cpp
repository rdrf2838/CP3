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

vector<vii> adjList;

int c, n, m, x, y, t;

int main() {
	cin >> c;
	while (c--) {
		adjList.clear();
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			vii temp; adjList.push_back(temp);
		}
		while (m--) {
			cin >> x >> y >> t;
			adjList[x].push_back(ii(y, t));
		}
		vi dist(n, INF); dist[0] = 0;
		for (int i = 0; i < n - 1; i++)
			for (int u = 0; u < n; u++)
				for (ii v : adjList[u])
					dist[v.first] = min(dist[v.first], dist[u] + v.second);
		bool hasNegCycle = false;
		for (int u = 0; u < n; u++)
			for (ii v : adjList[u])
				if (dist[v.first] > dist[u] + v.second)
					hasNegCycle = true;
		hasNegCycle ? cout << "possible\n" : cout << "not possible\n";
	}
}


