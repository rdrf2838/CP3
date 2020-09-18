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
#include <bitset>

using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
const int VISITED = 1, UNVISITED = -1, INF = 1000000000, MAX_V = 300;
int xl[] = { 1, -1, 0, 0 };
int yl[] = { 0,0,-1,1 };
class UnionFind {
private:
	vi p, rank, setSize;
	int numSets;
public:
	UnionFind(int N) {
		setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
		p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i;
	}
	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) {
			numSets--;
			int x = findSet(i), y = findSet(j);
			// rank is used to keep the tree short
			if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
			else {
				p[x] = y; setSize[y] += setSize[x];
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	}
	int numDisjointSets() { return numSets; }
	int sizeOfSet(int i) { return setSize[findSet(i)]; }
};
void printArray(int a[], int n) {
	for (int* i = a; i < a + n; i++) {
		if (i != a) {
			printf(" ");
		}
		printf("%d", *i);
	}
	printf("\n");
}void printArray(double a[], int n) {
	for (double* i = a; i < a + n; i++) {
		if (i != a) {
			printf(" ");
		}
		printf("%lf", *i);
	}
	printf("\n");
}
void printArray(char a[], int n) {
	for (char* i = a; i < a + n; i++) {
		if (i != a) {
			printf(" ");
		}
		printf("%c", *i);
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
void printAdjList(vector<vi> AdjList) {
	int i = 0;
	for (vi currpairlist : AdjList) {
		printf("%d: ", i);
		for (int currpair : currpairlist) {
			printf("(%d) ", currpair);
		}
		printf("\n");
		i++;
	}
}

int m, n, arr[120][12], cost[120][12], p[120][12];

void printAns(int r, int c) {
	printf("%d ", r + 1);
	if (c != 0)
		printAns(p[c][r], c - 1);
}

int mod(int a, int b) {
	if (a >= b)return mod(a - b, b);
	if (a < 0)return mod(a + b, b);
	return a;
}

int main() {
	while (scanf("%d %d\n", &m, &n) == 2) {
		for (int i = 0; i < m; i++)
			for (int j = n - 1; j >= 0; j--)
			//for (int j = 0; j < n; j++)
				scanf("%d", &arr[j][i]);

		for (int i = 0; i < m; i++)
			cost[0][i] = arr[0][i];

		for (int cc = 1; cc < n; cc++) {
			int pc = cc - 1;
			for (int cr = 0; cr < m; cr++) {
				int pr1 = mod(cr - 1, m), pr2 = cr, pr3 = mod(cr + 1, m);
				priority_queue<int> pq; pq.push(-pr1); pq.push(-pr2); pq.push(-pr3);
				int minVal = INF, minIdx = -1;
				while (!pq.empty()) {
					int pr = -pq.top(); pq.pop();
					if (cost[pc][pr] < minVal) {
						minVal = cost[pc][pr];
						minIdx = pr;
					}
				}
				cost[cc][cr] = arr[cc][cr] + minVal;
				p[cc][cr] = minIdx;
			}
		}
		int idx = -1, minVal = INF;
		for (int i = 0; i < m; i++) {
			if (minVal > cost[n - 1][i]) {
				minVal = cost[n - 1][i]; idx = i;
			}
		}
		printAns(idx, n - 1); printf("\n");
		printf("%d\n", minVal);
		//printf("MinIdx: %d\n", idx);
		//printf("\n");
		//for (int i = 0; i < n; i++)printArray(arr[i], m);
		//printf("\n");
		//for (int i = 0; i < n; i++)printArray(cost[i], m);
		//printf("\n");
		//for (int i = 0; i < n; i++)printArray(p[i], m);
		//printf("\n");
		//printAns(idx, n - 1);
		//printf("\n\n");
	}
}


