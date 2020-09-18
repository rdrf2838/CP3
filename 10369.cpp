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

int N, S, P, a, b;
double x, y;

double dist(pair<double, double> p1, pair<double, double>p2) {
	return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

int main() {
	scanf("%d\n", &N);
	while (N--) {
		scanf("%d %d\n", &S, &P);
		vector<pair<double, double>> pointList;
		vector< pair<double, ii> > EdgeList;
		for (int i = 0; i < P; i++) {
			scanf("%lf %lf", &x, &y);
			pair<double, double>p1(x, y);
			//printf("%lf %lf %lf %lf\n", x, y, p1.first, p1.second);
			for (int j = 0; j < pointList.size(); j++) {
				pair<double, double> p2 = pointList[j];
				//printf("p1.x: %d p1.y: %d p2.x: %d p2.y: %d dist:%d\n", p1.first, p1.second, p2.first, p2.second, dist(p1, p2));
				EdgeList.push_back(make_pair(dist(p1, p2), ii(i, j)));
			}
			pointList.push_back(p1);
		}

		//for (pair<double, double> point : pointList) {
		//	printf("%lf %lf\n", point.first, point.second);
		//}
		sort(EdgeList.begin(), EdgeList.end());

		//for (pair<double, ii> curr : EdgeList) {
		//	printf("dist: %lf u: %d v: %d\n", curr.first, curr.second.first, curr.second.second);
		//}

		UnionFind UF(P); double ans = 0;// all V are disjoint sets initially
		for (int i = 0; i < EdgeList.size(); i++) { // for each edge, O(E)
			pair<double, ii> front = EdgeList[i];
			if (!UF.isSameSet(front.second.first, front.second.second)) { // check
				UF.unionSet(front.second.first, front.second.second); // link them
				if (UF.setCount() == S) {
					ans = front.first;
					i = EdgeList.size();
				}
			}
		}
		printf("%.2lf\n", ans);
	}
}