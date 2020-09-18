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
#define endl "\n"
#define ii pair<int,int>
#define vii vector<ii>
#define vi vector<int>

using namespace std;

void printArray(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << ",";
	}
	cout << endl;
}
int dist(ii p1, ii p2) {
	return (abs(p1.first - p2.first) + abs(p1.second - p2.second));
}
int main() {

	int x;
	while (scanf("%d\n", &x)==1) {
		vii v1;
		vii v3;
		char a, b, c, d;
		int y, tempa;
		y = x;
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				scanf("%c", &a);
				tempa = (int)a;
				if (tempa == 49) {
					v1.push_back(ii(j, i));
				}
				else if (tempa == 51) {
					v3.push_back(ii(j, i));
				}
			}
			scanf("\n");
		}
		vi distlist;
		for (ii curr1ii : v1) {
			int mindist = 2147483647;
			for (ii curr3ii : v3) {
				int currdist = dist(curr1ii, curr3ii);
				if (currdist < mindist) {
					mindist = currdist;
				}
			}
			distlist.push_back(mindist);
		}
		std::sort(distlist.begin(), distlist.end());
		std::printf("%d\n", distlist.back());
	}
}