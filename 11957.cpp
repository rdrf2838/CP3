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

int T, N, ways[110][110], divisor = 1000007;
char board[110][110];

int isValid(int r, int c) {
	return (0 <= r && r < N && 0 <= c && c < N) && (board[r][c] != 'B');
}

int main() {
	scanf("%d\n", &T);
	for (int caseNum = 1; caseNum <= T; caseNum++) {
		scanf("%d\n", &N);
		for (int i = N - 1; i >= 0; i--) {
			fgets(board[i], 110, stdin);
		}
		int rb, cb;
		memset(ways, 0, sizeof(ways));
		for (int r = 0; r < N; r++)
			for (int c = 0; c < N; c++)
				if (board[r][c] == 'W') {
					ways[r][c] = 1;
					rb = r; cb = c;
					r = c = N;
				}
		if (isValid(rb + 1, cb + 1))ways[rb + 1][cb + 1] = 1;
		if (isValid(rb + 1, cb - 1))ways[rb + 1][cb - 1] = 1;

		for (int r = rb + 2; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (isValid(r, c)) {
					int rp = r - 1, cp1 = c - 1, cp2 = c + 1;
					if (isValid(rp, cp1))ways[r][c] = (ways[r][c] + ways[rp][cp1]) % divisor;
					if (isValid(rp, cp2))ways[r][c] = (ways[r][c] + ways[rp][cp2]) % divisor;

					int rpp = r - 2, cpp1 = c - 2, cpp2 = c + 2;
					if (isValid(rpp, cpp1) && (board[rp][cp1] == 'B'))ways[r][c] = (ways[r][c] + ways[rpp][cpp1]) % divisor;
					if (isValid(rpp, cpp2) && (board[rp][cp2] == 'B'))ways[r][c] = (ways[r][c] + ways[rpp][cpp2]) % divisor;
					//printf("Checking: r: %d c: %d rpp: %d cpp1: %d cpp2: %d isValid1: %d isValid 2: %d board1: %d board2: %d\n", r, c, rpp, cpp1, cpp2, isValid(rpp, cpp1), isValid(rpp, cpp2), (board[rp][cp1] == 'B'), (board[rp][cp2] == 'B'));
				}
			}
		}
		int ctr = 0;
		for (int i = 0; i < N; i++) ctr = (ctr + ways[N - 1][i]) % divisor;
		printf("Case %d: %d\n", caseNum, ctr);
		//for (int i = 0; i < N; i++)printArray(board[i], N);
		//for (int i = 0; i < N; i++)printArray(ways[i], N);



	}
}


