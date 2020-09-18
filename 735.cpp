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
# define endl "\n"
using namespace std;

void printArray(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i]<<",";
	}
	cout << endl;
}
int main() {
	int arr[43] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
		20,21,22,24,26,27,28,30,32,33,34,36,38,39,40,42,45,48,50,51,54,57,60 };
	while (true) {
		int x;
		scanf("%d", &x);
		if (x <= 0) {
			printf("END OF OUTPUT");
			break;
		}
		int ctr = 0; int cctr = 0;
		bool visited[43][43][43]; memset(visited, false, sizeof(visited));
		for (int i = 0; i < 43; i++) {
			for (int j = 0; j < 43; j++) {
				for (int k = 0; k < 43; k++) {
					int sum = arr[i] + arr[j] + arr[k];
					if (sum == x) {
						int temp[3] = { arr[i], arr[j], arr[k] };
						sort(temp, temp + 3);
						ctr += 1;
						if (!visited[i][j][k]) {
							cctr += 1;
							visited[i][j][k] = true;
							visited[i][k][j] = true;
							visited[j][i][k] = true;
							visited[j][k][i] = true;
							visited[k][i][j] = true;
							visited[k][j][i] = true;
						}
					}
				}
			}
		}
		if (ctr == 0) {
			printf("THE SCORE OF %d CANNOT BE MADE WITH THREE DARTS.\n", x);
		}
		else {
			printf("NUMBER OF COMBINATIONS THAT SCORES %d IS %d.\n", x, cctr);
			printf("NUMBER OF PERMUTATIONS THAT SCORES %d IS %d.\n", x, ctr);
		}
		for (int i = 0; i < 70; i++) {
			printf("*");
		}
		printf("\n");
	}
}