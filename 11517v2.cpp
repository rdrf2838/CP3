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

int T, price, n, moneylist[101], lowestprice, memo[30001];


int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &price, &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &moneylist[i]);
		}
		memo[0] = 0;
		for (int i = 0; i < n; i++) {
			int coinval = moneylist[i];
			for (int v = 30001 - coinval - 1; v >= 0; v--) {
				if (memo[v] < (1 << 30) - 1) {
					memo[v + coinval] = min(memo[v + coinval], memo[v] + 1);
				}
			}
		}
		printArray(memo, 30001);
	}
}

