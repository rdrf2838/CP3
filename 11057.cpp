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

int bsr(int arr[], int l, int r, int x) {
	if (r > l) {
		int midl = (r + l) / 2;
		int midr = midl + 1;
		if (arr[midl] == x)return midl;
		if (arr[midr] == x)return midr;
		if (arr[midl] < x && x < arr[midr])return midl;
		if (arr[midr] < x)return bsr(arr, midr, r, x);
		if (x < arr[midl])return bsr(arr, l, midl, x);
	}
}
int bs(int arr[], int l, int r, int x) {
	if (r >= l) {
		int mid = (r + l) / 2;
		if (arr[mid] == x)return mid;
		if (arr[mid] < x)return bs(arr, mid + 1, r, x);
		if (x < arr[mid])return bs(arr, l, mid - 1, x);
	}
	return -1;
}
int main() {
	int n, prices[10001], money;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &prices[i]);
		}
		scanf("%d", &money);
		sort(prices, prices + n);
		int startindex = bsr(prices, 0, n - 1, money / 2);
		for (int i = startindex; i >= 0; i--) {
			int p1 = prices[i]; int p2 = money - p1;
			int res = bs(prices, startindex + 1, n - 1, p2);
			if (res != -1) {
				printf("Peter should buy books whose prices are %d and %d.\n\n", p1, p2);
				break;
			}
		}

	}	
}