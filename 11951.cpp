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

int T, N, M;
long long K, arr[101][101];
int main() {
	//ofstream outfile;
	//outfile.open("Test.txt");
	scanf("%d", &T);
	for(int i=1; i<=T; i++) {
		scanf("%d %d %d", &N, &M, &K);
		for (int r = 0; r < N; r++){
			for (int c = 0; c < M; c++) {
				scanf("%d", &arr[r][c]);
				if (r > 0) arr[r][c] += arr[r - 1][c];
				if (c > 0) arr[r][c] += arr[r][c - 1];
				if (r > 0 && c > 0)arr[r][c] -= arr[r - 1][c - 1];
			}
		}
		long long bestsum = K; int bestarea = 0;
		for (int r0 = 0; r0 < N; r0++) {
			for (int r1 = r0; r1 < N; r1++) {
				for (int c0 = 0; c0 < M; c0++) {
					for (int c1 = c0; c1 < M; c1++) {
						int currarea = (c1 - c0 + 1) * (r1 - r0 + 1);
						if (currarea < bestarea)continue;
						long long currsum = arr[r1][c1];
						if (r0 > 0)currsum -= arr[r0 - 1][c1];
						if (c0 > 0)currsum -= arr[r1][c0 - 1];
						if (r0 > 0 && c0 > 0)currsum += arr[r0 - 1][c0 - 1];
						if (currsum <= K) {
							if (currarea == bestarea) {
								if (currsum < bestsum) bestsum = currsum;
							}
							else {
								bestsum = currsum;
								bestarea = currarea;
							}
						}
					}
				}
			}
		}
		if (bestarea == 0)bestsum = 0;
		printf("Case #%d: %d %lld\n", i, bestarea, bestsum);
		//outfile << "Case #" << i << ": " << bestarea << " " << bestsum<<"\n";
	}
	//outfile.close();
}