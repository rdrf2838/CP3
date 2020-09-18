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
const int VISITED = 1, UNVISITED = -1, INF = 1000000000;
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

int P, R, adjMat[60][60];
char str1[20], str2[20];

int main() {
	int caseNum = 0;
	while (1) {
		scanf("%d %d", &P, &R); if (P == 0 && R == 0)break;
		for (int i = 0; i < P; i++)
			for (int j = 0; j < P; j++) {
				if (i == j)adjMat[i][j] = 0;
				else adjMat[i][j] = INF;
			}

		map<string, int> mapper;
		map<int, string> revMapper;
		int idx = 0;
		for (int i = 0; i < R; i++) {
			scanf("%s %s", &str1, &str2);
			if (mapper.find(str1) == mapper.end()) {
				revMapper[idx] = str1;
				mapper[str1] = idx++;
			}
			if (mapper.find(str2) == mapper.end()) {
				revMapper[idx] = str2;
				mapper[str2] = idx++;
			}
			int i1 = mapper[str1], i2 = mapper[str2];
			adjMat[i1][i2] = adjMat[i2][i1] = 1;
		}
		//for (int i = 0; i < P; i++)printArray(adjMat[i], P);
		for (int k = 0; k < P; k++)
			for (int i = 0; i < P; i++)
				for (int j = 0; j < P; j++)
					adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
		int best = 0;
		for(int i=0; i<P; i++)
			for (int j = 0; j < P; j++) 
				best = max(best, adjMat[i][j]);
		caseNum++; 
		if (best >= INF)printf("Network %d: DISCONNECTED\n", caseNum);
		else printf("Network %d: %d\n", caseNum, best);
		printf("\n");
	}
}


