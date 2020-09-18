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

const int INF = 99999;
vector<vii> AdjList;
vector<int> inDeg;
vector<int> topList;
int N, M, u, v;
char b[110][60], temp1[120], temp2[120];
int bfind(char name[60]) {
	for (int i = 0; i < N; i++) {
		if (strcmp(b[i], name) == 0)return i;
	}
}
int main() {
	int caseno = 0;
	while (scanf("%d\n", &N) == 1) {
		caseno++;
		AdjList.clear(); inDeg.clear(); inDeg.assign(N, 0); topList.clear();
		for (int i = 0; i < N; i++) {
			scanf("%s\n", &b[i]);
			vii temp; AdjList.push_back(temp);
		}
		scanf("%d\n", &M);
		for (int i = 0; i < M; i++) {
			scanf("%s %s\n", &temp1, &temp2);
			u = bfind(temp1);
			v = bfind(temp2);
			AdjList[u].push_back(ii(v, 0));
		}
		for (int i = 0; i < N; i++) {
			for (ii v : AdjList[i]) {
				inDeg[v.first]++;
			}
		}
		priority_queue<int> pq;
		for (int i = 0; i < N; i++) {
			if (inDeg[i] == 0) {
				pq.push(-i);
			}
		}
		while (!pq.empty()) {
			int u = -pq.top(); pq.pop();
			topList.push_back(u);
			for (ii v : AdjList[u]) {
				inDeg[v.first]--;
				if (inDeg[v.first] == 0) {
					pq.push(-v.first);
				}
			}
		}
		//printVector ( topList);
		printf("Case #%d: Dilbert should drink beverages in this order:",caseno);
		for (int i : topList) {
			printf(" %s", b[i]);
		}printf(".\n\n");
	}

}
