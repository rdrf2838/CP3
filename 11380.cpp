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
const int VISITED = 1, UNVISITED = -1, INF = 1000000000, MAX_V = 2000;
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
}
void printArray(double a[], int n) {
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

int xl[] = { 1,-1,0,0 };
int yl[] = { 0,0,1,-1 };
int X, Y, P, res[2000][2000];
char arr[35][35];
vector<vi> AdjList;
int mf, f, s, t;
vi p;
void augment(int v, int minEdge) {
	if (v == s) { f = minEdge; return; }
	else if (p[v] != -1) {
		augment(p[v], min(minEdge, res[p[v]][v]));
		res[p[v]][v] -= f; res[v][p[v]] += f;
	}
}
int isWithin(int x, int y) {
	return (0 <= x && x < X && 0 <= y && y < Y);
}
int main() {
	while (scanf("%d %d %d\n", &X, &Y, &P) == 3) {
		for (int i = 0; i < X; i++)
			fgets(arr[i], 35, stdin);
		memset(res, 0, sizeof(res)); AdjList.clear();

		for (int i = 0; i < 2 * X * Y + 2; i++) {
			vi temp; AdjList.push_back(temp);
		}
		int s = 0, t = 2 * X * Y + 1;
		for (int k = 0; k < X * Y; k++) {
			int i = k / Y, j = k % Y, idx = k + 1;
			int i2 = i + X * Y, j2 = j + X * Y, idx2 = k + X * Y + 1;
			char curr = arr[i][j];
			if (curr == '*') {
				AdjList[s].push_back(idx);
				AdjList[idx].push_back(s);
				res[s][idx] = 1;
			}
			else if (curr == '#') {
				AdjList[idx2].push_back(t);
				AdjList[t].push_back(idx2);
				res[idx2][t] = P;
			}
			if (curr != '~') {
				AdjList[idx2].push_back(idx);
				AdjList[idx].push_back(idx2);
				if (curr == '#' || curr == '@')
					res[idx][idx2] = 1000;
				else res[idx][idx2] = 1;

				for (int m = 0; m < 4; m++) {
					int iside = i + xl[m], jside = j + yl[m], idxside = iside * Y + jside + 1;
					if (isWithin(iside, jside) && arr[iside][jside] != '~') {
						AdjList[idx2].push_back(idxside);
						AdjList[idxside].push_back(idx2);
						res[idx2][idxside] = 1000;
					}
				}
			}
		}
		//printAdjList(AdjList);
		//for (int i = 0; i < 2*X * Y + 2; i++)printArray(res[i],2* X * Y + 2);
		mf = 0;
		while (1) {
			f = 0;
			bitset<MAX_V> vis; vis[s] = true;
			queue<int> q; q.push(s);
			p.assign(MAX_V, -1);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				if (u == t) break;
				for (int v : AdjList[u]) {
					if (res[u][v] > 0 && !vis[v])
						vis[v] = true, q.push(v), p[v] = u;
				}
			}
			augment(t, INF);
			if (f == 0) break;
			mf += f;
		}
		printf("%d\n", mf);
	}
}


