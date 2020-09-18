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
#define ALL(x) x.begin(), x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())


using namespace std;

void printArray(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i];
	}
	cout << endl;
}
int N;         // using global variables in contests can be a good strategy
char x[110];  // make it a habit to set array size a bit larger than needed

unsigned long long pow(unsigned long long a, unsigned long long b) {
	if (b == 1) {
		return a;
	}
	else {
		unsigned long long c = a * pow(a, b - 1);
		return c;
	}
}
int main() {
	int a;
	scanf("%d", &a);
	while (a--) {
		unsigned long long int sum = 0; int coeff[21], n, temp, d, k; memset(coeff, 0, sizeof(coeff));
		scanf("%d", &n);
		for (int i = 0; i <= n; i++) {
			scanf("%d", &temp);
			coeff[i] = temp;
		}
		scanf("%d %d", &d, &k);
		n = ceil((-1 + sqrt(1 + 8 * k / d)) / 2);
		for (int j = 0; j < 21; j++){
			if (coeff[j] == 0) {

			}
			else {
				sum += coeff[j] * pow(n, j);
			}
		}
		printf("%llu\n", sum);

	}
} // return 0;
