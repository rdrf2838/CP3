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

vector<vii> adjList, adjListRev;

int T, N, M, s, t, p, u, v, c;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d %d %d", &N, &M, &s, &t, &p);
		s--; t--;
		adjList.clear(); adjListRev.clear();
		for (int i = 0; i < N; i++) {
			vii temp, temp2;
			adjList.push_back(temp);
			adjListRev.push_back(temp2);
		}
		vector<pair<int, ii>> edgeList;
		while (M--) {
			scanf("%d %d %d", &u, &v, &c);
			adjList[u - 1].push_back(ii(v - 1, c));
			adjListRev[v - 1].push_back(ii(u - 1, c));
			edgeList.push_back(make_pair(c, ii(u - 1, v - 1)));
		}
		vi dist(N, INF), distEnd(N, INF); dist[s] = 0; distEnd[t] = 0;
		priority_queue<ii> pq; pq.push(ii(0, s));
		while (!pq.empty()) {
			ii front = pq.top(); pq.pop();
			int d = front.first, u = front.second;
			if (d > dist[u])continue;
			for (ii v : adjList[u]) {
				if (dist[u] + v.second < dist[v.first]) {
					dist[v.first] = dist[u] + v.second;
					pq.push(ii(-dist[v.first], v.first));
				}
			}
		}
		pq.push(ii(0, t));
		while (!pq.empty()) {
			ii front = pq.top(); pq.pop();
			int d = front.first, u = front.second;
			if (d > distEnd[u])continue;
			for (ii v : adjListRev[u]) {
				if (distEnd[u] + v.second < distEnd[v.first]) {
					distEnd[v.first] = distEnd[u] + v.second;
					pq.push(ii(-distEnd[v.first], v.first));
				}
			}
		}
		int bestMid = -1;
		for (pair<int, ii> currEdge : edgeList) {
			int u = currEdge.second.first, v = currEdge.second.second, mid = currEdge.first;
			if (mid + dist[u] + distEnd[v] <= p && mid > bestMid)bestMid = mid;
		}
		printf("%d\n", bestMid);
		//printVector(dist);
		//printVector(distEnd);
	}
}


