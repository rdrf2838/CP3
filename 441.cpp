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
# define endl "\n"
using namespace std;

void printArray(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i];
	}
	cout << endl;
}
double round(double var, int dp)
{
	double value = (int)(var * dp + .5);
	return (double)value / dp;
}
int main() {
	std::ios::sync_with_stdio(false);
	int number = 0;
	while (true) {
		number += 1;
		if (number > 1)cout << endl;
		int k, s[13]; memset(s, 50, sizeof(s));
		cin >> k;
		if (k == 0) { break; }
		for (int i = 0; i < k; i++) {
			cin >> s[i];
		}
		for (int a = 0; a < k - 5; a++) {
			for (int b = a + 1; b < k - 4; b++) {
				for (int c = b + 1; c < k - 3; c++) {
					for (int d = c + 1; d < k - 2; d++) {
						for (int e = d + 1; e < k - 1; e++) {
							for (int f = e + 1; f < k; f++) {
								cout << s[a] << " " << s[b] << " " << s[c] << " " << s[d] << " " << s[e] << " " << s[f] << endl;
							}
						}
					}
				}
			}
		}

	}
}