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
int N, memoD[2001], memoI[2001], arr[2001];

int LIS(int i) {
	if (memoI[i] != -1)return memoI[i];
	int bestlis = 0;
	for (int j = 0; j < i; j++) {
		if (arr[j] < arr[i]) bestlis = max(bestlis, LIS(j));
	}
	return memoI[i] = bestlis + 1;
}
int LDS(int i) {
	if (memoD[i] != -1)return memoD[i];
	int bestlds = 0;
	for (int j = 0; j < i; j++) {
		if (arr[j] > arr[i])bestlds = max(bestlds, LDS(j));
	}
	return memoD[i] = bestlds + 1;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		memset(memoD, -1, sizeof(memoD)); memoD[0] = 1;
		memset(memoI, -1, sizeof(memoI)); memoI[0] = 1;
		scanf("%d", &N);
		for (int i = N - 1; i >= 0; i--) {
			scanf("%d", &arr[i]);
		}
		int beslen = 0;
		for (int i = 0; i < N; i++) {
			int currlen = LDS(i) + LIS(i) - 1;
			beslen = max(beslen, currlen);
		}
		printf("%d\n", beslen);
	}
}
