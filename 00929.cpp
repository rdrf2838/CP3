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

int RL[] = { 0,0,1,-1 };
int CL[] = { 1,-1,0,0 };
int T, N, M, grid[1100][1100], dist[1100][1100];

bool isValid(ii u) {
	int r = u.first, c = u.second;
	return (0 <= r && r < N && 0 <= c && c < M);
}


int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				scanf("%d", &grid[r][c]);
				dist[r][c] = INF;
			}
		}
		dist[0][0] = grid[0][0];
		priority_queue<pair<int, ii>> pq; pq.push(make_pair(-dist[0][0],ii(0,0)));
		while (!pq.empty()) {
			pair<int, ii> front = pq.top(); pq.pop(); 
			int d = - front.first; ii u = front.second;
			if (d > dist[u.first][u.second])continue;
			for (int i = 0; i < 4; i++) {
				ii v = ii(u.first + RL[i], u.second + CL[i]);
				if (isValid(v)) {
					if (dist[u.first][u.second] + grid[v.first][v.second] < dist[v.first][v.second]) {
						dist[v.first][v.second] = dist[u.first][u.second] + grid[v.first][v.second];
						pq.push(make_pair(-dist[v.first][v.second], ii(v.first, v.second)));
					}
				}
			}
		}
		printf("%d\n", dist[N - 1][M - 1]);
	}
}