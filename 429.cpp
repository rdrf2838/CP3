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

int N;

vector<vii> AdjList;
int finder(char dict[220][20],char str1[20]) {
	for (int i = 0; i < AdjList.size(); i++) {
		int len = strlen(str1); int same = 1;
		for (int j = 0; j < len; j++) {
			if (dict[i][j] != str1[j]) {
				same = 0; break;
			}
		}
		if (same)return i;
	}
}

int diffBy1(char str1[20], char str2[20]) {
	int l = strlen(str1); int ctr = 0;
	if (l == strlen(str2)) {
		for (int i = 0; i < l; i++) {
			if (str1[i] != str2[i])ctr++;
		}
	}
	if (ctr == 1)return 1;
	else return 0;
}

int main() {
	scanf("%d\n", &N); int ctr = 0;
	while (N--) {
		ctr++; if (ctr != 1)printf("\n");
		char dict[210][20], temp1[20], temp2[20], temp3[40];
		int i = 0; AdjList.clear();
		while (1) {
			fgets(dict[i], 20, stdin); if (dict[i][0] == '*')break;
			vii temp; AdjList.push_back(temp);
			for (int j = 0; j < i; j++) {
				if (diffBy1(dict[i], dict[j])) {
					AdjList[j].push_back(ii(i, 0));
					AdjList[i].push_back(ii(j, 0));
				}
			}
			i++;
		}
		while (fgets(temp3, 40, stdin)!=NULL) {
			 if (temp3[0] == '\n')break;
			sscanf(temp3, "%s %s\n", &temp1, &temp2);
			int source = finder(dict, temp1);
			int end = finder(dict, temp2);

			vi dist(AdjList.size(), INF); dist[source] = 0;
			queue<int> q; q.push(source);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				if (u == end)break;
				for (ii v : AdjList[u]) {
					if (dist[v.first] == INF) {
						dist[v.first] = dist[u] + 1;
						q.push(v.first);
					}
				}
			}
			printf("%s %s %d\n", temp1, temp2, dist[end]);
		}
	}
}