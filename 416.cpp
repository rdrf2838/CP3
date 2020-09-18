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
		if (i != a) {
			printf(" ");
		}
		printf("%d", *i);
	}
	printf("\n");
}

char temp[8];
int numlist[10] = { 111,127,7,125,109,102,79,91,6,63 }, selectedlist[11], givenlist[11], n, counter;

int bitter(const char* word) {
	char one[2] = "Y";
	int num = 0;
	for (int i = 0; i < 7; i++) {
		if (word[i] == one[0]) {
			num |= (1 << i);
		}
	}
	return num;
}

bool isvalid(int startidx) {
	int burneddigits = 0;
	for (int i = 0; i < n; i++) {
		int currnum = givenlist[i];
		int correctnum = numlist[startidx + i];
		if ((correctnum | currnum) != correctnum) {
			return false;
		}
		int burneddigits2 = correctnum - currnum;
		if (((correctnum & burneddigits) | burneddigits2) != burneddigits2) {
			return false;
		}
		burneddigits = burneddigits | burneddigits2;

	}
	return true;
}

void checker() {
	for (int i = 0; i < 11 - n; i++) {
		if (isvalid(i)) {
			counter += 1;
		}
	}
}
int main() {
	while (true) {
		scanf("%d", &n); if (n == 0)break;
		for (int i = 0; i < n; i++) {
			scanf("%s", temp);
			int cur = bitter(temp);
			givenlist[i] = cur;
		}
		counter = 0;
		checker();
		counter > 0 ? printf("MATCH\n") : printf("MISMATCH\n");
	}
}