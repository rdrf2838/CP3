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
int N, LIS[99999999], arr[99999999];

int LISsearch(int i, int arr[]) {
	if (LIS[i] != -1)return LIS[i];
	int LISmax = 0;
	for (int j = 0; j < i; j++) {
		if (arr[j] < arr[i]) {
			LISmax = max(LISmax, LISsearch(j, arr));
		}
	}
	LISmax += 1;
	return LIS[i] = LISmax;
}

void LISprint(int i, int arr[]) {
	for (int j = 0; j < i; j++) {
		if (LIS[j] == LIS[i] - 1) {
			printf("%d ", arr[j]);
			LISprint(j, arr);
		}
	}
}

int main() {
	int arr[8] = { -7, 10, 9, 2, 3, 8, 8, 1 };
	memset(LIS, -1, sizeof(LIS)); LIS[0] = 1;
	cout<<LISsearch(6,arr)<<"\n";
	printArray(LIS, 8);
	LISprint(6, arr);
}