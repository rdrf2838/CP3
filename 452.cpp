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

vector<vii> AdjList;
vector<vi> AdjListRev;
vi dfs_num;
int T, v, V;
char str[100], str2[50], temp;

int dfs(int u) {
	if (u == 26) return 0;
	dfs_num[u] = VISITED;
	int maxDist = 0;
	for (ii v : AdjList[u]) {
		maxDist = max(maxDist, dfs(v.first) + v.second);
	}
	return maxDist;
}


int main() {
	scanf("%d\n\n", &T);
	for (int t = 0; t < T; t++) {
		map<char, int> mapper;
		map<int, char> revMapper;
		V = 0;
		AdjList.clear(); 
		AdjListRev.clear();
		for (int i = 0; i < 27; i++) {
			vii temp; AdjList.push_back(temp);
			vi temp2; AdjListRev.push_back(temp2);
		}
		while (1) {
			str[0] = str2[0] = '\0';
			fgets(str, 100, stdin);
			if (str[0] == '\n'||str[0] == '\0')break;
			sscanf(str, "%c %d %s", &temp, &v, &str2);
			if (mapper.find(temp) == mapper.end()) {
				revMapper[V] = temp;
				mapper[temp] = V++;
			}
			if (str2[0] == NULL) {
				AdjList[mapper[temp]].push_back(ii(26, v));
				AdjListRev[26].push_back(mapper[temp]);
			}
			else {
				for (int i = 0; i < strlen(str2); i++) {
					char cur = str2[i];
					if (mapper.find(cur) == mapper.end()) {
						revMapper[V] = cur;
						mapper[cur] = V++;
					}
					AdjList[mapper[temp]].push_back(ii(mapper[cur], v));
					AdjListRev[mapper[cur]].push_back(mapper[temp]);
				}
			}
		}
		vi sources;
		for (int i = 0; i < V; i++) {
			if (AdjListRev[i].size() == 0) {
				sources.push_back(i);

			}
		}
		int maxNum = 0;
		for (int s : sources) {
			dfs_num.assign(27, UNVISITED);
			maxNum = max(maxNum, dfs(s));
		}
		//printAdjList(AdjList);
		if (t != 0)printf("\n");
		printf("%d\n", maxNum);
	}
}


