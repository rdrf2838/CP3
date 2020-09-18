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


int NC, NE, NM, adjMat[400][400];
char str1[10], str2[10];

int main() {
	int caseNum = 0;
	while (1) {
		caseNum++;
		scanf("%d\n", &NC); if (NC == 0)break;
		memset(adjMat, 0, sizeof(adjMat));
		map<string, int> mapper; int idx = 0;
		map<int, string> revMapper;
		while (NC--) {
			scanf("%d ", &NE);
			for (int i = 0; i < NE; i++) {
				scanf("%s", &str2);
				if (mapper.find(str2) == mapper.end()) {
					revMapper[idx] = str2;
					mapper[str2] = idx++;
				}
				if (i != 0) {
					int i1 = mapper[str1], i2 = mapper[str2];
					adjMat[i1][i2] = 1;
				}
				strcpy(str1, str2);
			}
		}
		scanf("%d", &NM);
		while (NM--) {
			scanf("%s %s", &str1, &str2);
			adjMat[mapper[str1]][mapper[str2]] = 1;
		}
		int sz = mapper.size();
		/*for (int i = 0; i < mapper.size(); i++)
			printArray(adjMat[i], mapper.size());
		printf("\n");*/
		for (int k = 0; k < sz; k++)
			for (int i = 0; i < sz; i++)
				for (int j = 0; j < sz; j++)
					adjMat[i][j] |= (adjMat[i][k] & adjMat[k][j]);
		for (int i = 0; i < sz; i++) {
			adjMat[i][i] = 1;
			for (int j = 0; j < sz; j++)
				adjMat[i][j] = (adjMat[i][j] | adjMat[j][i]);
		}
		//for (int i = 0; i < mapper.size(); i++)
		//	printArray(adjMat[i], mapper.size());
		vii pairL;
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++) {
				if (j >= i)continue;
				if (adjMat[i][j] == 0) pairL.push_back(ii(i, j));
			}
		int count = pairL.size();
		if (count == 0)printf("Case %d, no concurrent events.\n", caseNum);
		else {
			printf("Case %d, %d concurrent events:\n", caseNum, count);
			count = min(count, 2);
			for (int i = 0; i < count; i++) {
				printf("(%s,%s) ", revMapper[pairL[i].first].c_str(), revMapper[pairL[i].second].c_str());
			} printf("\n");
		}

	}
}


