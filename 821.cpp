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
class UnionFind {                                              // OOP style
private:
	vi p, rank, setSize;                       // remember: vi is vector<int>
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

int a, b, adjMat[110][110];

int main() {
	int caseNo = 0;
	while (1) {
		caseNo++;
		scanf("%d %d", &a, &b); if (a == 0 && b == 0)break;
		for (int i = 0; i < 110; i++)
			for (int j = 0; j < 110; j++)
				adjMat[i][j] = INF;
		adjMat[a][b] = 1; int maxPg = 0;
		while (1) {
			scanf("%d %d", &a, &b); if (a == 0 && b == 0)break;
			maxPg = max(maxPg, a); maxPg = max(maxPg, b);
			adjMat[a][b] = 1;
		}
		maxPg++;
		for (int k = 1; k < maxPg; k++)
			for (int i = 1; i < maxPg; i++)
				for (int j = 1; j < maxPg; j++)
					adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
		double sum = 0; int num = 0;
		for (int i = 1; i < maxPg; i++)
			for (int j = 1; j < maxPg; j++)
				if (i != j && adjMat[i][j] != INF) {
					sum += adjMat[i][j];
					num++;
				}
		printf("Case %d: average length between pages = %0.3lf clicks\n", caseNo, sum / num);
	}
}


