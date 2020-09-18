
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
void printArray(long long a[], int n) {
	for (long long* i = a; i < a + n; i++) {
		if (i != a) {
			printf(" ");
		}
		printf("%lld", *i);
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

int m, //total money
n, //queries
plist[101],//price of each item
flist[101], //favour
memo[101][10001]; //memo[index][remaining money]
int favourer(int idx, int remM) {
	if (memo[idx][remM] != -1)return memo[idx][remM];
	if (remM == 0 || idx == n)return memo[idx][remM] = 0;
	if (plist[idx] > remM) return memo[idx][remM] = favourer(idx + 1, remM);
	return memo[idx][remM] = max(favourer(idx + 1, remM), favourer(idx + 1, remM - plist[idx]) + flist[idx]);
}

int favourerPrune(int idx, int remM) {
	//printf("idx: %d next item: %d remMoney: %d\n", idx, plist[idx],remM);
	if (memo[idx][remM] != -1)return memo[idx][remM];

	if (remM == 0) {
		return memo[idx][remM] = 0;
	}
	if (idx == n) {
		int moneyspent = m + 200 - remM;
		if (moneyspent <= 2000) {
			return memo[idx][remM] = -99999;
		}
		else return memo[idx][remM] = 0;
	}
	if (plist[idx] > remM) return memo[idx][remM] = favourerPrune(idx + 1, remM);
	return memo[idx][remM] = max(favourerPrune(idx + 1, remM), favourerPrune(idx + 1, remM - plist[idx]) + flist[idx]);
}

int main() {
	ofstream outfile;
	outfile.open("Test.txt");
	while (scanf("%d %d", &m, &n) == 2) {
		memset(memo, -1, sizeof(memo));
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &plist[i], &flist[i]);
		}
		if (m < 1800) {
			printf("%d\n", favourer(0, m));
			outfile << favourer(0, m) << "\n";
		}
		else {
			printf("%d\n", favourerPrune(0, m + 200));
			outfile << favourerPrune(0, m + 200) << "\n";

		}
	}

}
