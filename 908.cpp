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

int N, K, M, u, v, w, prevSum;

int main() {
	int ctr = 0;
	while (scanf("%d", &N) == 1) {
		ctr++; if (ctr != 1)printf("\n");
		prevSum = 0;
		for (int i = 0; i < N - 1; i++) {
			scanf("%d %d %d", &u, &v, &w); prevSum += w;
		}
		scanf("%d", &K);
		vector< pair<int, ii> > EdgeList;
		for (int i = 0; i < K; i++) {
			scanf("%d %d %d", &u, &v, &w);
			EdgeList.push_back(make_pair(w, ii(u-1, v-1)));
		}
		scanf("%d", &M);
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &u, &v, &w);
			EdgeList.push_back(make_pair(w, ii(u-1, v-1)));
		}
		sort(EdgeList.begin(), EdgeList.end());
		int mst_cost = 0;
		UnionFind UF(N); // all V are disjoint sets initially
		for (int i = 0; i < K + M; i++) { // for each edge, O(E)
			pair<int, ii> front = EdgeList[i];
			if (!UF.isSameSet(front.second.first, front.second.second)) { // check
				mst_cost += front.first; // add the weight of e to MST
				UF.unionSet(front.second.first, front.second.second); // link them
			}
		}
		printf("%d\n%d\n", prevSum, mst_cost);
	}
}