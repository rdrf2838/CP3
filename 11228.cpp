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

int T, n;
double r, x, y;

double dist(pair<double, double> p1, pair<double, double>p2) {
	return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}
int main() {
	scanf("%d\n", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %lf\n", &n, &r);
		vector<pair<double, double>> cityList;
		vector< pair<double, ii> > EdgeList;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &x, &y);
			pair<double, double> p1(x, y);
			for (int j = 0; j < cityList.size(); j++) {
				pair<double, double>p2 = cityList[j];
				EdgeList.push_back(make_pair(dist(p1, p2), ii(i, j)));
			}
			cityList.push_back(p1);
		}
		sort(EdgeList.begin(), EdgeList.end());
		/*for (pair<double, ii> eachPair : EdgeList) {
			printf("dist: %lf u: %d v: %d\n", eachPair.first, eachPair.second.first, eachPair.second.second);
		}*/

		int stateCtr = n, isUpdate = 0;
		double roadDist = 0, railDist = 0;
		UnionFind UF(n);
		for (int i = 0; i < EdgeList.size(); i++) {
			pair<double, ii>front = EdgeList[i];
			if (!UF.isSameSet(front.second.first, front.second.second)) {
				if (front.first <= r)roadDist += front.first;
				else {
					if (!isUpdate) {
						isUpdate = 1;
						stateCtr = UF.setCount();
					}
					railDist += front.first;
				}
				UF.unionSet(front.second.first, front.second.second);
			}
		}if (!isUpdate)stateCtr = UF.setCount();
		printf("Case #%d: %d %d %d\n", t, stateCtr, (int)(roadDist + 0.5), (int)(railDist + 0.5));
	}
}