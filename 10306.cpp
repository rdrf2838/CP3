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

int n, m, S;
int conval[41], infoval[41];
int memo[3000][3000];

int ways(int currcv, int curriv) {
	int totalval = currcv * currcv + curriv * curriv;
	if (totalval == S * S)return 0;
	if (totalval > S * S)return 99999;
	if (memo[currcv][curriv] != -1)return memo[currcv][curriv];
	int leastways = 99999;
	for (int i = 0; i < m; i++) {
		int nextcv = currcv + conval[i];
		int nextiv = curriv + infoval[i];
		leastways = min(leastways, ways(nextcv, nextiv));
	}leastways += 1;
	return memo[currcv][curriv] = leastways;
}

int main() {
	scanf("%d", &n);
	while (n--) {
		memset(memo, -1, sizeof(memo));
		scanf("%d %d", &m, &S);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &conval[i], &infoval[i]);
		}
		int ans = ways(0, 0);
		ans >= 99999 ? printf("not possible\n") : printf("%d\n", ans);
	}
}

