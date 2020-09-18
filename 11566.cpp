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
double x, T, plist[202], M;
int N//number of people
, K//number of dim sum dishes
//price list
, flist[202]//favour list
, temp
//total money = (N+1)*x
, memo[1001][101]; //memo[money][dish num]
//remember to divide the favour by (n+1) at the end!
int favour(int dimsumPrice, int orderedNum, int nextDish) {
	if (orderedNum == 2 * (N + 1) || nextDish == 2 * K)return 0;
	if (memo[dimsumPrice][nextDish] != -1)return memo[dimsumPrice][nextDish];
	int nexttotalcost = (int)(0.99999 + 1.1 * ((double)dimsumPrice + plist[nextDish] + T * ((double)N + 1.0)));
	if (nexttotalcost > M) return memo[dimsumPrice][nextDish] = favour(dimsumPrice, orderedNum, nextDish + 1);
	else return memo[dimsumPrice][nextDish] = max(favour(dimsumPrice, orderedNum, nextDish + 1),
		favour(dimsumPrice + plist[nextDish], orderedNum + 1, nextDish + 1) + flist[nextDish]);
}

int main() {
	while (true) {
		memset(flist, 0, sizeof(flist));
		memset(memo, -1, sizeof(memo));
		scanf("%d %lf %lf %d", &N, &x, &T, &K);
		M = (N + 1) * x;
		if (N == 0 && x == 0 && T == 0 && K == 0)break;
		for (int i = 0; i < K; i++) {
			scanf("%lf", &plist[2 * i]);
			plist[2 * i + 1] = plist[2 * i];
			for (int j = 0; j < N + 1; j++) {
				scanf("%d", &temp);
				flist[2 * i] += temp;
			}
			flist[2 * i + 1] = flist[2 * i];
		}
		printf("%0.2lf\n", (double)favour(0, 0, 0) / (double)(N + 1));
	}
}

