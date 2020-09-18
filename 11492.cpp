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

int finder(vector<string>L, string word) {
	for (int i = 0; i < L.size(); i++) {
		if (L[i] == word)return i;
	}
	return -1;
}

vector<vii> adjList;
vector<string> langL, wordL;
vector<pair<int, int>> wordLangL;
int M;

int main() {
	while (1) {
		langL.clear(); wordL.clear(); wordLangL.clear(); adjList.clear();
		cin >> M; if (M == 0)break;
		for (int i = 0; i < M + 2; i++) {
			vii temp; adjList.push_back(temp);
		}
		string O, D;
		cin >> O >> D;
		langL.push_back(O); langL.push_back(D);
		for (int u = 0; u < M; u++) {
			string I1, I2, P;
			cin >> I1 >> I2 >> P;
			if (O == I1 || O == I2)adjList[M].push_back(ii(u, 0));
			else if (D == I1 || D == I2)adjList[u].push_back(ii(M + 1, P.size()));
			if (finder(langL, I1) == -1)langL.push_back(I1);
			if (finder(langL, I2) == -1)langL.push_back(I2);
			int l1 = finder(langL, I1), l2 = finder(langL, I2);
			for (int v = 0; v < wordLangL.size(); v++) {
				int t1 = wordLangL[v].first, t2 = wordLangL[v].second;
				if (t1 == l1 || t2 == l1 || t1 == l2 || t2 == l2) {
					if (P[0] != wordL[v][0]) {
						adjList[u].push_back(ii(v, P.size()));
						adjList[v].push_back(ii(u, wordL[v].size()));
					}
				}
			}
			wordL.push_back(P); wordLangL.push_back(ii(l1, l2));
		}
		/*cout << "\n";
		for (int i = 0; i < wordL.size(); i++)cout << wordL[i] << " " << langL[wordLangL[i].first] << " " << langL[wordLangL[i].second] << "\n";
		printAdjList(adjList);*/

		priority_queue<ii> pq; pq.push(ii(0, M));
		vector<int> dist(M + 2, INF); dist[M] = 0;
		while (!pq.empty()) {
			ii front = pq.top(); pq.pop();
			int u = front.second, d = front.first;
			if (d > dist[u])continue;
			for (ii v : adjList[u]) {
				if (dist[u] + v.second < dist[v.first]) {
					dist[v.first] = dist[u] + v.second;
					pq.push(ii(-dist[v.first], v.first));
				}
			}
		}
		//cout << dist[M + 1]==INF?"impossivel":dist[M+1]<<
		if (dist[M + 1] == INF)cout << "impossivel\n";
		else cout << "Answer: " << dist[M + 1] << "\n";
	}
}


