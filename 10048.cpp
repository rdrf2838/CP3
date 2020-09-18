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
const int VISITED = 1, UNVISITED = -1;
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
vector<vii> AdjList;
vi dfs_num, dfs_dist;
int C, S, Q, c1, c2, d, isFound;
void dfs(int u) {
	dfs_num[u] = VISITED;
	for (ii v : AdjList[u]) {
		if (dfs_num[v.first] == UNVISITED) {
			dfs_dist[v.first] = max(dfs_dist[u], v.second);
			dfs(v.first);
		}
	}
}
int main() {
	int ctr = 0;
	while (1) {
		scanf("%d %d %d", &C, &S, &Q); if (C == 0 && S == 0 && Q == 0)break;
		ctr++; if (ctr != 1)printf("\n");
		AdjList.clear();
		for (int i = 0; i < C; i++) {
			vii temp; AdjList.push_back(temp);
		}
		vector< pair<int, ii> > EdgeList;
		for (int i = 0; i < S; i++) {
			scanf("%d %d %d", &c1, &c2, &d);
			EdgeList.push_back(make_pair(d, ii(c1 - 1, c2 - 1)));
		} // (w, u, v)
		sort(EdgeList.begin(), EdgeList.end());
		UnionFind UF(C); // all V are disjoint sets initially
		for (int i = 0; i < S; i++) { // for each edge, O(E)
			pair<int, ii> front = EdgeList[i];
			if (!UF.isSameSet(front.second.first, front.second.second)) { // check
				UF.unionSet(front.second.first, front.second.second); // link them
				AdjList[front.second.first].push_back(ii(front.second.second, front.first));
				AdjList[front.second.second].push_back(ii(front.second.first, front.first));
			}
		}
		//printAdjList(AdjList);
		printf("Case #%d\n",ctr);
		for (int i = 0; i < Q; i++){
			scanf("%d %d", &c1, &c2); c1--; c2--;
			dfs_num.assign(C, UNVISITED); dfs_dist.assign(C, -1);
			dfs(c1); 
			//printVector(dfs_dist);
			int ans = dfs_dist[c2];
			ans==-1?printf("no path\n"): printf("%d\n", ans);
		}
	}
}