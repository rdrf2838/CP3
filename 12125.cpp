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


int T, N, n, m; 
double D, x, y;

vector<vi> AdjList;
int res[MAX_V][MAX_V], mf, f, s, t;
vi p;
void augment(int v, int minEdge) {
	if (v == s) { f = minEdge; return; }
	else if (p[v] != -1) {
		augment(p[v], min(minEdge, res[p[v]][v]));
		//printf("Edge: %d %d Flow: %d\n", p[v], v, f);
		res[p[v]][v] -= f; res[v][p[v]] += f;
	}
}
double dist(pair<double, double> p1, pair<double, double> p2) {
	return sqrt((p2.first - p1.first)* (p2.first - p1.first) + (p2.second - p1.second)* (p2.second - p1.second));
}
int main() {
	scanf("%d", &T); 
	while (T--) {
		scanf("%d %lf", &N, &D);
		s = 2 * N;
		memset(res, 0, sizeof(res)); AdjList.clear();
		for (int i = 0; i < 2 * N + 1; i++) {
			vi temp; AdjList.push_back(temp);
		}
		vector<pair<double, double>> vdd;
		int pgct = 0;
		for (int i = 0; i < N; i++) {
			scanf("%lf %lf %d %d", &x, &y, &n, &m);
			pair<double, double> ddnxt(x, y);
			AdjList[i].push_back(N + i);
			AdjList[N + i].push_back(i);
			res[i][N + i] = m;
			AdjList[s].push_back(i);
			AdjList[i].push_back(s);
			res[s][i] = n; pgct += n;
			for (int j = 0; j < vdd.size(); j++) {
				pair<double, double> ddprev = vdd[j];
				if (dist(ddprev, ddnxt) <= D) {
					int i2 = i + N, j2 = j + N;
					AdjList[i2].push_back(j);
					AdjList[j].push_back(i2);
					res[i2][j] = INF;
					AdjList[j2].push_back(i);
					AdjList[i].push_back(j2);
					res[j2][i] = INF;
				}
			}
			vdd.push_back(ddnxt);
		}
		//printAdjList(AdjList);
		//for (int i = 0; i < s + 1; i++)printArray(res[i], s + 1);
		int temp[MAX_V][MAX_V];
		for (int i = 0; i < s + 1; i++)
			for (int j = 0; j < s + 1; j++)
				temp[i][j] = res[i][j];
		vi pgarr;
		for(t=0; t<N; t++){
			//printf("Source: %d Sink: %d\n", s, t);
			mf = 0;
			while (1){
				f = 0;
				bitset<MAX_V> vis; vis[s] = true;
				queue<int> q; q.push(s);
				p.assign(MAX_V, -1);
				while (!q.empty()) {
					int u = q.front(); q.pop();
					//printf("Visiting %d\n", u);
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
			if (mf == pgct)pgarr.push_back(t);
			//printf("Ans: %d/%d\n", mf, pgct);
			//for (int i = 0; i < s + 1; i++)printArray(res[i], s + 1);

			for (int i = 0; i < s + 1; i++)
				for (int j = 0; j < s + 1; j++)
					res[i][j] = temp[i][j];
		}
		if (pgarr.empty())printf("-1\n");
		else { 
			int ctr = 0;
			for (int pg : pgarr) {
				if (ctr != 0)printf(" ");
				printf("%d", pg);
				ctr++;
			}
			printf("\n"); 
		}
	}
}


