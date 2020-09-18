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
		if (i != a) {
			printf(" ");
		}
		printf("%d", *i);
	}
	printf("\n");
}
int n, caseno = 0, arr[18]; bool test[18];
int primes[11] = { 2,3,5,7,11,13,17,19,23,29,31 };

bool isvalid(int a, int b) {
	return binary_search(primes, primes + 11, (a + b));
}

void backtrack(int arr[18], int remaining, int curridx, int lastint) {
	if (curridx == n) {
		if (isvalid(lastint, arr[0])) {
			printArray(arr, n);
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			int actint = i + 1;
			if (((1 << i) & remaining) && isvalid(actint, lastint)) {
				arr[curridx] = actint;
				int rmn = remaining & ~(1 << i);
				backtrack(arr, rmn, curridx + 1, actint);
			}
		}
	}
}

int main() {
	while (scanf("%d", &n) == 1) {
		caseno += 1;
		if (caseno > 1)printf("\n");
		printf("Case %d:\n", caseno);
		if (n != 1) {
			int temp = ((1 << n) - 2);
			arr[0] = 1;
			backtrack(arr, temp, 1, 1);
		}
	}
}