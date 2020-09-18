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
}
int s, d, tarr[13], bestsum;
//currmonth starts from 0, ends at 11

int arrsum(int arr[13]) {
	int sum = 0;
	for (int* i = arr; i < arr + 12; i++) {
		sum += *i == 1 ? s : (-d);
	}
	return sum;
}
bool isvalid(int currmonth, int arr[13]) {
	int* end = arr + currmonth + 1; int* start = arr + currmonth - 4;
	int sum = 0;
	for (int* i = start; i < end; i++) {
		sum += *i == 1 ? s : (-d);
	}
	return sum < 0 ? true : false;
}
void backtrack(int currmonth, int arr[13]) {
	if (currmonth == 12) {
		int currsum = arrsum(arr);
		if (bestsum < currsum) bestsum = currsum;
		return;
	}
	else {
		if (currmonth >= 4 && !isvalid(currmonth, arr)) {
			return;
		}
		arr[currmonth + 1] = 1;
		backtrack(currmonth + 1, arr);
		arr[currmonth + 1] = 0;
		backtrack(currmonth + 1, arr);
	}

}
int main() {
	while (scanf("%d %d", &s, &d) == 2) {
		bestsum = -(1 << 31) + 1;
		memset(tarr, 0, sizeof(tarr));
		backtrack(-1, tarr);
		bestsum >= 0 ? printf("%d\n", bestsum) : printf("Deficit\n");
	}
}