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

int T, N, M, A, B, C;

int main() {
	scanf("%d", &T);
	ofstream outFile; outFile.open("Test.txt");

	while (T--) {
		scanf("%d %d", &N, &M);
		vector< pair<int, ii> > EdgeList; // (weight, two vertices) of the edge
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &A, &B, &C); // read the triple: (u, v, w)
			EdgeList.push_back(make_pair(C, ii(A-1, B-1)));
		} // (w, u, v)
		sort(EdgeList.begin(), EdgeList.end());
		vector<int> EdgeCtr; EdgeCtr.assign(M, 0);
		int mst_cost = 0;
		UnionFind UF(N); // all V are disjoint sets initially
		for (int i = 0; i < M; i++) { // for each edge, O(E)
			pair<int, ii> front = EdgeList[i];
			if (!UF.isSameSet(front.second.first, front.second.second)) { // check
				EdgeCtr[i] = 1;
				mst_cost += front.first; // add the weight of e to MST
				UF.unionSet(front.second.first, front.second.second); // link them
			}
		}
		int bestMstCost2 = 3000000;
		for (int j = 0; j < M; j++) {
			if (EdgeCtr[j] == 1) {
				int mstCost2 = 0;
				UnionFind UF(N);
				for (int i = 0; i < M; i++) { // for each edge, O(E)
					if (j != i) {
						pair<int, ii> front = EdgeList[i];
						if (!UF.isSameSet(front.second.first, front.second.second)) { // check
							mstCost2 += front.first; // add the weight of e to MST
							UF.unionSet(front.second.first, front.second.second); // link them
						}
					}
				}
				if(UF.setCount()==1)bestMstCost2 = min(bestMstCost2, mstCost2);
			}
		}
		printf("%d %d\n", mst_cost, bestMstCost2);
		outFile << mst_cost << " " << bestMstCost2 << "\n";
	}
	outFile.close();
}