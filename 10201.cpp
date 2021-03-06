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

vi stations, prices;
int D, T, memo[210][110];

int dfs(int gas, int u) {
	if ((gas < 0))return INF;

	int& local = memo[gas][u];
	if (local != -1)return local;

	if (u == stations.size() - 1) {
		if (gas >= 100)return 0;
		else return INF;
	}

	int minCost = INF;

	if (u == 0) {
		for (int v = u + 1; v < stations.size(); v++) {
			int d2 = stations[v] - stations[u];
			minCost = min(minCost, dfs(gas - d2, v));
		}
	}

	else {
		for (int v = u + 1; v < stations.size(); v++) {
			int d2 = stations[v] - stations[u];
			for (int gas2 = gas; gas2 <= 200; gas2++) {
				int price = (gas2 - gas) * prices[u];
				minCost = min(minCost, price + dfs(gas2 - d2, v));
			}
		}
	}

	return local = minCost;
}

int main() {
	int ctr = 0;
	scanf("%d\n", &T);
	while (T--) {
		ctr++;
		stations.clear(); prices.clear();
		memset(memo, -1, sizeof(memo));

		scanf("%d\n", &D);

		stations.push_back(0);
		prices.push_back(0);

		while (1) {
			char str[20]; str[0] = '\0';
			fgets(str, 20, stdin);
			if ((str[0] == '\n') || (str[0] == '\0'))break;

			int station, price;

			sscanf(str, "%d %d", &station, &price);

			stations.push_back(station);
			prices.push_back(price);

		}

		stations.push_back(D);
		prices.push_back(INF);

		int ans = dfs(100, 0);
		if (ctr != 1)printf("\n");
		if (ans >= INF)printf("Impossible\n");
		else printf("%d\n", dfs(100, 0));
	}
}


