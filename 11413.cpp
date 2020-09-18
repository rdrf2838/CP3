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

using namespace std;

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

int n, m, arr[1001];

bool isvalid(int ctrsize) {
	int ctrcount = 1, currctrfillvol = 0;
	for (int i = 0; i < n; i++) {
		int currvesselsize = arr[i];
		if (currvesselsize > ctrsize)return false;
		currctrfillvol += currvesselsize;
		if (currctrfillvol > ctrsize) {
			currctrfillvol = currvesselsize;
			ctrcount += 1;
		}
		if (ctrcount > m)return false;
	}
	return true;
}

int binarysearch(int l, int r) {
	if (r >= l) {
		if (r == l)return r;
		int mid = (l + r) / 2;
		if (isvalid(mid))return binarysearch(l, mid);
		if (!isvalid(mid))return binarysearch(mid + 1, r);
	}
	return -1;
}

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
		}
		printf("%d\n",binarysearch(0,1000000));
	}
}