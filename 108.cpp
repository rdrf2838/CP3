
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

int N, arr[101][101];
int rsq(int x0, int x1, int y0, int y1) {
	int currsum = arr[y1][x1];
	if (y0 > 0)currsum -= arr[y0 - 1][x1];
	if (x0 > 0)currsum -= arr[y1][x0 - 1];
	if (y0 > 0 && x0 > 0)currsum += arr[y0 - 1][x0 - 1];
	return currsum;
}
int finder() {
	int bestsum = -1270000;
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			for (int k = 0; k < N; k++) {
				for (int l = k; l < N; l++) {
					int currsum = rsq(k, l, i, j);
					if (currsum > bestsum)bestsum = currsum;
				}
			}
		}
	}
	return bestsum;
}
int main() {
	ofstream outfile;
	outfile.open("Test.txt");

	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &arr[i][j]);
				if (i > 0) arr[i][j] += arr[i - 1][j];
				if (j > 0) arr[i][j] += arr[i][j - 1];
				if (i > 0 && j > 0) arr[i][j] -= arr[i - 1][j - 1];
			}
		}
		int res = finder();
		printf("%d\n", res);
		outfile << res << "\n";
	}
	outfile.close();
}
