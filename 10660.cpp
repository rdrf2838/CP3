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
# define endl "\n"
#define ii pair<int,int>
#define iii pair<ii,int>
#define viii vector<iii>
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
	return(abs(p1.first - p2.first) + abs(p1.second - p2.second));
}
int main() {
	vii intxy;
	for (int i = 0; i < 25; i++) {
		intxy.push_back(ii(i % 5, i / 5));
	}
	int t,n,r,q,p;
	scanf("%d\n", &t);
	while (t--) {
		viii plist;
		scanf("%d\n", &n);
		while (n--) {
			scanf("%d %d %d\n", &r, &q, &p);
			plist.push_back(iii(ii(q, r), p));
		}
		int sum = 2147483647, a0, b0, c0, d0, e0;
		for (int a = 0; a < 21; a++) {
			for (int b = a + 1; b < 22; b++) {
				for (int c = b + 1; c < 23; c++) {
					for (int d = c + 1; d < 24; d++) {
						for (int e = d + 1; e < 25; e++) {
							int cursum = 0;
							for (iii qrp : plist) {
								ii xy = qrp.first;
								int p = qrp.second;
								int arr[5] = { a,b,c,d,e };
								int mindist = 2147483647;
								for (int* temp = arr; temp < arr + 5; temp++) {
									int currdist = dist(xy, intxy[*temp]);
									if (currdist < mindist) {
										mindist = currdist;
									}
								}
								cursum += p * mindist;
							}
							if (cursum < sum) {
								a0 = a; b0 = b; c0 = c; d0 = d; e0 = e;
								sum = cursum;
							}
						}
					}
				}
			}
		}
		printf("%d %d %d %d %d\n", a0, b0, c0, d0, e0);
	}
}