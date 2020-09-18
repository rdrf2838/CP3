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

char str[20];
int n;
long long ways[20][20];

int main() {
	while (fgets(str, 20, stdin) != NULL) {

		n = strlen(str) - 1;
		memset(ways, 0, sizeof(ways));

		if (str[0] == '?')
			for (int i = 0; i < n; i++) {
				ways[0][i] = 1;
			}
		else {
			int r = str[0] - '1';
			if ((int)str[0] > 60) r -= 7;
			for (int i = 0; i < n; i++) {
				ways[0][i] = 0;
			}
			ways[0][r] = 1;
		}

		for (int r = 1; r < n; r++) {
			if (str[r] == '?') {
				for (int c = 0; c < n; c++) {
					for (int cp = 0; cp < n; cp++) {
						if (abs(cp - c) > 1) {
							ways[r][c] += ways[r - 1][cp];
						}
					}
				}
			}
			else {
				for (int c = 0; c < n; c++) {
					ways[r][c] = 0;
				}
				int c = str[r] - '1';
				if ((int)str[r] > 60) c -= 7;
				for (int cp = 0; cp < n; cp++) {
					if (abs(cp - c) > 1) {
						ways[r][c] += ways[r - 1][cp];
					}
				}
			}
		}
		long long ctr = 0;
		for (int i = 0; i < n; i++) ctr += ways[n - 1][i];
		printf("%lld\n", ctr);
		//for (int i = 0; i < n; i++)printArray(ways[i], n);
	}
}


