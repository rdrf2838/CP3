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

int T, price, n, moneylist[101], lowestprice, memo[101][10001];

int coinnum(int nextidx, int currval) {
	if (currval >= price) {
		if (currval <= lowestprice) {
			lowestprice = currval;
			return 0;
		}return 99999;
	}
	if (nextidx == n)return 99999;

	if (memo[nextidx][currval] != -1) {
		return memo[nextidx][currval];
	}
	return memo[nextidx][currval] = 
		(min(coinnum(nextidx + 1, currval), 1 + coinnum(nextidx + 1, currval + moneylist[nextidx])));
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &price, &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &moneylist[i]);
		}
		lowestprice = 10001; memset(memo, -1, sizeof(memo));
		int ans = coinnum(0, 0);
		printf("answer: %d %d\n", lowestprice, ans);
	}
}

