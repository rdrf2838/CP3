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

using namespace std;

void printArray(int a[], int n) {
	for (int* i = a; i < a + n; i++) {
		printf("%d ", *i);
	}
}

int n, t, arr[21], temparr[21], bestarr[21], bestsum, bestctr;

void backtrack(int temparr[21], int tempctr, int ctr, int currsum) {
	if (ctr == t + 1) {
		if (currsum > bestsum) {
			bestsum = currsum;
			bestctr = tempctr;
			copy(temparr, temparr + tempctr - 1, bestarr);
		}
	}
	else {
		for (int i = ctr; i < t + 1; i++) {
			int nextval = arr[i];
			int nextsum = nextval + currsum;
			if (nextsum <= n) {
				temparr[tempctr] = nextval;
				backtrack(temparr, tempctr + 1, i + 1, nextsum);
			}
		}
	}
}

int main() {

	while (scanf("%d %d", &n, &t) == 2) {
		memset(arr, 0, sizeof(arr)); memset(bestarr, 0, sizeof(bestarr)); memset(temparr, 0, sizeof(temparr));
		bestsum = 0; bestctr = 0;
		int tsum = 0;
		for (int i = 0; i < t; i++) {
			scanf("%d", &arr[i]);
			tsum += arr[i];
		}
		if (tsum <= n) {
			printArray(arr, t); printf("sum:%d\n", tsum);
		}
		else {
			backtrack(temparr, 0, 0, 0);
			printArray(bestarr, bestctr - 1); printf("sum:%d\n", bestsum);
		}

	}
}