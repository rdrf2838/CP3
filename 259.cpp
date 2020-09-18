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
const int VISITED = 1, UNVISITED = -1, INF = 1000000000, MAX_V = 40;
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
char A, B;
char input[100], input2[20];
vector<vi> AdjList;
int res[MAX_V][MAX_V], mf, f, s = 0, t = 37, V = 38; // global variables
vi p; // p stores the BFS spanning tree from s
void augment(int v, int minEdge) { // traverse BFS spanning tree from s->t
	if (v == s) { f = minEdge; return; } // record minEdge in a global var f
	else if (p[v] != -1) {
		augment(p[v], min(minEdge, res[p[v]][v]));
		res[p[v]][v] -= f; res[v][p[v]] += f;
	}
}

int main() {
	char app;
	int num, tot, isRun = 1;

	while (isRun) {
		memset(res, 0, sizeof res); tot = 0;
		while(1) {
			if (fgets(input, 100, stdin) == 0) {
				isRun = 0;
				break;
			}
			//printf("Current Input: %s\n", input);
			if (strcmp(input, "\n") == 0)break;
			sscanf(input, "%c%c %s", &A, &B, input2);
			res[0][A - 'A' + 1] = B - '0'; tot += B - '0';
			for (int i = 0;; i++) {
				if (input2[i] == ';')break;
				res[A - 'A' + 1][27 + input2[i] - '0'] = INF;
			}
		}
		for (int i = 27; i < 37; i++) res[i][37] = 1;
		mf = 0;
		//for (int i = 0; i < MAX_V; i++)printArray(res[i], MAX_V);
		while (1) {
			//printf("Running: visiting\n ");
			f = 0; bitset<MAX_V> vis; vis[s] = true;
			queue<int> q; q.push(s); p.assign(MAX_V, -1);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				if (u == t)break;
				for (int v = 0; v < V; v++)
					if (res[u][v] > 0 && !vis[v])
						vis[v] = true, q.push(v), p[v] = u;
			}
			augment(t, INF);
			if (f == 0)break;
			mf += f;
		}
		//printf("Maxflow: %d total: %d\n", mf, tot);
		if (mf != tot)printf("!\n");
		else {
			for (int i = 27; i < 37; i++) {
				int ans = -1;
				for (int j = 1; j < 27; j++) {
					if (res[i][j] == 1) ans = j;
				}
				if (ans == -1)printf("_");
				else printf("%c", (char)(ans + 'A' - 1));
			}printf("\n");
		}
	}
	return 0;
}


