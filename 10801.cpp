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

int n, k, elevator[6][110];

int main() {
	while (scanf("%d %d\n", &n, &k) == 2) {
		memset(elevator, 0, sizeof(elevator));
		for (int i = 0; i < n; i++)
			scanf("%d", &elevator[i][0]);
		scanf("\n");
		for (int i = 0; i < n; i++) {
			char temp[300];
			fgets(temp, 300, stdin);
			string str(temp); stringstream ss(str);
			int num;
			while (ss >> num) {
				//remember to convert back!!
				elevator[i][num + 1] = 1;
			}
		}
		/*for (int i = 0; i < 6; i++) {
			printArray(elevator[i], 110);
		}*/

		vector<int> dur(101, INF); dur[1] = 0;
		priority_queue<pair<int, ii>> pq;
		for (int i = 0; i < n; i++)
			if (elevator[i][1] == 1) {
				//printf("Pushed: 0, currfloor: 1, currlift: %d\n", i);
				pq.push(make_pair(0, ii(1, i)));
			}

		while (!pq.empty()) {
			pair<int, ii> front = pq.top(); pq.pop();
			int d = -front.first, currFloor = front.second.first, currLift = front.second.second;
			//printf("Visiting: dur: %d currFloor: %d currLift: %d\n", d, currFloor, currLift);
			if (d > dur[currFloor])continue;
			for (int nextLift = 0; nextLift < n; nextLift++) {
				if (elevator[nextLift][currFloor])
				for (int nextFloor = 1; nextFloor < 101; nextFloor++) {
					if (elevator[nextLift][nextFloor]) {
						int nextTime = d;
						if (currLift != nextLift)nextTime += 60;
						nextTime += abs(nextFloor - currFloor) * elevator[nextLift][0];
						if (nextTime < dur[nextFloor]) {
							dur[nextFloor] = nextTime;
							pq.push(make_pair(-nextTime, ii(nextFloor, nextLift)));
						}
					}
				}
			}
		}
		int ans = dur[k + 1];
		if (ans == INF)printf("IMPOSSIBLE\n");
		else printf("%d\n", ans);
	}
}