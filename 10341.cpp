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

int p, q, r, s, t, u;

double f(double x) {
	return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int main() {
	double error = 1e-7;
	while (scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u) == 6) {
		if (f(0) * f(1) > 0) {
			printf("No solution\n");
		}
		else {
			double l = 0, r = 1, solution;
			while (true) {
				double mid = (l + r) / 2;
				if (r - l < error) {
					solution = mid;
					break;
				}
				else if (f(mid) == 0) {
					solution = mid;
					break;
				}
				else if (f(mid) > 0) {
					l = mid;
				}
				else if (f(mid) < 0) {
					r = mid;
				}
			}
			printf("%.4lf\n", solution);
		}

	}
}