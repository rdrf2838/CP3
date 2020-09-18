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

int N, arr[10001], prevnum, nextnum;

int rsq(int l, int r) {
	if (l == 0)return arr[r];
	return (arr[r] - arr[l-1]);
}
int search() {
	int maxval = -(1 << 31) + 1;
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			int currval = rsq(i, j);
			//printf("RSQ: %d %d is %d\n", i, j, currval);
			if (currval > maxval) maxval = currval;
		}
	}
	return maxval;
}

int printsearch(int maxval) {
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			int currval = rsq(i, j);
			if (maxval == currval) {
				printf("The indices are %d and %d\n", i, j);
			}
		}
	}
	return maxval;
}


int main() {
	while (true) {
		scanf("%d", &N);
		if (N == 0)break;
		for (int i = 0; i < N; i++) {
			if (i == 0)scanf("%d", &arr[0]);
			else {
				prevnum = arr[i - 1];
				scanf("%d", &nextnum);
				arr[i] = prevnum + nextnum;
			}
		}
		int ans = search();
		ans > 0 ? printf("The maximum winning streak is %d.\n", ans)
			: printf("Losing streak. %d\n", ans);
		//printsearch(ans);
	}
}