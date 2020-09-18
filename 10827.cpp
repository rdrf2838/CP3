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
void printArray(bool a[], int n) {
	for (bool* i = a; i < a + n; i++) {
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

int T, N, arr[151][151];
int search() {
	int bestsum = -2250000;
	for (int r0 = 0; r0 < N; r0++) {
		for (int r1 = r0; r1 < r0 + N; r1++) {
			for (int c0 = 0; c0 < N; c0++) {
				for (int c1 = c0; c1 < c0 + N; c1++) {
					int currsum = arr[r1][c1];
					if (r0 > 0) currsum -= arr[r0 - 1][c1];
					if (c0 > 0) currsum -= arr[r1][c0 - 1];
					if (r0 > 0 && c0 > 0)currsum += arr[r0 - 1][c0 - 1];
					bestsum = max(bestsum, currsum);
				}
			}
		}
	}
	return bestsum;
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int r = 0; r < 2 * N; r++) {
			for (int c = 0; c < 2 * N; c++) {
				if (r < N && c < N) {
					int temp; scanf("%d", &temp);
					arr[r][c] = temp;
					arr[r + N][c] = temp;
					arr[r][c + N] = temp;
					arr[r + N][c + N] = temp;
				}
				if (r > 0)arr[r][c] += arr[r - 1][c];
				if (c > 0)arr[r][c] += arr[r][c - 1];
				if (r > 0 && c > 0)arr[r][c] -= arr[r - 1][c - 1];
			}
		}
		int res = search();
		printf("%d\n", res);
	}
}