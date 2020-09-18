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
int N, memoD[2001], memoI[2001], heights[2001], widths[2001];

int LIS(int i) {
	if (memoI[i] != -1)return memoI[i];
	int bestlis = 0;
	for (int j = 0; j < i; j++) {
		if (heights[j] < heights[i]) bestlis = max(bestlis, LIS(j));
	}
	return memoI[i] = bestlis + widths[i];
}
int LDS(int i) {
	if (memoD[i] != -1)return memoD[i];
	int bestlds = 0;
	for (int j = 0; j < i; j++) {
		if (heights[j] > heights[i])bestlds = max(bestlds, LDS(j));
	}
	return memoD[i] = bestlds + widths[i];
}

int main() {
	int T; scanf("%d", &T);
	for(int t=1; t<=T; t++) {
		scanf("%d", &N);
		for (int i = 0; i<N; i++) {
			scanf("%d", &heights[i]);
		}
		for (int i = 0; i < N; i++) {
			scanf("%d", &widths[i]);
		}
		memset(memoD, -1, sizeof(memoD)); memoD[0] = widths[0];
		memset(memoI, -1, sizeof(memoI)); memoI[0] = widths[0];
		int maxlis = 0; int maxlds = 0;
		for (int i = 0; i < N; i++) {
			maxlis = max(maxlis, LIS(i));
			maxlds = max(maxlds, LDS(i));
		}
		printf("Case %d. ", t);
		maxlis >= maxlds ? printf("Increasing (%d). Decreasing (%d).\n",maxlis,maxlds) 
			: printf("Decreasing (%d). Increasing (%d).\n",maxlds,maxlis);
		
	}
}
