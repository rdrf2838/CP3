


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

int M, C, price[25][25];
int memo[210][25];

int shop(int money, int g) {
	if (money < 0)return -1000000000;
	if (g == C)return M - money;
	int ans = -1;
	if (memo[money][g] != -1)return memo[money][g];
	for (int model = 1; model <= price[g][0]; model++) {
		int res = shop(money - price[g][model], g + 1);
		if (res > ans)ans = res;
	};
	return memo[money][g] = ans;
}

int main() {
	int i, j, TC, score;
	scanf("%d", &TC);
	while (TC--) {
		scanf("%d %d", &M, &C);
		for (i = 0; i < C; i++) {
			scanf("%d", &price[i][0]); // store K in price[i][0]
			for (j = 1; j <= price[i][0]; j++) scanf("%d", &price[i][j]);
		}
		memset(memo, -1, sizeof(memo));
		score = shop(M, 0);
		score >= 0 ? printf("%d\n", score) : printf("No solution\n");
	}
	return 0;
}