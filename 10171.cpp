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


int N, w, adjMatY[30][30], adjMatM[30][30];
char ym, ub, X, Y;

int main() {
	while (1) {
		scanf("%d\n", &N); if (N == 0)break;
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
				adjMatY[i][j] = adjMatM[i][j] = INF;
		map<char, int> mcharint; map<int, char> mintchar;
		int idx = 0;
		while (N--) {
			scanf("%c %c %c %c %d\n", &ym, &ub, &X, &Y, &w);
			if (mcharint.find(X) == mcharint.end()) {
				mintchar[idx] = X;
				mcharint[X] = idx++;
			}
			if (mcharint.find(Y) == mcharint.end()) {
				mintchar[idx] = Y;
				mcharint[Y] = idx++;
			}
			int s1 = mcharint[X], s2 = mcharint[Y];
			if (ym == 'Y') {
				adjMatY[s1][s2] = w;
				if (ub == 'B') adjMatY[s2][s1] = w;
			}
			else if (ym == 'M') {
				adjMatM[s1][s2] = w;
				if (ub == 'B') adjMatM[s2][s1] = w;
			}
		}
		int sz = mcharint.size();
		scanf("%c %c\n", &X, &Y); 
		if (mcharint.find(X) == mcharint.end()) {
			mintchar[idx] = X;
			mcharint[X] = idx++;
		}
		if (mcharint.find(Y) == mcharint.end()) {
			mintchar[idx] = Y;
			mcharint[Y] = idx++;
		}
		int p1 = mcharint[X], p2 = mcharint[Y];
		for (int k = 0; k < sz; k++)
			for (int i = 0; i < sz; i++)
				for (int j = 0; j < sz; j++) {
					adjMatM[i][j] = min(adjMatM[i][j], adjMatM[i][k] + adjMatM[k][j]);
					adjMatY[i][j] = min(adjMatY[i][j], adjMatY[i][k] + adjMatY[k][j]);
				}
		//for (int i = 0; i < sz; i++)printArray(adjMatY[i], sz);
		//printf("\n");
		//for (int i = 0; i < sz; i++)printArray(adjMatM[i], sz);
		adjMatY[p1][p1] = adjMatM[p2][p2] = 0;
		int energy = INF;
		vector<int> loc;
		for (int i = 0; i < sz; i++) {
			int currE = adjMatY[p1][i] + adjMatM[p2][i];
			if (currE < energy) {
				loc.clear();
				energy = currE;
				loc.push_back(i);
			}
			else if (currE == energy) {
				loc.push_back(i);
			}
		}
		vector<char> locChar;
		for (int currInt : loc) {
			char temp = mintchar[currInt];
			locChar.push_back(temp);
		}
		sort(locChar.begin(), locChar.end());
		if (energy >= INF)printf("You will never meet.\n");
		else {
			printf("%d", energy); 
			for (char temp : locChar)printf(" %c", temp); 
			printf("\n");
		}

	}
}


