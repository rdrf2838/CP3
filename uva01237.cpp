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

using namespace std;

void printArray(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i];
	}
	cout << endl;
}
int main() {
	printf("hello world!");
	//int a;
	//scanf("%d", &a);
	//printf("%d", a);
	/*int a;
	scanf("%d", &a);
	while (a--) {
		int d, low[10001], high[10001]; memset(low, 0, sizeof(low)); memset(high, 0, sizeof(high));
		char name[10001][21]; memset(name, "", sizeof(name));
		scanf("%d", &d);
		for (int i = 0; i < d; i++) {
			scanf("%s %d %d", name[i], low[i], high[i]);
		}
		int q, ctr, query[1001]; memset(query, 0, sizeof(query));
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d", query[i]);
		}
		printArray(low, d);
		printArray(high, d);
		printArray(query, q);
	}*/
}