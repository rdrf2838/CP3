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

int p, city[2500][2500], a, s;
int X[] = { 1,-1,0,0 };
int Y[] = { 0,0,1,-1 };
vii startp, endp;

int main() {
	while (1) {
		int width = 10; startp.clear(); endp.clear();
		memset(city, UNVISITED, sizeof(city));
		scanf("%d", &p); if (p == 0)break;
		while (p--) { scanf("%d %d", &a, &s); startp.push_back(ii(a, s)); }
		scanf("%d", &p);
		while (p--) { scanf("%d %d", &a, &s); endp.push_back(ii(a, s)); }

		queue<ii> q;
		for (ii u : startp) {
			city[u.first][u.second] = 0;
			q.push(u);
		}
		for (ii u : endp)city[u.first][u.second] = -2;
		int bestDist = -1;
		while (!q.empty()) {
			ii u = q.front(); q.pop();
			for (int i = 0; i < 4; i++) {
				int nextX = u.first + X[i];
				int nextY = u.second + Y[i];
				if (nextX < 0 || nextY < 0)continue;
				if (city[nextX][nextY] <= UNVISITED) {
					if (city[nextX][nextY] == -2) {
						bestDist = city[u.first][u.second] + 1;
						break;
					}
					city[nextX][nextY] = city[u.first][u.second] + 1;
					q.push(ii(nextX, nextY));
				}
			}
			if (bestDist != -1)break;
		}
		/*for (int i = 0; i < width; i++) {
			printArray(city[i], width);
		}*/
		printf("%d\n", bestDist);
	}
}