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

using namespace std;

void printArray(int a[], int n) {
	for (int* i = a; i < a + n; i++) {
		printf("%d ", *i);
	}
	printf("\n");
}


int t, n, x[13], arr[13], successcount;
vector<vector<int>> vvi;

bool isequal(vector<int> v1, vector<int> v2, int n) {
	bool res = true;
	for (int i = 0; i < n; i++) {
		if (v1[i] != v2[i]) res = false;
	}
	return res;
}

void backtrack(int nxtidx, int arr[13], int arrlen, int prevsum) {
	if (prevsum == t) {
		vector<int> currlist(arr, arr + 13);
		bool unique = true;
		for (vector<int> templist : vvi) {
			if (isequal(templist, currlist, arrlen)) unique = false;
		}
		if (unique) {
			vvi.push_back(currlist);
			successcount += 1;
			for (int i = 0; i < arrlen; i++) {
				if (i > 0)printf("+");
				printf("%d", arr[i]);
			}
			printf("\n");
		}
		return;
	}
	if (prevsum > t)return;
	if (nxtidx == n)return;

	for (int i = nxtidx; i < n; i++) {
		int nextval = x[i];
		int nextsum = nextval + prevsum;
		arr[arrlen] = nextval;
		backtrack(i + 1, arr, arrlen + 1, nextsum);
	}
}

int main() {
	while (true) {
		scanf("%d %d", &t, &n);
		if (n == 0)break;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x[i]);
		}
		successcount = 0; vvi.clear(); memset(arr, 0, sizeof(arr));
		printf("Sums of %d:\n", t);
		backtrack(0, arr, 0, 0);
		if (!successcount)printf("NONE\n");

	}
}