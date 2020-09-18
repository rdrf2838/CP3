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

vector<vector<vector<int>>> cost;
int n, k, ct, val, memo[12][1100];

int dfs(int day, int loc) {
	if (day < 0)return INF;
	//printf("Visiting: day: %d loc: %d\n", day, loc);
	int& local = memo[loc][day];
	if (local != -1)return local;

	if (day == 0) {
		if (loc == n - 1)return local = 0;
		else return local = INF;
	}

	int minCost = INF;
	for (int nxtLoc = 0; nxtLoc < n; nxtLoc++) {
		if (nxtLoc != loc) {
			//printf("    nxtloc: %d\n", nxtLoc);
			vector<int> prices = cost[loc][nxtLoc];
			int currDay = k - day;
			int currPrice = prices[currDay % prices.size()];
			minCost = min(minCost, currPrice + dfs(day - 1, nxtLoc));

		}
	}

	return local = minCost;

}

int main() {
	int caseNum = 1;
	while (1) {
		scanf("%d %d\n", &n, &k); if ((n == 0) && (k == 0))break;
		cost.clear();
		for (int i = 0; i < n; i++) {
			vector<vector<int>> temp;
			for (int j = 0; j < n; j++) {
				vector<int> temp2;
				temp.push_back(temp2);
			}
			cost.push_back(temp);
		}
		memset(memo, -1, sizeof(memo));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j) {
					scanf("%d", &ct);
					for (int k = 0; k < ct; k++) {
						scanf("%d", &val);
						if (val == 0)val = INF;
						cost[i][j].push_back(val);
					}
				}
			}
		}
		int ans = dfs(k, 0);
		printf("Scenario #%d\n", caseNum); caseNum++;
		ans >= INF ? 
			printf("No flight possible.\n\n") : 
			printf("The best flight costs %d.\n\n", ans);
	}
}


