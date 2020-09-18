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

int money, memo[6][30001], coins[] = { 1,5,10,25,50 };

int ways(int type, int value) {
	if (value == 0)return 1;
	if (value < 0 || type == 5)return 0;
	if (memo[type][value] != -1)return memo[type][value];

	return memo[type][value] = ways(type + 1, value) + ways(type, value - coins[type]);
}

int main() {
	memset(memo, -1, sizeof(memo));
	while (scanf("%d", &money) == 1) {
		int waycount = ways(0, money);
		waycount == 1 ? printf("There is only 1 way to produce %d cents change.\n", money) :
			printf("There are %d ways to produce %d cents change.\n", waycount, money);
	}
}

