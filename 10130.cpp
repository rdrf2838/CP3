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

int N, P[1001], W[1001], MW, G, memo[31][1001];

int val(int idx, int remW) {
	if (idx == N || remW == 0)return 0;
	if (memo[remW][idx] != -1)return memo[remW][idx];
	if (remW >= W[idx]) {
		int a = val(idx + 1, remW - W[idx]) + P[idx];
		int b = val(idx + 1, remW);
		return memo[remW][idx] = a > b ? a : b;
	}
	else {
		int b = val(idx + 1, remW);
		return memo[remW][idx] = b;
	}
}

int main() {
	//ofstream outfile;
	//outfile.open("Atest.txt");
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(memo, -1, sizeof(memo));
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &P[i], &W[i]);
		}
		scanf("%d", &G);
		int totalval = 0;
		for (int i = 0; i < G; i++) {
			scanf("%d", &MW);
			totalval += val(0, MW);
		}
		printf("%d\n", totalval);
		//outfile << totalval << "\n";
	}
	//outfile.close();
}
