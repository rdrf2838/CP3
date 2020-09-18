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
int T, n, arr[100001];
bool isvalid(int k) {
	int currk = k;
	for (int i = 0; i < n; i++) {
		int firstrung = arr[i];
		int nextrung = arr[i + 1];
		int disttojump = nextrung - firstrung;
		if (disttojump > k)return false;
		if (disttojump == k) k -= 1;
	}
	return true;
}

int binarysearch(int l, int r) {
	if (r >= l) {
		if (r == l)return r;
		int mid = (r + l) / 2;
		if (isvalid(mid))return binarysearch(l, mid);
		if (!isvalid(mid))return binarysearch(mid + 1, r);
	}
}

int main() {
	scanf("%d", &T);
	int counter = 1;
	while (T--) {
		scanf("%d", &n);
		arr[0] = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i+1]);
		}
		printf("Case %d: %d\n", counter, binarysearch(1, 10000000));
		counter += 1;
	}
}