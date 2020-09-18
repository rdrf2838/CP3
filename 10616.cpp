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

int N, Q, M, sumcounter;
long long nlist[201], D;
int memo[201][11][21];//memo[ctr][chosen][curremainder]

int solcount(int ctr, int chosen, long long currrem) {
	if (memo[ctr][chosen][currrem] != -1) {
		return memo[ctr][chosen][currrem];
	}

	if (chosen == M) {
		if (currrem == 0) {
			return (memo[ctr][chosen][currrem] = 1);
		}
		else { return memo[ctr][chosen][currrem] = 0; }
	}

	if (ctr == N) return (memo[ctr][chosen][currrem] = 0);

	long long nextrem = (currrem + nlist[ctr]) % D;
	if (nextrem < 0)nextrem += D;
	return memo[ctr][chosen][currrem] =
		solcount(ctr + 1, chosen, currrem) + solcount(ctr + 1, chosen + 1, nextrem);
}

int main() {
	int counter = 1;
	while (true) {
		scanf("%d %d", &N, &Q);
		if (N == 0 && Q == 0)break;
		printf("SET %d:\n", counter); counter++;
		for (int i = 0; i < N; i++) {
			scanf("%lld", &nlist[i]);
		}

		for (int i = 0; i < Q; i++) {
			memset(memo, -1, sizeof(memo));
			scanf("%d %d", &D, &M);
			printf("QUERY %d: %d\n", i + 1, solcount(0, 0, 0));
		}
	}
}
