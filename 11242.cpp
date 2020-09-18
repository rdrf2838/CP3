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
# define endl "\n"
using namespace std;

void printArray(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i];
	}
	cout << endl;
}
double round(double var, int dp)
{
	double value = (int)(var * dp + .5);
	return (double)value / dp;
}
int main() {
	while (true) {
		int f, r; double flist[101], rlist[101];
		memset(flist, 0, sizeof(flist)); memset(rlist, 0, sizeof(rlist));
		scanf("%d", &f);
		if (f == 0)break;
		cin >> r;
		for (int i = 0; i < f; i++) {
			scanf("%lf", &flist[i]);
		}
		for (int i = 0; i < r; i++) {
			scanf("%lf", &rlist[i]);
		}
		double dlist[10201]; memset(dlist, 11, sizeof(dlist)); int it = 0;
		for (int i = 0; i < f; i++) {
			double fcurr = flist[i];
			for (int j = 0; j < r; j++) {
				double rcurr = rlist[j];
				double d = rcurr / fcurr;
				dlist[it] = d;
				it += 1;
			}
		}
		sort(dlist, dlist + f * r);
		double diffmax = 0;
		for (int i = 0; i < f * r - 1; i++) {
			double d1 = dlist[i]; double d2 = dlist[i + 1];
			double diff = d2 / d1;
			if (diff > diffmax) {
				diffmax = diff;
			}
		}
		printf("%0.2lf\n", diffmax);
	}
}