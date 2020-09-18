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

int main() {
	int M, N, Q, L, U;
	while (true) {
		int arr[501][501];
		scanf("%d %d", &N, &M);
		if (M == 0 && N == 0)break;
		for (int n = 0; n < N; n++) {
			for (int m = 0; m < M; m++) {
				scanf("%d", &arr[n][m]);
			}
		}
		scanf("%d", &Q);
		while (Q--) {
			int bestlen = 0;
			scanf("%d %d", &L, &U);
			bool validsol = false;
			for (int n = 0; n < N; n++) {
				auto it = lower_bound(arr[n], arr[n] + M, L);
				int m = it - arr[n];
				if (m == M)continue;
				int len = 0;

				while (true) {
					int mcurr = m + len;
					int ncurr = n + len;
					if (mcurr == M || ncurr == N|| arr[ncurr][mcurr] > U) {
						if (len > 0)validsol = true;
						if (len > bestlen) bestlen = len - 1;
						len = 0;
						break;
					}
					len++;
				}
			}
			validsol?printf("%d\n", bestlen + 1): printf("0\n");
		}
		printf("-\n");

	}
}