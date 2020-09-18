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
const int VISITED = 1, UNVISITED = -1, INF = 1000000000, MAX_V = 1000;
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

int n, m, v, a, b;
vector<pair<int, ii>> monkeys;
vector<int> segments;
vector<vi> AdjList;
int res[MAX_V][MAX_V], mf, f, s, t;
vi p;
void augment(int v, int minEdge) {
	if (v == s) { f = minEdge; return; }
	else if (p[v] != -1) {
		augment(p[v], min(minEdge, res[p[v]][v]));
		res[p[v]][v] -= f; res[v][p[v]] += f;
	}
}

int main() {
	int cn = 0;
	while (1) {
		cn++;
		scanf("%d", &n); if (n == 0)break;
		scanf("%d", &m);
		AdjList.clear(); segments.clear(); monkeys.clear();
		memset(res, 0, sizeof(res)); int tot = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d", &v, &a, &b); tot += v;
			segments.push_back(a), segments.push_back(b);
			monkeys.push_back(make_pair(v, ii(a, b)));
		}
		sort(segments.begin(), segments.end());
		auto ip = unique(segments.begin(), segments.end());
		segments.resize(distance(segments.begin(), ip));
		int segNum = segments.size() - 1, V = n + segNum + 2;
		int i = V; while (i--) { vi temp; AdjList.push_back(temp); }
		for (int i = 1; i < n + 1; i++) {
			AdjList[0].push_back(i);
			AdjList[i].push_back(0);
			res[0][i] = monkeys[i - 1].first;
		}
		for (int i = n + 1; i < n + segNum + 1; i++) {
			int j = i - n - 1, k = 0;
			int n1 = segments[j], n2 = segments[j + 1];
			for (pair<int, ii> monkey : monkeys) {
				ii rangeM = monkey.second;
				if (rangeM.first <= n1 && n2 <= rangeM.second) {
					AdjList[k + 1].push_back(i);
					AdjList[i].push_back(k + 1);
					res[k + 1][i] = n2 - n1;
				}
				k++;
			}
			AdjList[i].push_back(n + segNum + 1);
			AdjList[n + segNum + 1].push_back(i);
			res[i][n + segNum + 1] = m * (n2 - n1);
		}
		//printf("Segments: \n");printVector(segments);
		//printf("Adj List: \n"); printAdjList(AdjList);
		//printf("res: \n"); for (int i = 0; i < V; i++)printArray(res[i], V);

		s = 0; t = n + segNum + 1;
		mf = 0;
		while (1) {
			f = 0;
			bitset<MAX_V> vis; vis[s] = true;
			queue<int> q; q.push(s);
			p.assign(MAX_V, -1);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				if (u == t) break;
				for (int j = 0; j < (int)AdjList[u].size(); j++) {
					int v = AdjList[u][j];
					if (res[u][v] > 0 && !vis[v])
						vis[v] = true, q.push(v), p[v] = u;
				}
			}
			augment(t, INF);
			if (f == 0) break;
			mf += f;
		}
		//printf("res: \n"); for (int i = 0; i < V; i++)printArray(res[i], V);
		printf("Case %d: ", cn);
		if (mf == tot) {
			printf("Yes\n"); vi arr(segNum, 0);
			for (int i = 1; i < n + 1; i++) {
				vii vp;
				for (int j = n + 1; j < n + segNum + 1; j++) {
					if (res[j][i] != 0) {
						int c1 = segments[j - n - 1], c2 = segments[j - n];
						int segWidth = c2 - c1;
						int initial = arr[j - n - 1];
						arr[j - n - 1] += res[j][i];
						if (res[j][i] == segWidth) {
							arr[j - n - 1] -= res[j][i];
							vp.push_back(ii(c1, c2));
						}
						else if (arr[j - n - 1] > segWidth) {
							vp.push_back(ii(c1 + initial, c2));
							arr[j - n - 1] %= segWidth;
							vp.push_back(ii(c1, c1 + arr[j - n - 1]));
						}
						else {
							vp.push_back(ii(c1 + initial, c1 + arr[j - n - 1]));
						}
					}
				}
				sort(vp.begin(), vp.end());
				vii vp2; vp2.push_back(vp[0]);
				for (int j = 1; j < vp.size(); j++) {
					ii lastEle = vp2.back(), nextEle = vp[j];
					if (nextEle.first != nextEle.second) {
						if (lastEle.second == nextEle.first)vp2.back().second = nextEle.second;
						else(vp2.push_back(nextEle));
					}
				}
				//printf("%d ", vp.size());
				//for (ii currPair : vp)printf("(%d,%d) ", currPair.first, currPair.second);
				//printf("\n");
				printf("%d", vp2.size());
				for (ii currPair : vp2) {
					printf(" (%d,%d)", currPair.first, currPair.second);
				}
				printf("\n"); 
			}
		}
		else {
			printf("No\n");
		}
	}

	// inside int main(): set up ‘res’, 'AdjMat', ‘s’, and ‘t’ with appropriate values

}


